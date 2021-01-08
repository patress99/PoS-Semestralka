#include "Menu.h"
#include "Game.h"


Menu::Menu() {

    this->playerName = "Player";
    this->serverIP = "localhost";
    this->playerType = 'x';

    this->offsetY = 100.f;
    this->offsetX = 40.f;

    this->videoMode.height = 900;
    this->videoMode.width = 1600;

    if (!font.loadFromFile("../fonts/aAsianNinja.ttf")) {
        std::cout << "Cannot load Font aAsianNinja!" << std::endl;
    }


    if (!this->backgroundTex.loadFromFile("../assets/mlaticka.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << std::endl;
        exit(1);
    }

    sf::Image image;
    if (!image.loadFromFile("../assets/mlaticka.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD ICON" << "\n";
        exit(1);
    }


    this->window.create(this->videoMode, "Mlaticka", sf::Style::Titlebar | sf::Style::Close);


    this->window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    this->window.setFramerateLimit(144);
    this->window.setVerticalSyncEnabled(false);


    this->buffer = new sf::SoundBuffer();
    this->bufferM = new sf::SoundBuffer();
    this->sound = new sf::Sound();
    this->mainTheme = new sf::Sound();

    this->playMusic("mlatC.ogg");


    this->background.setTexture(this->backgroundTex);

    this->mainMenu();

    while (this->window.isOpen()) {
        this->pollEvents();
        this->renderWindow();
    }

}


Menu::~Menu() {
    delete this->sound;
    delete this->buffer;
    delete this->bufferM;
    delete this->mainTheme;
}

void Menu::render() {

    this->window.draw(this->background);

    for (int i = 0; i < this->currentAmountOfItems; i++) {
        this->window.draw(this->menu[i]);
    }

}

void Menu::MoveUp() {

    if (this->selectedItemIndex - 1 >= 0) {
        this->menu[this->selectedItemIndex].setScale(1, 1);
        this->menu[this->selectedItemIndex].setFillColor(sf::Color::White);

        this->selectedItemIndex--;
        this->menu[this->selectedItemIndex].setFillColor(sf::Color::Red);

    }
}

void Menu::MoveDown() {

    if (this->selectedItemIndex + 1 < this->currentAmountOfItems) {
        this->menu[this->selectedItemIndex].setScale(1, 1);
        this->menu[this->selectedItemIndex].setFillColor(sf::Color::White);
        this->selectedItemIndex++;
        this->menu[this->selectedItemIndex].setFillColor(sf::Color::Red);

    }
}

void Menu::mainMenu() {


    this->currentMenu = 0;
    this->currentAmountOfItems = 2;
    this->selectedItemIndex = 0;

    this->menu[0].setFont(this->font);
    this->menu[0].setFillColor(sf::Color::Red);
    this->menu[0].setString("Play");
    this->menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));

    this->menu[1].setFont(this->font);
    this->menu[1].setFillColor(sf::Color::White);
    this->menu[1].setString("Exit");
    this->menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

}

void Menu::secondMenu() {
    this->currentMenu = 1;
    this->currentAmountOfItems = 4;
    this->selectedItemIndex = 0;

    this->menu[0].setFont(this->font);
    this->menu[0].setFillColor(sf::Color::Red);
    this->menu[0].setString("Start game");
    this->menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));

    this->menu[1].setFont(this->font);
    this->menu[1].setFillColor(sf::Color::White);
    this->menu[1].setString("Join game");
    this->menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

    this->menu[2].setFont(this->font);
    this->menu[2].setFillColor(sf::Color::White);
    this->menu[2].setString("Change Nickname");
    this->menu[2].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 3));

    this->menu[3].setFont(this->font);
    this->menu[3].setFillColor(sf::Color::White);
    this->menu[3].setString("Back");
    this->menu[3].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 4));
}

