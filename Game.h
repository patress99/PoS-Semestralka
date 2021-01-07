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

    sf::RenderWindow& window;
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

    Player *player;
    sf::RectangleShape playerHealthBar;
    sf::RectangleShape playerHealthBarBack;
    sf::Text playerName;
    bool playerAttacked;

    Player *enemy;
    sf::RectangleShape enemyHealthBar;
    sf::RectangleShape enemyHealthBarBack;
    sf::Text enemyName;

    char playerType;

    bool playable;
    sf::SoundBuffer* buffer;
    sf::SoundBuffer* bufferM;
    sf::Sound* sound;
    sf::Sound* battleMusic;

    bool endGame;

    void initVariables();


public:
    Game(sf::RenderWindow& wind);

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

    sf::RenderWindow& getWindow();

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

    void playMusic(sf::String string);
};