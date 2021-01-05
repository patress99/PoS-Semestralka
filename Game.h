#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include "Hrac.h"
#include "Server.h"
#include "Client.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

const int PORT = 10022;

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

    //Grass
    sf::Texture grassTex;
    sf::Sprite grass;

    //Socket
    sf::TcpSocket* socket;

    //Client/Server
    Server* server;
    Client* client;


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

    //Player type
    char playerType;



    //Sound
    sf::SoundBuffer* buffer;
    sf::Sound* sound;


    //Game logic
    bool endGame;

    //Inicializacie
    void initVariables();

    void initWindow();



public:
    Game();

    ~Game();

    const bool running() const;

    const bool getEndGame() const;

    void setPlayerType(char type);

    void initPlayers();

    char getPlayerType();

    void pollEvents();

    void update();

    void render();

    void renderPlayers();

    void renderWorld();

    void renderEnd();

    void updateInput();

    void updateOnlineGame(sf::Vector2f pos);

    void updateCollision();

    void updatePlayers();

    void updateGUI();

    void renderGui();

    void initGUI();

    void playSound(sf::String string);

    void isGameReady();

    Hrac getPlayer();
};