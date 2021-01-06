#include "Game.h"

void Game::initVariables() {

    this->window = nullptr;
    this->winner = nullptr;

    if (!this->worldBackgroundTex.loadFromFile("../assets/sky.jpg")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
        exit(1);
    }

    if (!this->grassTex.loadFromFile("../assets/grass.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD GRASS TEXTURE" << "\n";
        exit(1);
    }

    if (!this->gameFont.loadFromFile("../fonts/aAsianNinja.ttf")) {
        std::cout << "ERROR::GAME::Failed to load font" << "\n";
        exit(3);
    }

    this->worldBackground.setTexture(this->worldBackgroundTex);

    this->grass.setTexture(this->grassTex);
    this->grass.setPosition(sf::Vector2f(0.f, 840.f));
    this->endGame = false;
}

void Game::initWindow() {
    this->videoMode.height = 900;
    this->videoMode.width = 1600;

    if (this->playerType == 's') {
        this->window = new sf::RenderWindow(this->videoMode, "Mlaticka Server", sf::Style::Titlebar | sf::Style::Close);
    } else {
        this->window = new sf::RenderWindow(this->videoMode, "Mlaticka Client", sf::Style::Titlebar | sf::Style::Close);
    }

    sf::Image image;

    if (!image.loadFromFile("../assets/mlaticka.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD ICON" << "\n";
        exit(1);
    }

    this->window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initGUI() {

    //Nicknames of players
    this->player1Name.setPosition(sf::Vector2f(20.f, 50.f));
    this->player1Name.setFont(this->gameFont);
    this->player1Name.setCharacterSize(35);
    this->player1Name.setFillColor(sf::Color::Blue);
    this->player1Name.setString(this->hrac1->getName());

    this->player2Name.setPosition(sf::Vector2f(this->videoMode.width - 320.f, 50.f));
    this->player2Name.setFont(this->gameFont);
    this->player2Name.setCharacterSize(35);
    this->player2Name.setFillColor(sf::Color::Red);
    this->player2Name.setString(this->hrac2->getName());


    //Healthbars
    this->player1HealthBar.setSize(sf::Vector2f(300.f, 25.f));
    this->player1HealthBar.setFillColor(sf::Color::Blue);
    this->player1HealthBar.setPosition(sf::Vector2f(20.f, 20.f));

    this->player1HealthBarBack = this->player1HealthBar;
    this->player1HealthBarBack.setFillColor(sf::Color(25, 25, 25, 200));

    this->player2HealthBar.setSize(sf::Vector2f(300.f, 25.f));
    this->player2HealthBar.setFillColor(sf::Color::Red);
    this->player2HealthBar.setPosition(sf::Vector2f(this->videoMode.width - 320.f, 20.f));

    this->player2HealthBarBack = this->player2HealthBar;
    this->player2HealthBarBack.setFillColor(sf::Color(25, 25, 25, 200));


}

void Game::initPlayers() {

    if (this->playerType == 's') {
        this->hrac1 = new Player(1, "Player 1", 50, this->videoMode.height - 100);
        this->hrac2 = new Player(2, "Player 2 ", this->videoMode.width - 100, this->videoMode.height - 100);
    } else {
        this->hrac1 = new Player(2, "Player 2", this->videoMode.width - 100, this->videoMode.height - 100);
        this->hrac2 = new Player(1, "Player 1", 50, this->videoMode.height - 100);
    }
}


Game::Game() {
    this->buffer = new sf::SoundBuffer();
    this->sound = new sf::Sound();
    this->ip = sf::IpAddress::getLocalAddress();

    this->playable = true;
    this->initVariables();


}

Game::~Game() {
    delete this->window;
    delete this->hrac1;
    delete this->hrac2;
    delete this->buffer;
    delete this->sound;

}


const bool Game::running() const {
    return this->window->isOpen();
}

const bool Game::getEndGame() const {

    return this->endGame;
}

void Game::pollEvents() {
    //Event polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::GainedFocus:
                this->playable = true;
                break;
            case sf::Event::LostFocus:
                this->playable = false;
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;

        }
    }
}

void Game::update() {

    this->updateOnlineGame();

    this->updateInput();
    this->updatePlayers();
    this->updateCollision();
    this->updateGUI();

    this->updateOnlineGame();


    if (this->endGame == false) {
        if (this->hrac1->getHealth() <= 0) {
            this->winner = hrac2;
            this->endGame = true;
            playSound("vyhralProtivnik.wav");

        }

        if (this->hrac2->getHealth() <= 0) {
            this->winner = hrac1;
            this->endGame = true;
            playSound("vyhralHrac.wav");
        }

    }

    this->updateOnlineGame();
}


void Game::renderPlayers() {
    this->hrac1->render(*this->window);
    this->hrac2->render(*this->window);
}

void Game::renderWorld() {
    this->window->draw(this->worldBackground);
    this->window->draw(this->grass);
}


void Game::updateCollision() {
    //Out of bounds player1

    if (this->hrac1->getBounds().left < 0.f) {
        this->hrac1->setPosition(0.f, this->hrac1->getBounds().top);
    } else if (this->hrac1->getBounds().left + this->hrac1->getBounds().width >= this->window->getSize().x) {
        this->hrac1->setPosition(this->window->getSize().x - this->hrac1->getBounds().width,
                                 this->hrac1->getBounds().top);
    }

    //Out of bounds player2
    if (this->hrac2->getBounds().left < 0.f) {
        this->hrac2->setPosition(0.f, this->hrac2->getBounds().top);
    } else if (this->hrac2->getBounds().left + this->hrac2->getBounds().width >= this->window->getSize().x) {
        this->hrac2->setPosition(this->window->getSize().x - this->hrac2->getBounds().width,
                                 this->hrac2->getBounds().top);
    }

    //Collision of players
    if (this->hrac1->getBounds().intersects(this->hrac2->getBounds()) ||
        this->hrac2->getBounds().intersects(this->hrac1->getBounds())) {
        if (this->playerType == 's') {
            this->hrac1->move(-1, 0);
            this->hrac2->move(1, 0);
        } else {
            this->hrac1->move(1, 0);
            this->hrac2->move(-1, 0);
        }

    }
}

void Game::updateGUI() {
    float percentage1 = static_cast<float>(this->hrac1->getHealth()) / this->hrac1->getMaxHealth();
    float percentage2 = static_cast<float>(this->hrac2->getHealth()) / this->hrac2->getMaxHealth();

    this->player1HealthBar.setSize(sf::Vector2f(300.f * percentage1, this->player1HealthBar.getSize().y));
    this->player2HealthBar.setSize(sf::Vector2f(300.f * percentage2, this->player2HealthBar.getSize().y));


}

void Game::updateInput() {

    if (this->playable) {


        //Move player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            this->hrac1->move(-1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            this->hrac1->move(1.f, 0.f);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->hrac1->canAttack()) {

            if (abs(this->hrac1->getPos().x - this->hrac2->getPos().x) < 90) {
                this->hrac2->loseHp(20);
                playSound("au.wav");
            } else {
                playSound("empty-hit.wav");
            }
        }

    }



/*

 TCP:
    socket.send(packet);

    socket.receive(packet);
    if (packet >> hrac2Pos.x >> hrac2Pos.y >> healthHrac) {
        this->hrac2->setPosition(hrac2Pos);
        this->hrac1->setHealth(healthHrac);
    }
*/



}

