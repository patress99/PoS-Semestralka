#include "Game.h"

//Private functions
void Game::initVariables()
{
    this->window = nullptr;

    //Game logic
    this->endGame = false;
}

void Game::initWindow()
{
    this->videoMode.height = 900;
    this->videoMode.width = 1600;

    this->window = new sf::RenderWindow(this->videoMode, "Mlaticka", sf::Style::Titlebar | sf::Style::Close);
    window.

    this->window->setFramerateLimit(60);
}

void Game::initPlayers() {
    this->hrac1 = new Hrac(50,50);
    this->hrac2 = new Hrac(200,50);
}

void Game::initText()
{
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("TEST");
}

//Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initText();
    this->initPlayers();
}

Game::~Game()
{
    delete this->window;
}

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

void Game::pollEvents()
{
    //Event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::update()
{
    this->pollEvents();

    if (this->endGame == false)
    {
        //own logic
    }

    //End game condition
    //TODO: Hrac1 / Hrac 2 zomrel
}


void Game::renderPlayers(sf::RenderTarget& target)
{
    target.draw(hrac1->getSprite());
    target.draw(hrac2->getSprite());
}

void Game::render()
{
    /**
        @return void
        - clear old frame
        - render objects
        - display frame in window
        Renders the game objects.
    */

    this->window->clear();

    this->renderPlayers(*this->window);

    this->window->display();
}

