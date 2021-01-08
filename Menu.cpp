#include "Menu.h"
#include "Game.h"


Menu::Menu() {

    playerName = "Player";
    serverIP = "localhost";

    this->offsetX = 40.f;
    this->offsetY = 100.f;
    this->playerType = 'x';

    this->videoMode.height = 900;
    this->videoMode.width = 1600;

    if (!font.loadFromFile("../fonts/aAsianNinja.ttf")) {
        // handle error
    }


    if (!this->backgroundTex.loadFromFile("../assets/mlaticka.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
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

    playMusic("mlatC.ogg");


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

    for (int i = 0; i < currentAmountOfItems; i++) {
        this->window.draw(menu[i]);
    }

}

void Menu::MoveUp() {

    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setScale(1, 1);
        menu[selectedItemIndex].setFillColor(sf::Color::White);

        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);

    }
}

void Menu::MoveDown() {

    if (selectedItemIndex + 1 < currentAmountOfItems) {
        menu[selectedItemIndex].setScale(1, 1);
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);

    }
}

void Menu::mainMenu() {


    this->currentMenu = 0;
    this->currentAmountOfItems = 2;
    this->selectedItemIndex = 0;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));


    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Exit");
    menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

}

void Menu::secondMenu() {
    this->currentMenu = 1;
    this->currentAmountOfItems = 4;
    this->selectedItemIndex = 0;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Start game");
    menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Join game");
    menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Change Nickname");
    menu[2].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 3));

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Back");
    menu[3].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 4));
}

void Menu::nicknameMenu() {
    this->currentMenu = 2;
    this->currentAmountOfItems = 2;
    this->selectedItemIndex = 0;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Nickname: " + playerName);
    menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Back");
    menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

}

void Menu::ipMenu() {

    this->currentMenu = 3;
    this->currentAmountOfItems = 3;
    this->selectedItemIndex = 0;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Server IP: " + serverIP);
    menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Connect");
    menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Back");
    menu[2].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 3));
}


void Menu::serverStartMenu() {
    this->playerType = 's';
    window.clear();

    this->currentMenu = 4;
    this->currentAmountOfItems = 1;
    this->selectedItemIndex = 0;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Waiting for Client to connect...");
    menu[0].setPosition(sf::Vector2f(((float) this->window.getSize().x / 2) - (menu[0].getLocalBounds().width / 2),
                                     this->window.getSize().y / 2));
    menu[0].setScale(1, 1);

    window.draw(menu[0]);
    window.display();

    this->startGame('s', playerName, serverIP);
}

void Menu::clientStartMenu() {
    this->playerType = 'c';

    window.clear();

    this->currentMenu = 5;
    this->currentAmountOfItems = 1;
    this->selectedItemIndex = 0;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Waiting for Server to host game...");
    menu[0].setPosition(sf::Vector2f(((float) this->window.getSize().x / 2) - (menu[0].getLocalBounds().width / 2),
                                     this->window.getSize().y / 2));
    menu[0].setScale(1, 1);

    window.draw(menu[0]);
    window.display();

    this->startGame('c', playerName, serverIP);
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

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Odveta ? ");
    menu[0].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Red);
    menu[1].setString("ANO");
    menu[1].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("NIE");
    menu[2].setPosition(sf::Vector2f(this->offsetX, this->offsetY * 3));
}


int Menu::GetCurrentMenu() {
    return this->currentMenu;
}

void Menu::playSound(sf::String string) {
    buffer->loadFromFile("../sounds/" + string);
    sound->setBuffer(*buffer);
    sound->setVolume(20.0f);
    sound->play();
}

void Menu::playMusic(sf::String string) {
    bufferM->loadFromFile("../sounds/" + string);
    mainTheme->setBuffer(*bufferM);
    mainTheme->setVolume(1.0f);
    mainTheme->play();
}

void Menu::pollEvents() {
    clearScale();
    while (this->window.pollEvent(event)) {

        switch (event.type) {
            case sf::Event::TextEntered:
                if (selectedItemIndex == 0 && GetCurrentMenu() == 2) {

                    if (event.text.unicode != 8) {
                        playerName += event.text.unicode;
                    } else {
                        playerName = playerName.substring(0, playerName.getSize() - 1);
                    }

                    menu[0].setString("Nickname: " + playerName);
                } else if (selectedItemIndex == 0 && GetCurrentMenu() == 3) {

                    if (event.text.unicode != 8) {
                        serverIP += event.text.unicode;
                    } else {
                        serverIP = serverIP.substring(0, serverIP.getSize() - 1);
                    }

                    menu[0].setString("Server IP: " + serverIP);
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
                                    this->serverStartMenu();
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
                                    this->clientStartMenu();
                                } else if (this->GetPressedItem() == 2) {
                                    this->playSound("select.ogg");
                                    this->secondMenu();
                                }
                                break;
                            case 6:
                                if (this->GetPressedItem() == 2) {
                                    this->playSound("select.ogg");
                                    this->window.close();
                                } else if (this->GetPressedItem() == 1) {
                                    this->playSound("select.ogg");
                                    if (this->playerType == 'c') {
                                        this->clientStartMenu();
                                    } else if (this->playerType == 's') {
                                        this->serverStartMenu();
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

    mainTheme->stop();

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
        menu[i].setScale(1, 1);
    }
    menu[selectedItemIndex].setScale(2, 2);
}