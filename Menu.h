#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>


class Menu
{
private:
    sf::Event event;
    sf::RenderWindow window;
    sf::VideoMode videoMode;

    sf::String playerName;
    sf::String serverIP;

    int currentMenu;
    int selectedItemIndex;
    int currentAmountOfItems;

    float offsetX;
    float offsetY;


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

    void render();

    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    int GetCurrentMenu();

private:
    void pollEvents();
    void startGame(char type, sf::String playerName, sf::String serverIP);
    void playSound(sf::String string);
    void playMusic(sf::String string);

    void renderWindow();

    void mainMenu();
    void secondMenu();
    void nicknameMenu();
    void ipMenu();

    void clientStartMenu();

    void serverStartMenu();

    void revengeMenu();

    void clearScale();
};