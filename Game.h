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

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
    //Variables
    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    //Text
    sf::Text uiText;

    //Background
    sf::Texture backGround;
    //Game logic
    bool endGame;

    //Game objects

    Hrac* hrac1;
    Hrac* hrac2;

    //Private functions
    void initVariables();
    void initWindow();
    void initText();
    void initPlayers();

public:
    //Constructors / Destructors
    Game();
    ~Game();

    //Accessors
    const bool running() const;
    const bool getEndGame() const;

    void pollEvents();

    void update();

    void render();

    void renderPlayers(sf::RenderTarget &target);
};