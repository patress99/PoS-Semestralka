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

    sf::Texture muteTex;
    sf::Sprite muteIcon;

    sf::Packet packet;

    sf::TcpSocket socket;
    sf::TcpListener listener;
    sf::Thread *packetThread;
    sf::Thread *animThread;
    sf::Mutex mutex;

    unsigned short port;


    Player *winner;

    Player *player;
    sf::RectangleShape playerHealthBar;
    sf::RectangleShape playerHealthBarBack;
    sf::Text playerName;

    bool playerAttacked = false;
    bool playerBlocked = false;
    bool playerCritical = false;

    Player *enemy;
    sf::RectangleShape enemyHealthBar;
    sf::RectangleShape enemyHealthBarBack;
    bool enemyBlocked = false;
    sf::Text enemyName;

    char playerType;

    bool playable;
    sf::SoundBuffer* buffer;
    sf::SoundBuffer* bufferM;
    sf::Sound* sound;
    sf::Sound* battleMusic;

    int musicCooldown;

    bool endGame;

    void initVariables();


public:
    Game(sf::RenderWindow& wind);

    ~Game();

    const bool running() const;

    const bool isEndGame() const;

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

    void renderGui();

    void initGUI();

    void playSound(sf::String string);

    void init();

    void serverSide();

    bool clientSide(sf::String ip);

    void thUpdateOnlineGame();

    void thAnimate();

    void setPlayerType(char type);

    void setPlayerName(sf::String string);

    void acceptClient();

    void playMusic(sf::String string);

    Player* getWinner();

    bool musCooldown();

    void terminateThreads();

    bool connect(sf::String ip);

};