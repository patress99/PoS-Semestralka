#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>


class Menu
{
private:

    sf::RenderWindow* window;

    sf::String playerName;
    sf::String hostIP;

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
    void secondMenu();
    void render();

    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    int GetCurrentMenu();

private:
    void pollEvents();
    void startGame(char type);
    void playSound(sf::String string);
    void playMusic(sf::String string);

    void renderWindow();
};