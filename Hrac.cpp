#include <iostream>
#include "Hrac.h"


sf::Sprite& Hrac::getSprite() {
    return this->sprite;
}


void Hrac::setHealth(int health) {
    this->health = health;
}

const int Hrac::getHealth() {
    return this->health;
}

Hrac::~Hrac() {

}

Hrac::Hrac(float spawnX, float spawnY) {
    this->health = 100;
    if (!texture.loadFromFile("F:\\skola\\vysoka\\3rocnik\\CLionProjects\\PoS-Semestralka\\PoS-Semestralka\\imgs\\hrac1.png")) {
        std::cout << "Could not load player texture" << std::endl;
    }


    this->sprite.setTexture(texture);
    this->sprite.setPosition(spawnX,spawnY);

}