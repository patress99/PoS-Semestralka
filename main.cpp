
#include <iostream>
#include "Game.h"

//using namespace sf;

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    Game game;

    while (game.running() && !game.getEndGame())
    {
        game.update();

        game.render();
    }

    return 0;
}