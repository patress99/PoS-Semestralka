#include "Menu.h"


Menu::Menu()
{
    this->buffer = new sf::SoundBuffer();
    this->sound = new sf::Sound();
}


Menu::~Menu()
{
    delete this->buffer;
    delete this->sound;
}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{

    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown()
{

    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::mainMenu(float width, float height) {
    if (!font.loadFromFile("../fonts/aAsianNinja.ttf"))
    {
        // handle error
    }

    this->currentMenu = 0;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(10.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Exit");
    menu[1].setPosition(sf::Vector2f(10.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    selectedItemIndex = 0;
}

void Menu::secondMenu(float width, float height, sf::Event event) {
    sf::String playerInput;
    sf::Text playerText;
    if (!font.loadFromFile("../fonts/aAsianNinja.ttf"))
    {
        // handle error
    }

    this->currentMenu = 1;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Start game");
    menu[0].setPosition(sf::Vector2f(10.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    playerInput += event.text.unicode;
    playerText.setString(playerInput);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Back");
    menu[1].setPosition(sf::Vector2f(10.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

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

