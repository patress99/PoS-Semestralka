#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 2



class Menu
{
public:
    Menu();
    ~Menu();

    void mainMenu(float width, float height);
    void secondMenu(float width, float height, sf::Event event);
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    int GetCurrentMenu();

private:
    int currentMenu;
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

};