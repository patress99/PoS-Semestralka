
#include <iostream>
#include "Game.h"
#include "Menu.h"

void startGame(char type) {

    Game game;


    char odveta = 'Y';

    game.setPlayerType(type);


    while ((odveta == 'Y' || odveta == 'y') ) {
        game.init();
        game.playSound("start.ogg");
        while (!game.getEndGame() )
        {
            game.update();
            game.pollEvents();
            game.render();
        }
        std::cout << "Chces odvetu? Y | N" << std::endl;
        std::cin >> odveta;
        std::cout << odveta << std::endl;

        game.getWindow()->close();
    }





}

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    sf::RenderWindow window(sf::VideoMode(600, 600), "Mlaticka");

    sf::Image image;

    if (!image.loadFromFile("../assets/mlaticka.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD ICON" << "\n";
        exit(1);
    }


    window.setIcon(image.getSize().x,image.getSize().y,image.getPixelsPtr());
    Menu menu;
    menu.mainMenu();

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
                            menu.playSound("switch.ogg");
                            menu.MoveUp();
                            break;

                        case sf::Keyboard::Down:
                            menu.playSound("switch.ogg");
                            menu.MoveDown();
                            break;

                        case sf::Keyboard::Return:
                            switch (menu.GetPressedItem())
                            {

                                case 0:
                                    menu.playSound("select.ogg");
                                    if (menu.GetCurrentMenu() == 0) {
                                        menu.secondMenu(event);
                                    } else {
                                        window.close();
                                        startGame('s');

                                    }

                                    break;
                                case 1:
                                    menu.playSound("select.ogg");
                                    if (menu.GetCurrentMenu() == 0) {
                                        window.close();
                                    } else {
                                        menu.mainMenu();
                                    }

                                    break;
                                case 2:
                                    menu.playSound("select.ogg");
                                    if (menu.GetCurrentMenu() == 0) {
                                        window.close();
                                    } else {
                                        window.close();
                                        startGame('c');
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