void Menu::nicknameMenu() {
    this->currentMenu = 2;
    this->currentAmountOfItems = 2;
    this->selectedItemIndex = 0;

    this->menu[0].setFont(this->font);
    this->menu[0].setFillColor(sf::Color::Red);
    this->menu[0].setString("Nickname: " + this->playerName);
    this->menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));

    this->menu[1].setFont(this->font);
    this->menu[1].setFillColor(sf::Color::White);
    this->menu[1].setString("Back");
    this->menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

}

void Menu::ipMenu() {

    this->currentMenu = 3;
    this->currentAmountOfItems = 3;
    this->selectedItemIndex = 0;

    this->menu[0].setFont(this->font);
    this->menu[0].setFillColor(sf::Color::Red);
    this->menu[0].setString("Server IP: " + this->serverIP);
    this->menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));

    this->menu[1].setFont(this->font);
    this->menu[1].setFillColor(sf::Color::White);
    this->menu[1].setString("Connect");
    this->menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

    this->menu[2].setFont(this->font);
    this->menu[2].setFillColor(sf::Color::White);
    this->menu[2].setString("Back");
    this->menu[2].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 3));
}


void Menu::serverStartMenu() {
    this->window.clear();

    this->currentMenu = 4;
    this->currentAmountOfItems = 1;
    this->selectedItemIndex = 0;

    this->menu[0].setFont(this->font);
    this->menu[0].setFillColor(sf::Color::White);
    this->menu[0].setString("Waiting for Client to connect...");
    this->menu[0].setPosition(sf::Vector2f(((float) this->window.getSize().x / 2) - (this->menu[0].getLocalBounds().width / 2),
                                     this->window.getSize().y / 2));
    this->menu[0].setScale(1, 1);

    this->window.draw(this->menu[0]);
    this->window.display();
}

void Menu::clientStartMenu() {
    this->window.clear();

    this->currentMenu = 5;
    this->currentAmountOfItems = 1;
    this->selectedItemIndex = 0;

    this->menu[0].setFont(this->font);
    this->menu[0].setFillColor(sf::Color::White);
    this->menu[0].setString("Waiting for Server to host game...");
    this->menu[0].setPosition(sf::Vector2f(((float) this->window.getSize().x / 2) - (this->menu[0].getLocalBounds().width / 2),
                                     this->window.getSize().y / 2));
    this->menu[0].setScale(1, 1);

    this->window.draw(this->menu[0]);
    this->window.display();
}

void Menu::revengeMenu() {

    this->currentMenu = 6;
    this->currentAmountOfItems = 3;
    this->selectedItemIndex = 1;

    /*sf::Text revText;

    revText.setFont(font);
    revText.setFillColor(sf::Color::White);
    revText.setString("Odveta ? ");
    revText.setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));
     */

    this->menu[0].setFont(this->font);
    this->menu[0].setFillColor(sf::Color::White);
    this->menu[0].setString("Odveta ? ");
    this->menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));

    this->menu[1].setFont(this->font);
    this->menu[1].setFillColor(sf::Color::Red);
    this->menu[1].setString("ANO");
    this->menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

    this->menu[2].setFont(this->font);
    this->menu[2].setFillColor(sf::Color::White);
    this->menu[2].setString("NIE");
    this->menu[2].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 3));
}


int Menu::GetCurrentMenu() {
    return this->currentMenu;
}

void Menu::playSound(sf::String string) {
    this->buffer->loadFromFile("../sounds/" + string);
    this->sound->setBuffer(*this->buffer);
    this->sound->setVolume(20.0f);
    this->sound->play();
}

void Menu::playMusic(sf::String string) {
    this->bufferM->loadFromFile("../sounds/" + string);
    this->mainTheme->setBuffer(*this->bufferM);
    this->mainTheme->setVolume(1.0f);
    this->mainTheme->play();
}

