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
    sf::Image image;
    image.loadFromFile(R"(imgs\hrac.png)");
    texture.update(image);
    this->sprite.setTexture(texture);
    this->sprite.setPosition(spawnX,spawnY);
}
