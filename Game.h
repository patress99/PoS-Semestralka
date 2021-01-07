#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Game {
private:

    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event ev;

    sf::Font gameFont;

    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;

    sf::Texture grassTex;
    sf::Sprite grass;


    sf::Packet packet;
    sf::TcpSocket socket;
    sf::TcpListener listener;

    sf::Mutex mutex;

    //sf::UdpSocket socket;
    sf::IpAddress ip;
    unsigned short port;

    sf::IpAddress rIp;
    unsigned short rPort;

    Player *winner;

    Player *hrac1;
    sf::RectangleShape player1HealthBar;
    sf::RectangleShape player1HealthBarBack;
    sf::Text player1Name;
    sf::String playerName;
    bool player1Attacked;

    Player *hrac2;
    sf::RectangleShape player2HealthBar;
    sf::RectangleShape player2HealthBarBack;
    sf::Text player2Name;
    bool player2Attacked;

    char playerType;

    bool playable;
    sf::SoundBuffer* buffer;
    sf::Sound* sound;

    bool endGame;

    void initVariables();

    void initWindow();



public:
    Game();

    ~Game();

    const bool running() const;

    const bool isEndGame() const;

    void setPlayerType(char type, sf::String ip);

    void initPlayers();

    void pollEvents();

    void update();

    void render();

    void renderPlayers();

    void renderWorld();

    void renderEnd();

    void updateInput();

    void updateCollision();

    void updatePlayers();

    void updateGUI();

    sf::RenderWindow* getWindow();

    void renderGui();

    void initGUI();

    void playSound(sf::String string);

    void init();

    void serverSide();

    void clientSide(sf::String ip);

    void thUpdateOnlineGame();

    void thAnimate();

    void setPlayerName(sf::String string);

    void acceptClient();
};