void Menu::pollEvents() {
    clearScale();
    while (this->window.pollEvent(event)) {

        switch (event.type) {
            case sf::Event::TextEntered:
                if (this->selectedItemIndex == 0 && GetCurrentMenu() == 2) {

                    if (event.text.unicode != 8) {
                        this->playerName += event.text.unicode;
                    } else {
                        this->playerName = this->playerName.substring(0, this->playerName.getSize() - 1);
                    }

                    this->menu[0].setString("Nickname: " + this->playerName);
                } else if (this->selectedItemIndex == 0 && GetCurrentMenu() == 3) {

                    if (event.text.unicode != 8) {
                        this->serverIP += event.text.unicode;
                    } else {
                        this->serverIP = this->serverIP.substring(0, this->serverIP.getSize() - 1);
                    }

                    this->menu[0].setString("Server IP: " + this->serverIP);
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        this->playSound("switch.ogg");
                        this->MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        this->playSound("switch.ogg");
                        this->MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (this->GetCurrentMenu()) {
                            case 0:
                                if (this->GetPressedItem() == 0) {
                                    this->playSound("select.ogg");
                                    this->secondMenu();
                                } else {
                                    this->window.close();
                                    break;
                                }
                                break;
                            case 1:
                                if (this->GetPressedItem() == 0) {
                                    this->playSound("select.ogg");
                                    this->playerType = 's';
                                    this->serverStartMenu();
                                    this->startGame(this->playerType, this->playerName, this->serverIP);
                                } else if (this->GetPressedItem() == 1) {
                                    this->playSound("select.ogg");
                                    this->ipMenu();
                                } else if (this->GetPressedItem() == 2) {
                                    this->playSound("select.ogg");
                                    this->nicknameMenu();
                                } else if (this->GetPressedItem() == 3) {
                                    this->playSound("select.ogg");
                                    this->mainMenu();
                                }
                                break;
                            case 2:
                                if (this->GetPressedItem() == 1) {
                                    this->playSound("select.ogg");
                                    this->secondMenu();
                                }
                                break;
                            case 3:
                                if (this->GetPressedItem() == 1) {
                                    this->playSound("select.ogg");
                                    this->playerType = 'c';
                                    this->clientStartMenu();
                                    this->startGame(this->playerType,this->playerName,this->serverIP);
                                } else if (this->GetPressedItem() == 2) {
                                    this->playSound("select.ogg");
                                    this->secondMenu();
                                }
                                break;
                            case 6:
                                if (this->GetPressedItem() == 2) {
                                    this->playSound("select.ogg");
                                    this->mainMenu();
                                } else if (this->GetPressedItem() == 1) {
                                    this->playSound("select.ogg");
                                    if (this->playerType == 'c') {
                                        this->clientStartMenu();
                                        this->startGame(this->playerType, this->playerName, this->serverIP);
                                    } else if (this->playerType == 's') {
                                        this->serverStartMenu();
                                        this->startGame(this->playerType, this->playerName, this->serverIP);
                                    } else {
                                        std::cout << "Invalid player type" << std::endl;
                                        this->window.close();
                                    }
                                }
                                break;
                        }
                        break;
                }
                break;
            case sf::Event::Closed:
                this->window.close();
                break;
        }
    }
}

void Menu::startGame(char type, sf::String playerName, sf::String serverIP) {

    Game game(this->window);

    game.setPlayerName(playerName);
    game.setPlayerType(type, serverIP);

    this->mainTheme->stop();

    game.init();

    while (game.running() && !game.isEndGame()) {
        game.update();
        game.render();
        game.pollEvents();
    }

    sf::sleep(sf::seconds(3));
    this->revengeMenu();
}

void Menu::renderWindow() {
    this->window.clear();
    this->render();
    this->window.display();
}

void Menu::clearScale() {
    for (int i = 0; i < 10; ++i) {
        this->menu[i].setScale(1, 1);
    }
    this->menu[selectedItemIndex].setScale(2, 2);
}