#include "Game.h"

//Private functions
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

    this->window = new sf::RenderWindow(this->videoMode, "Mlaticka", sf::Style::Titlebar | sf::Style::Close);
    sf::Image image;
    if (!image.loadFromFile("../assets/mlaticka.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD ICON" << "\n";
        exit(1);
    }

    this->window->setIcon(image.getSize().x,image.getSize().y,image.getPixelsPtr());

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
        this->hrac1 = new Hrac(1, "Janci", 50, this->videoMode.height - 100);
        this->hrac2 = new Hrac(2, "Jurci", this->videoMode.width - 100, this->videoMode.height - 100);
    } else {
        this->hrac1 = new Hrac(2, "Jurci", this->videoMode.width - 100, this->videoMode.height - 100);
        this->hrac2 = new Hrac(1, "Janci", 50, this->videoMode.height - 100);
    }
}


Game::Game() {
    this->buffer = new sf::SoundBuffer();
    this->sound = new sf::Sound();
    this->ip = sf::IpAddress::getLocalAddress();
    this->playable = true;


}

Game::~Game() {
    delete this->window;
    delete this->hrac1;
    delete this->hrac2;
    delete this->buffer;
    delete this->sound;

    //delete this->socket;
    delete this->server;
    delete this->client;
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

    this->updateInput();
    this->updatePlayers();
    this->updateCollision();
    this->updateGUI();



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
    //Out of bounds hrac1
    if (this->hrac1->getBounds().left < 0.f) {
        this->hrac1->setPosition(0.f, this->hrac1->getBounds().top);
    } else if (this->hrac1->getBounds().left + this->hrac1->getBounds().width >= this->window->getSize().x) {
        this->hrac1->setPosition(this->window->getSize().x - this->hrac1->getBounds().width,
                                 this->hrac1->getBounds().top);
    }

    //Out of bounds hrac2
    if (this->hrac2->getBounds().left < 0.f) {
        this->hrac2->setPosition(0.f, this->hrac2->getBounds().top);
    } else if (this->hrac2->getBounds().left + this->hrac2->getBounds().width >= this->window->getSize().x) {
        this->hrac2->setPosition(this->window->getSize().x - this->hrac2->getBounds().width,
                                 this->hrac2->getBounds().top);
    }

    //Collision hraci
    if (this->hrac1->getBounds().intersects(this->hrac2->getBounds()) ||
        this->hrac2->getBounds().intersects(this->hrac1->getBounds())) {
        this->hrac1->move(-1, 0);
        this->hrac2->move(1, 0);
    }
}

void Game::updateGUI() {
    float percentage1 = static_cast<float>(this->hrac1->getHealth()) / this->hrac1->getMaxHealth();
    float percentage2 = static_cast<float>(this->hrac2->getHealth()) / this->hrac2->getMaxHealth();

    this->player1HealthBar.setSize(sf::Vector2f(300.f * percentage1, this->player1HealthBar.getSize().y));
    this->player2HealthBar.setSize(sf::Vector2f(300.f * percentage2, this->player2HealthBar.getSize().y));




}

void Game::updateInput() {

    sf::Packet packet;

    sf::Vector2f prevPos, hrac2Pos;
    int healthH2, healthHrac;

    healthH2 = this->hrac2->getHealth();
    prevPos = this->hrac1->getPos();

    std::cout << "HP PACKET : "<< healthH2 << std::endl;
    std::cout << "HP REAL : "<< this->hrac2->getHealth() << std::endl;

    socket.setBlocking(false);

    if (this->playable) {


        //Move player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            this->hrac1->move(-1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            this->hrac1->move(1.f, 0.f);

        //Move player2
/*    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->hrac2->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->hrac2->move(1.f, 0.f);*/


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->hrac1->canAttack()) {
            //Utok hraca 1
            if (this->playerType == 's') {
                this->hrac1->updateTexture("hrac1utok.png");

            } else {
                this->hrac1->updateTexture("hrac2utok.png");
            }



            if (abs(this->hrac1->getPos().x-this->hrac2->getPos().x) < 90) {
                this->hrac2->loseHp(20);


                playSound("au.wav");
            } else {
                playSound("empty-hit.wav");
            }

            //this->hrac1->updateTexture("hrac1.png");

        }

/*    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->hrac2->canAttack()) {
        //Utok hraca 2
        this->hrac2->updateTexture("hrac2utok.png");

        if (abs(this->hrac1->getPos().x-this->hrac2->getPos().x) < 90) {
            this->hrac1->loseHp(20);
            playSound("au.wav");
        } else {
            playSound("empty-hit.wav");
        }
        //this->hrac2->updateTexture("hrac2.png");
    }*/


    }

    std::cout << "HP PACKET : "<< healthH2 << std::endl;
    std::cout << "HP REAL : "<< this->hrac2->getHealth() << std::endl;

