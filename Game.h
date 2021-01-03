#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include "Hrac.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game {
private:
    //Okno + riadenie
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event ev;

    sf::Font gameFont;

    //BG
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;

    //Hraci
    Hrac *winner;

    Hrac *hrac1;
    sf::RectangleShape player1HealthBar;
    sf::RectangleShape player1HealthBarBack;
    sf::Text player1Name;

    Hrac *hrac2;
    sf::RectangleShape player2HealthBar;
    sf::RectangleShape player2HealthBarBack;
    sf::Text player2Name;

    //Game logic
    bool endGame;

    //Inicializacie
    void initVariables();

    void initWindow();

    void initPlayers();

public:
    Game();

    ~Game();

    const bool running() const;

    const bool getEndGame() const;

    void pollEvents();

    void update();

    void render();

    void renderPlayers();

    void renderWorld();

    void updateInput();

    void updateCollision();

    void updatePlayers();

    void updateGUI();

    void renderGui();

    void initGUI();

    void start();
};