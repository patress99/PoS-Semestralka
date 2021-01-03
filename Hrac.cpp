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

Hrac::Hrac(sf::Texture& texture, float spawnX, float spawnY) {
    this->health = 100;
    texture.loadFromImage("imgs/hrac.png");
    this->sprite.setTexture(texture, true);
    this->sprite.setPosition(spawnX,spawnY);

}
