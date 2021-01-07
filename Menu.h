#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>


class Menu
{
private:
    int currentMenu;
    int selectedItemIndex;
    int currentAmountOfItems;

    //Sound
    sf::SoundBuffer* buffer;
    sf::SoundBuffer* bufferM;
    sf::Sound* sound;
    sf::Sound* mainTheme;

    //Background
    sf::Texture backgroundTex;
    sf::Sprite background;

    sf::Font font;
    sf::Text menu[10];

public:
    Menu();
    ~Menu();

    void mainMenu();
    void secondMenu(sf::Event event);
    void draw(sf::RenderWindow &window);

    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    int GetCurrentMenu();

    void playSound(sf::String string);

    void playMusic(sf::String string);
};