/*    if (healthH2 != this->hrac2->getHealth()) {
        packetHp << this->hrac2->getHealth();
        socket.send(packetHp);
    }

    socket.receive(packetHp);
    if (packetHp >> healthHrac) {
        if (healthHrac != this->hrac1->getHealth()) {
            this->hrac1->setHealth(healthHrac);
        }

    }





    if (prevPos != this->hrac1->getPos()) {
        packetPos << this->hrac1->getPos().x << this->hrac1->getPos().y;
        socket.send(packetPos);
    }*/

    packet << this->hrac1->getPos().x << this->hrac1->getPos().y << this->hrac2->getHealth();
    socket.send(packet);

    socket.receive(packet);
    if (packet >> hrac2Pos.x >> hrac2Pos.y >> healthHrac) {
        this->hrac2->setPosition(hrac2Pos);
        this->hrac1->setHealth(healthHrac);
    }


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
    winnerName.setPosition(sf::Vector2f((window->getSize().x / 2) - 100, window->getSize().y /2));
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

    std::cout << "Game : " << &this->socket<< std::endl;
    std::cout << "Game : " << this->socket.getRemotePort() << std::endl;
    std::cout << "Game : " << this->socket.getRemoteAddress()<< std::endl;
    if (type == 's') {
        //this->server = serverSide();
        //this->socket = &server->getSocket();
        serverSide();
        std::cout << "Server vytvoreny" << std::endl;
    } else {
        //this->client = new Client(PORT);
        //this->socket = &client->getSocket();
        clientSide();
        std::cout << "Client vytvoreny" << std::endl;
    }
    std::cout << "Game : " << &this->socket<< std::endl;
    std::cout << "Game : " << this->socket.getRemotePort() << std::endl;
    std::cout << "Game : " << this->socket.getRemoteAddress()<< std::endl;
}

char Game::getPlayerType() {
    return this->playerType;
}

void Game::updateOnlineGame(sf::Vector2f pos) {

    sf::Packet packet;

    if (this->playerType == 's') {

        if (pos != this->hrac1->getPos()) {
            packet << this->hrac1->getPos().x << this->hrac1->getPos().y;

        }
    } else if (this->playerType == 'c') {


        if (pos != this->hrac2->getPos()) {
            packet << this->hrac2->getPos().x << this->hrac2->getPos().y;

        }
    }
    socket.receive(packet);

    sf::Vector2f position;

    if (packet >> position.x >> position.y) {
        this->hrac2->setPosition(position);
    }


}

Hrac Game::getPlayer() {
    if (this->playerType == 's') {
        return *this->hrac1;
    } else {
        return *this->hrac2;
    }
}

void Game::isGameReady() {



    bool ready = false;
    if (this->playerType == 's') {
        //this->server->listenToConnection();
        //this->socket = &this->server->getSocket();
        std::cout << "GameREADY : " << &this->socket<< std::endl;
        std::cout << "GameREADY : " << &this->socket<< std::endl;

        //std::cout << "GameREADY : " << &this->server->getSocket()<< std::endl;
        //std::cout << "GameREADY : " << &this->server->getSocket()<< std::endl;
    } else {

        do {
            //this->client->tryToConnect();
            clientSide();
            std::cout << "Client caka na server" << std::endl;
            //if (this->socket.connect(this->client->getIp(),PORT) == (this->socket.Done)) {
            if (this->socket.connect(this->ip,PORT) == (this->socket.Done)) {
                std::cout << "Client sa spojil so serverom" << std::endl;
                ready = true;
            }


        } while(!ready);
    }


}

void Game::init() {
    this->initVariables();
    this->initWindow();
    this->initPlayers();
    this->initGUI();
}



void Game::serverSide() {

    std::cout << &this->socket<< std::endl;
    std::cout << this->socket.getRemotePort() << std::endl;
    std::cout << this->socket.getRemoteAddress()<< std::endl;

    listener.listen(PORT);
    listener.accept(this->socket);
    std::cout << "Server sa spojil" << std::endl;

    std::cout << &this->socket<< std::endl;
    std::cout << this->socket.getRemotePort() << std::endl;
    std::cout << this->socket.getRemoteAddress()<< std::endl;

}

void Game::clientSide() {
    this->socket.connect(this->ip,PORT);
}

sf::TcpSocket &Game::getSocket() {
    return this->socket;
}

void Game::testMessage() {



    std::cout << this->playerType << " : " << this->socket.getRemoteAddress() << std::endl;
    std::cout << this->playerType << " : " <<this->socket.getRemotePort() << std::endl;


    char data[100];
    size_t received;
    std::string txt;
    txt = "GOD";
    socket.send(txt.c_str(),txt.length()+1);
    socket.receive(data, sizeof(data), received);

    std::cout << "Received " << data << " bytes" << std::endl;





}
