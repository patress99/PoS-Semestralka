#include <iostream>
#include "Hrac.h"


sf::Sprite Hrac::getSprite() {
    return this->sprite;
}

void Hrac::setHealth(int health) {
    this->health = health;
}

int Hrac::getHealth() {
    return this->health;
}

Hrac::~Hrac() {

}

Hrac::Hrac(float spawnX, float spawnY) {
    this->health = 100;

    sf::Texture texture;

    if (!texture.loadFromFile("assets/hrac.png")) {
        std::cout << "Could not load player texture" << std::endl;
    }

    this->sprite.setTexture(texture);
    this->sprite.setPosition(spawnX,spawnY);

}
