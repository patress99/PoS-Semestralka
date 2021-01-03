
#include <iostream>
#include "Game.h"
#include "Menu.h"

void startGame() {
    Game game;
    game.start();


    while (game.running() && !game.getEndGame())
    {

        game.update();
        game.render();
    }
}

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));
    sf::RenderWindow window(sf::VideoMode(600, 600), "Mlaticka_menu");
    Menu menu;
    menu.mainMenu(window.getSize().x, window.getSize().y);




    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up:
                            menu.MoveUp();
                            break;

                        case sf::Keyboard::Down:
                            menu.MoveDown();
                            break;

                        case sf::Keyboard::Return:
                            switch (menu.GetPressedItem())
                            {

                                case 0:
                                    if (menu.GetCurrentMenu() == 0) {
                                        menu.secondMenu(window.getSize().x, window.getSize().y, event);
                                    } else {
                                        startGame();
                                    }

                                    break;
                                case 1:
                                    if (menu.GetCurrentMenu() == 0) {
                                        window.close();
                                    } else {
                                        menu.mainMenu(window.getSize().x, window.getSize().y);
                                    }

                                    break;
                            }

                            break;
                    }

                    break;
                case sf::Event::Closed:
                    window.close();

                    break;

            }
        }

        window.clear();

        menu.draw(window);

        window.display();
    }







    return 0;
}