void Game::render() {

    this->window->clear();

    this->renderWorld();
    this->renderPlayers();
    this->renderGui();

    if (this->endGame == true) {
        this->renderEnd();
    }

    this->window->display();
}

void Game::updatePlayers() {
    this->hrac1->update();
    this->hrac2->update();
}

void Game::renderGui() {

    this->window->draw(this->player1Name);
    this->window->draw(this->player2Name);
    this->window->draw(this->player1HealthBar);
    this->window->draw(this->player1HealthBarBack);
    this->window->draw(this->player2HealthBar);
    this->window->draw(this->player2HealthBarBack);

}

void Game::renderEnd() {
    sf::Text winnerName;
    winnerName.setPosition(sf::Vector2f((window->getSize().x / 2) - 100, window->getSize().y / 2));
    winnerName.setFont(this->gameFont);
    winnerName.setCharacterSize(35);
    winnerName.setFillColor(sf::Color::Green);
    winnerName.setString("Vyhral hrac " + this->winner->getName());

    this->window->draw(winnerName);

}

void Game::playSound(sf::String string) {
    buffer->loadFromFile("../sounds/" + string);
    sound->setBuffer(*buffer);
    sound->setVolume(20.0f);
    sound->play();
}

void Game::setPlayerType(char type) {
    this->playerType = type;

    if (type == 's') {

        this->port = 2000;

        if (socket.bind(this->port) != sf::Socket::Done) {
            std::cout << "Socket Server Error: Unable to bind to port " << this->port << std::endl;
        }



        serverSide();

        std::cout << "Server Created!" << std::endl;

    } else {

        this->port = 2001;

        if (socket.bind(this->port) != sf::Socket::Done) {
            std::cout << "Socket Client Error: Unable to bind to port " << this->port << std::endl;
        }



        clientSide();

        std::cout << "Client Created!" << std::endl;

    }


    socket.setBlocking(false);
}

void Game::init() {
    this->initWindow();
    this->initPlayers();
    this->initGUI();
}


void Game::serverSide() {
    //TCP

    /*
    listener.listen(PORT);
    listener.accept(this->socket);
    std::cout << "Server sa spojil s clientom" << std::endl;
    */

    char buffer[2000];
    size_t received;

    do {
        if (socket.receive(buffer, sizeof(buffer), received, rIp, rPort) != sf::Socket::Done) {
            std::cout << "Socket error" << std::endl;
        }
    } while (received <= 0);


}

void Game::clientSide() {
    //TCP
    //this->socket.connect(this->ip,PORT);

    //sf::IpAddress sendIP("25.85.55.6");
    sf::IpAddress sendIP(this->ip.getLocalAddress());


    this->rIp = sendIP;
    this->rPort = 2000;
    std::string txt = "Connection established!";

    if (socket.send(txt.c_str(), txt.length() + 1, this->rIp, this->rPort) != sf::Socket::Done) {
        std::cout << "Socket error" << std::endl;
    }
}

void Game::updateOnlineGame() {

    sf::Packet packet;

    sf::Vector2f prevPos, hrac2Pos;
    int healthH2, healthHrac;

    healthH2 = this->hrac2->getHealth();
    prevPos = this->hrac1->getPos();


    packet << this->hrac1->getPos().x << this->hrac1->getPos().y << this->hrac2->getHealth();
    socket.send(packet, rIp, rPort);


    socket.receive(packet, rIp, rPort);

    if (packet >> hrac2Pos.x >> hrac2Pos.y >> healthHrac ) {
        this->hrac1->setHealth(healthHrac);
        this->hrac2->setPosition(hrac2Pos);

    }
}




