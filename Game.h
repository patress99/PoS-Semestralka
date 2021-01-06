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

    //Grass
    sf::Texture grassTex;
    sf::Sprite grass;

    //Socket
    //sf::TcpSocket socket;
    sf::UdpSocket socket;
    sf::TcpListener listener;
    sf::IpAddress ip;
    unsigned short port;

    sf::IpAddress rIp;
    unsigned short rPort;

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

    bool playable;

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

    void init();

    Hrac getPlayer();

    void serverSide();

    void clientSide();

    void testMessage();
};