#include "Menu.h"
#include "Game.h"


Menu::Menu() {

    this->window = new sf::RenderWindow(sf::VideoMode(600, 600), "Mlaticka");

    sf::Image image;

    if (!image.loadFromFile("../assets/mlaticka.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD ICON" << "\n";
        exit(1);
    }

    this->window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    this->buffer = new sf::SoundBuffer();
    this->bufferM = new sf::SoundBuffer();
    this->sound = new sf::Sound();
    this->mainTheme = new sf::Sound();

    playMusic("mlatC.ogg");

    if (!this->backgroundTex.loadFromFile("../assets/mlaticka.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
        exit(1);
    }

    this->background.setTexture(this->backgroundTex);
    this->background.scale(0.95f, 0.66f);

    this->mainMenu();

    while (this->window->isOpen()) {
        this->pollEvents();
        this->renderWindow();
    }
}


Menu::~Menu() {
    delete this->window;
    delete this->sound;
    delete this->buffer;
    delete this->bufferM;
    delete this->mainTheme;

}

void Menu::render() {

    this->window->draw(this->background);

    for (int i = 0; i < currentAmountOfItems; i++) {
        this->window->draw(menu[i]);
    }

}

void Menu::MoveUp() {

    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown() {

    if (selectedItemIndex + 1 < currentAmountOfItems) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::mainMenu() {

    if (!font.loadFromFile("../fonts/aAsianNinja.ttf")) {
        // handle error
    }

    this->currentAmountOfItems = 2;

    this->currentMenu = 0;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(10.f, 100 * 1));


    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Exit");
    menu[1].setPosition(sf::Vector2f(10.f, 100 * 2));

    selectedItemIndex = 0;
}

void Menu::secondMenu() {
    if (!font.loadFromFile("../fonts/aAsianNinja.ttf")) {
        // handle error
    }

    this->currentMenu = 1;
    this->currentAmountOfItems = 3;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Start game");
    menu[0].setPosition(sf::Vector2f(10.f, 100 * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Back");
    menu[1].setPosition(sf::Vector2f(10.f, 100 * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Join");
    menu[2].setPosition(sf::Vector2f(10.f, 100 * 3));


    selectedItemIndex = 0;
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

    sf::Event event;
    while (this->window->pollEvent(event)) {
        switch (event.type) {
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
                        switch (this->GetPressedItem()) {
                            case 0:
                                this->playSound("select.ogg");
                                if (this->GetCurrentMenu() == 0) {
                                    this->secondMenu();
                                } else {
                                    this->window->close();
                                    this->startGame('s');
                                }
                                break;
                            case 1:
                                this->playSound("select.ogg");
                                if (this->GetCurrentMenu() == 0) {
                                    this->window->close();
                                } else {
                                    this->mainMenu();
                                }

                                break;
                            case 2:
                                this->playSound("select.ogg");
                                if (this->GetCurrentMenu() == 0) {
                                    this->window->close();
                                } else {
                                    this->window->close();
                                    startGame('c');
                                }
                                break;
                        }
                        break;
                }
                break;
            case sf::Event::Closed:
                this->window->close();
                break;
        }
    }
}

void Menu::startGame(char type) {

    Game game;

    char odveta = 'Y';

    game.setPlayerType(type);


    while ((odveta == 'Y' || odveta == 'y')) {
        game.init();
        game.playSound("start.ogg");
        while (!game.isEndGame()) {

            game.update();
            game.pollEvents();
            game.render();

        }
        std::cout << "Chces odvetu? Y | N" << std::endl;
        std::cin >> odveta;
        std::cout << odveta << std::endl;

        game.getWindow()->close();
    }
}

void Menu::renderWindow() {
    this->window->clear();
    this->render();
    this->window->display();
}
