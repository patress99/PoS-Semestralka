#include "Game.h"

Game::Game(sf::RenderWindow& wind) : window(wind) {

    this->buffer = new sf::SoundBuffer();
    this->sound = new sf::Sound();
    this->bufferM = new sf::SoundBuffer();
    this->battleMusic = new sf::Sound();

    this->ip = sf::IpAddress::getLocalAddress();
    this->playable = true;

    this->musicCooldown = 0;

}

void Game::initVariables() {

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

    if (!this->muteTex.loadFromFile("../assets/mute.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD MUTE ICON" << "\n";
        exit(3);
    }
    this->muteIcon.setTexture(this->muteTex);
    this->muteIcon.scale(0.2f,0.2f);
    this->muteIcon.setPosition(sf::Vector2f(20.f, 100.f));

    this->worldBackground.setTexture(this->worldBackgroundTex);

    this->grass.setTexture(this->grassTex);
    this->grass.setPosition(sf::Vector2f(0.f, 840.f));
    this->endGame = false;
}

void Game::initGUI() {
    this->playerName.setFont(this->gameFont);
    this->playerName.setOutlineColor(sf::Color::Black);
    this->playerName.setOutlineThickness(2.f);
    this->playerName.setCharacterSize(35);
    this->playerName.setFillColor(sf::Color::White);
    this->playerName.setString(this->player->getName());

    this->enemyName.setFont(this->gameFont);
    this->enemyName.setOutlineColor(sf::Color::Black);
    this->enemyName.setOutlineThickness(2.f);
    this->enemyName.setCharacterSize(35);
    this->enemyName.setFillColor(sf::Color::White);
    this->enemyName.setString(this->enemy->getName());



    this->playerHealthBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHealthBar.setFillColor(sf::Color::Red);


    this->enemyHealthBar.setSize(sf::Vector2f(300.f, 25.f));
    this->enemyHealthBar.setFillColor(sf::Color::Red);


    if (this->playerType == 's') {
        //Player names
        this->playerName.setPosition(sf::Vector2f(20.f, 5.f));
        this->enemyName.setPosition(sf::Vector2f(this->window.getSize().x - 20.f - this->enemyName.getLocalBounds().width, 5.f));

        //Healthbars
        this->playerHealthBar.setPosition(sf::Vector2f(20.f, 50.f));
        this->enemyHealthBar.setPosition(sf::Vector2f(this->window.getSize().x - 20.f, 50.f + this->enemyHealthBar.getLocalBounds().height));
        this->enemyHealthBar.setRotation(180);
    } else {
        //Player names
        this->playerName.setPosition(sf::Vector2f(this->window.getSize().x - 20.f - this->playerName.getLocalBounds().width , 5.f));
        this->enemyName.setPosition(sf::Vector2f(20.f, 5.f));

        //Healthbars
        this->playerHealthBar.setPosition(sf::Vector2f(this->window.getSize().x - 20.f, 50.f + + this->playerHealthBar.getLocalBounds().height));
        this->playerHealthBar.setRotation(180);
        this->enemyHealthBar.setPosition(sf::Vector2f(20.f, 50.f));

    }

    this->playerHealthBarBack = this->playerHealthBar;
    this->playerHealthBarBack.setFillColor(sf::Color(0, 0, 0, 50));

    this->enemyHealthBarBack = this->enemyHealthBar;
    this->enemyHealthBarBack.setFillColor(sf::Color(0, 0, 0, 50));

}

void Game::initPlayers() {

    if (this->playerType == 's') {
        this->player = new Player(1, this->playerName.getString(), 50, this->window.getSize().y - 100);
        this->enemy = new Player(2, this->enemyName.getString(), this->window.getSize().x - 50, this->window.getSize().y - 100);
    } else {
        this->player = new Player(2, this->playerName.getString(), this->window.getSize().x - 50, this->window.getSize().y - 100);
        this->enemy = new Player(1, this->enemyName.getString(), 50, this->window.getSize().y - 100);
    }
}

Game::~Game() {
    delete this->player;
    delete this->enemy;
    delete this->buffer;
    delete this->sound;
    delete this->bufferM;
    delete this->battleMusic;

}


const bool Game::running() const {
    return this->window.isOpen();
}

const bool Game::isEndGame() const {
    return this->endGame;
}

void Game::pollEvents() {
    //Event polling
    while (this->window.pollEvent(this->ev)) {
        std::string disc = "d";
        bool done = false;
        switch (this->ev.type) {

            case sf::Event::Closed:
                do {
                    mutex.lock();
                    socket.setBlocking(true);
                    socket.send(disc.c_str(),disc.length()+1);
                    socket.setBlocking(false);
                    done = true;

                    if (this->playerType == 's') {
                        this->listener.close();

                    }
                    this->socket.disconnect();
                    window.close();
                    mutex.unlock();

                } while (!done);



                break;
            case sf::Event::GainedFocus:
                this->playable = true;
                break;
            case sf::Event::LostFocus:
                this->playable = false;
                break;


        }
    }
}

void Game::update() {
    this->updateInput();
    this->updatePlayers();
    this->updateCollision();
    this->updateGUI();



    if (!this->endGame) {
        if (this->player->getHealth() <= 0) {
            this->winner = enemy;
            this->endGame = true;
            playSound("vyhralProtivnik.wav");

        }

        if (this->enemy->getHealth() <= 0) {
            this->winner = player;
            this->endGame = true;
            playSound("vyhralHrac.wav");
        }

    }

}


void Game::renderPlayers() {
    this->window.draw(this->player->getSprite());
    this->window.draw(this->enemy->getSprite());
}

void Game::renderWorld() {
    this->window.draw(this->worldBackground);
    this->window.draw(this->grass);
}


void Game::updateCollision() {
    //Out of bounds player1

    if (this->player->getBounds().left < 0.f) {
        this->player->setPosition(0.f, this->player->getBounds().top);

    } else if (this->player->getBounds().left + this->player->getBounds().width >= this->window.getSize().x) {
        if (this->playerType == 's') {
            this->player->setPosition(this->window.getSize().x - this->player->getBounds().width, this->player->getBounds().top);
        } else {
            this->player->setPosition(this->window.getSize().x, this->player->getBounds().top);
        }

    }

    //Out of bounds player2
    if (this->enemy->getBounds().left < 0.f) {
        this->enemy->setPosition(0.f, this->enemy->getBounds().top);
    } else if (this->enemy->getBounds().left + this->enemy->getBounds().width >= this->window.getSize().x) {
        if (this->playerType == 's') {
            this->enemy->setPosition(this->window.getSize().x, this->player->getBounds().top);
        } else {
            this->enemy->setPosition(this->window.getSize().x - this->player->getBounds().width, this->player->getBounds().top);
        }

    }

    //Collision of players
    if (this->player->getBounds().intersects(this->enemy->getBounds()) ||
        this->enemy->getBounds().intersects(this->player->getBounds())) {
        if (this->playerType == 's') {
            this->player->move(-1, 0);
            this->enemy->move(1, 0);
        } else {
            this->player->move(1, 0);
            this->enemy->move(-1, 0);
        }

    }
}

void Game::updateGUI() {
    float percentage1 = static_cast<float>(this->player->getHealth()) / this->player->getMaxHealth();
    float percentage2 = static_cast<float>(this->enemy->getHealth()) / this->enemy->getMaxHealth();

    this->playerHealthBar.setSize(sf::Vector2f(300.f * percentage1, this->playerHealthBar.getSize().y));
    this->enemyHealthBar.setSize(sf::Vector2f(300.f * percentage2, this->enemyHealthBar.getSize().y));


}

void Game::updateInput() {
    int sound = 0;


    if (this->playable) {

        //Move player
        this->musCooldown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !this->musCooldown()) {
            if (this->battleMusic->getVolume() > 0.f) {
                this->battleMusic->setVolume(0.f);
            } else {
                this->battleMusic->setVolume(5.f);
            }
            this->musicCooldown = 100;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            this->player->move(-1.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            this->player->move(1.f, 0.f);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack() && !this->playerBlocked) {
            this->player->setAttackCooldown();
            if (abs(this->player->getPos().x - this->enemy->getPos().x) < 150) {
                if (this->enemyBlocked) {
                    playSound("block.ogg");
                    sound = 3;
                } else {

                    if (this->playerCritical) {
                        this->enemy->loseHp((rand() % 5) + 15);
                        playSound("auCrit.wav");
                        sound = 4;
                    } else {
                        this->enemy->loseHp((rand() % 5) + 5);
                        playSound("au.wav");
                        sound = 2;
                    }


                }

            } else {
                playSound("empty-hit.wav");
                sound = 1;
            }
            this->playerCritical = false;
            this->playerAttacked = true;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->player->canBlock() && !this->playerAttacked) {
            this->player->setBlockCooldown();
            playSound("empty-hit.wav");
            sound = 1;

            this->playerBlocked = true;

        }
    }

    mutex.lock();
    packet << this->player->getPos().x << this->player->getPos().y << this->playerAttacked << this->playerBlocked << sound
           << this->enemy->getHealth();
    //TCP
    socket.send(packet);
    packet.clear();
    mutex.unlock();
}

void Game::render() {

    this->window.clear();


    this->renderWorld();
    this->renderPlayers();
    this->renderGui();



    if (this->endGame) {
        this->renderEnd();
    }


    this->window.display();
}

void Game::updatePlayers() {
    this->player->update();
    this->enemy->update();
}

void Game::renderGui() {

    this->window.draw(this->playerName);
    this->window.draw(this->enemyName);
    this->window.draw(this->playerHealthBar);
    this->window.draw(this->playerHealthBarBack);
    this->window.draw(this->enemyHealthBar);
    this->window.draw(this->enemyHealthBarBack);
    if (this->battleMusic->getVolume() == 0.f) {
        this->window.draw(this->muteIcon);
    }

}

void Game::renderEnd() {
    sf::Text winnerName;

    winnerName.setPosition(sf::Vector2f((window.getSize().x / 2) - 100, window.getSize().y / 2));
    winnerName.setFont(this->gameFont);
    winnerName.setCharacterSize(35);
    winnerName.setFillColor(sf::Color::Green);

    if (this->winner == nullptr) {
        if (this->playerType == 's') {

            winnerName.setString("Client sa odpojil");
        } else {
            winnerName.setString("Server sa odpojil");
        }

    } else {
        winnerName.setString("Vyhral : " + this->winner->getName());
    }




    this->window.draw(winnerName);

}

void Game::playSound(sf::String string) {
    buffer->loadFromFile("../sounds/" + string);
    sound->setBuffer(*buffer);
    sound->setVolume(20.0f);
    sound->play();
}

void Game::playMusic(sf::String string) {
    bufferM->loadFromFile("../sounds/" + string);
    battleMusic->setBuffer(*bufferM);
    battleMusic->setVolume(5.0f);
    battleMusic->setLoop(true);
    battleMusic->play();

}

bool Game::setPlayerType(char type, sf::String ip) {

    sf::String eName;
    this->playerType = type;
    this->port = 2000;


    if (type == 's') {
        serverSide();
    } else {
        if (!clientSide(ip)) {
            std::cout << "RIP NENAPOJIL SOMSA" << std::endl;
            this->player = nullptr;
            this->enemy = nullptr;
            return false;
        }
    }

    mutex.lock();
    packet << this->playerName.getString();
    socket.send(packet);
    packet.clear();
    socket.receive(packet);
    if (packet >> eName) {
        this->enemyName.setString(eName);
    }
    packet.clear();
    mutex.unlock();


    socket.setBlocking(false);
    return true;
}

void Game::init() {

    this->initVariables();
    this->initPlayers();
    this->initGUI();
    this->playMusic("battleMusic.ogg");

    sf::Thread *packetThread;
    packetThread = new sf::Thread(&Game::thUpdateOnlineGame, this);
    packetThread->launch();

    sf::Thread *animThread;
    animThread = new sf::Thread(&Game::thAnimate, this);
    animThread->launch();
}


void Game::serverSide() {

    listener.listen(this->port);
    std::cout << "Listening on port " << this->port << ". Waiting for client to connect..." << std::endl;
    this->acceptClient();

    //sf::Thread * thread = new sf::Thread(&Game::acceptClient, this);
    //thread->launch();
}

void Game::acceptClient() {
    listener.accept(this->socket);
    std::cout << "Connection with client established " << std::endl;
}

bool Game::clientSide(sf::String serverIP) {

    sf::IpAddress ip(serverIP);

    sf::Socket::Status status;

    int pocetPokusov = 0;
    do {
        if (pocetPokusov > 10) {
            std::cout << "Unable to connect to server" << std::endl;
            return false;
        }
        pocetPokusov++;

        status = this->socket.connect(ip, 2000, sf::seconds(3));
        std::cout << "Waiting for server to host game..." << std::endl;

    } while (status != sf::Socket::Done);

    std::cout << "Connected to server! Starting Game..." << std::endl;
    return true;
}

void Game::thUpdateOnlineGame() {

    sf::Vector2f prevPos, hrac2Pos;
    bool attacked, blocked;
    int healthH2, healthHrac;
    int sound;

    while (!this->endGame) {
        mutex.lock();

        char data[2000];
        size_t received;
        socket.receive(data, sizeof(data),received);
        if (received > 0) {
            std::string txt;
            txt = data;

            if (txt == "d") {
                std::cout << "Enemy sa odpojil" << std::endl;
                socket.disconnect();
                playSound("vyhralHrac.wav");
                this->endGame = true;
            }


        }
        socket.receive(packet);
        if (packet >> hrac2Pos.x >> hrac2Pos.y >> attacked >> blocked >> sound >> healthHrac) {
            this->player->setHealth(healthHrac);
            this->enemy->setPosition(hrac2Pos);
            this->enemyBlocked = blocked;
            if (attacked) {
                if (this->playerType == 's') {
                    this->enemy->updateTexture("hrac2utok.png");
                } else {
                    this->enemy->updateTexture("hrac1utok.png");
                }
            } else if (!attacked) {
                if (this->playerType == 's') {
                    this->enemy->updateTexture("hrac2.png");
                } else {
                    this->enemy->updateTexture("hrac1.png");

                }
            }

            if (blocked) {
                if (this->playerType == 's') {
                    this->enemy->updateTexture("hrac2blok.png");
                } else {
                    this->enemy->updateTexture("hrac1blok.png");
                }
            }

            if (sound == 1) {
                playSound("empty-hit.wav");

            } else if (sound == 2) {
                playSound("au.wav");
            } else if (sound == 3) {
                playSound("block.ogg");
                this->playerCritical = true;
            } else if (sound == 4) {
                playSound("auCrit.wav");
            }
        }
        packet.clear();

        mutex.unlock();
        sf::sleep(sf::milliseconds(1));


    }


}

void Game::thAnimate() {

    while (!this->endGame) {
        if (this->playerAttacked) {

            if (this->playerType == 's') {
                this->player->updateTexture("hrac1utok.png");
            } else {
                this->player->updateTexture("hrac2utok.png");

            }
            sf::sleep(sf::milliseconds(150));

            if (this->playerType == 's') {
                this->player->updateTexture("hrac1.png");
            } else {
                this->player->updateTexture("hrac2.png");
            }
            this->playerAttacked = false;

        } else if (this->playerBlocked) {

            if (this->playerType == 's') {
                this->player->updateTexture("hrac1blok.png");
            } else {
                this->player->updateTexture("hrac2blok.png");

            }
            sf::sleep(sf::milliseconds(100));

            if (this->playerType == 's') {
                this->player->updateTexture("hrac1.png");
            } else {
                this->player->updateTexture("hrac2.png");
            }
            this->playerBlocked = false;

        }

    }

}

sf::RenderWindow& Game::getWindow() {
    return this->window;
}

void Game::setPlayerName(sf::String string) {

    if (string.isEmpty()) {
        string = (this->playerType == 'c' ? "Player1" : "Player2");
    }
    this->playerName.setString(string);

}

bool Game::musCooldown() {
    if (this->musicCooldown == 0) {
        return false;
    }
    this->musicCooldown--;
    return true;
}

Player* Game::getWinner() {
    return this->winner;
}





