#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 2



class Menu
{
private:
    int currentMenu;
    int selectedItemIndex;

    //Sound
    sf::SoundBuffer* buffer;
    sf::SoundBuffer* bufferM;
    sf::Sound* sound;
    sf::Sound* mainTheme;

    //Background
    sf::Texture backgroundTex;
    sf::Sprite background;

    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

public:
    Menu();
    ~Menu();

    void mainMenu(float width, float height);
    void secondMenu(float width, float height, sf::Event event);
    void draw(sf::RenderWindow &window);

    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    int GetCurrentMenu();

    void playSound(sf::String string);

    void playMusic(sf::String string);
};