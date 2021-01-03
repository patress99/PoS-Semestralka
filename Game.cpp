#include "Game.h"

//Private functions
void Game::initVariables() {

    this->window = nullptr;
    this->winner = nullptr;

    if (!this->worldBackgroundTex.loadFromFile("../assets/sky.jpg")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
        exit(1);
    }

    if (!this->gameFont.loadFromFile("../fonts/aAsianNinja.ttf")) {
        std::cout << "ERROR::GAME::Failed to load font" << "\n";
        exit(3);
    }

    this->worldBackground.setTexture(this->worldBackgroundTex);
    this->endGame = false;
}

void Game::initWindow() {
    this->videoMode.height = 900;
    this->videoMode.width = 1600;

    this->window = new sf::RenderWindow(this->videoMode, "Mlaticka", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initGUI() {

    //Nicknames of players
    this->player1Name.setPosition(sf::Vector2f(20.f, 50.f));
    this->player1Name.setFont(this->gameFont);
    this->player1Name.setCharacterSize(35);
    this->player1Name.setFillColor(sf::Color::Red);
    this->player1Name.setString(this->hrac1->getName());

    this->player2Name.setPosition(sf::Vector2f(this->videoMode.width - 320.f, 50.f));
    this->player2Name.setFont(this->gameFont);
    this->player2Name.setCharacterSize(35);
    this->player2Name.setFillColor(sf::Color::Blue);
    this->player2Name.setString(this->hrac2->getName());


    //Healthbars
    this->player1HealthBar.setSize(sf::Vector2f(300.f, 25.f));
    this->player1HealthBar.setFillColor(sf::Color::Red);
    this->player1HealthBar.setPosition(sf::Vector2f(20.f, 20.f));

    this->player1HealthBarBack = this->player1HealthBar;
    this->player1HealthBarBack.setFillColor(sf::Color(25, 25, 25, 200));

    this->player2HealthBar.setSize(sf::Vector2f(300.f, 25.f));
    this->player2HealthBar.setFillColor(sf::Color::Blue);
    this->player2HealthBar.setPosition(sf::Vector2f(this->videoMode.width - 320.f, 20.f));

    this->player2HealthBarBack = this->player2HealthBar;
    this->player2HealthBarBack.setFillColor(sf::Color(25, 25, 25, 200));


}

void Game::initPlayers() {
    this->hrac1 = new Hrac(1, "Test1", 50, this->videoMode.height - 100);
    this->hrac2 = new Hrac(2, "Test2", this->videoMode.width - 100, this->videoMode.height - 100);
}


Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initPlayers();
    this->initGUI();
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

    this->pollEvents();

    if (this->endGame == false) {
        if (this->hrac1->getHealth() <= 0) {
            this->winner = hrac2;
            this->endGame = true;
        }

        if (this->hrac2->getHealth() <= 0) {
            this->winner = hrac1;
            this->endGame = true;
        }
    }

    if (this->endGame == true) {
        //TODO: Hrac1 / Hrac 2 zomrel - ohlas koniec hry
    }
}


void Game::renderPlayers() {
    this->hrac1->render(*this->window);
    this->hrac2->render(*this->window);
}

void Game::renderWorld() {
    this->window->draw(this->worldBackground);
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
    //Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->hrac1->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->hrac1->move(1.f, 0.f);

    //Move player2
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->hrac2->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->hrac2->move(1.f, 0.f);


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->hrac1->canAttack()) {
        //Utok hraca 1
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->hrac1->canAttack()) {
        //Utok hraca 2
    }
}

void Game::render() {

    this->window->clear();

    this->renderWorld();
    this->renderPlayers();

    this->renderGui();

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

void Game::start() {
    this->buffer = new sf::SoundBuffer();
    buffer->loadFromFile("../sounds/start.ogg");
    this->sound = new sf::Sound();
    sound->setBuffer(*buffer);
    sound->setVolume(20.0f);
    sound->play();
}