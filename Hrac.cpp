#include <iostream>
#include "Hrac.h"

Hrac::~Hrac() {

}

Hrac::Hrac(int player, std::string name, float spawnX, float spawnY) {

    this->name = name;
    this->maxHealth = 100;
    this->health = this->maxHealth;
    this->movementSpeed = 5.f;
    this->attackCooldownMax = 30.f;
    this->attackCooldown = this->attackCooldownMax;
    this->player = player;
    if (this->player == 1) {
        if (!texture.loadFromFile("../assets/hrac1.png")) {
            std::cout << "Could not load player1 texture" << std::endl;
            exit(2);
        }
    } else if (this->player == 2) {
        if (!texture.loadFromFile("../assets/hrac2.png")) {
            std::cout << "Could not load player2 texture" << std::endl;
            exit(2);
        }
    }

    this->sprite.setTexture(texture);
    this->sprite.setPosition(spawnX, spawnY);

}

const bool Hrac::canAttack() {
    if (this->attackCooldown >= this->attackCooldownMax) {
        this->attackCooldown = 0.f;
        return true;
    }

    return false;
}

void Hrac::move(const float dirX, const float dirY) {
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Hrac::loseHp(const int value) {
    this->health -= value;
    if (this->health < 0)
        this->health = 0;
}

void Hrac::setPosition(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

void Hrac::setPosition(const sf::Vector2f pos) {
    this->sprite.setPosition(pos);
}

const sf::FloatRect Hrac::getBounds() const {
    return this->sprite.getGlobalBounds();
}

const sf::Vector2f &Hrac::getPos() const {
    return this->sprite.getPosition();
}


void Hrac::updateAttack() {
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.5f;
}

void Hrac::update() {
    this->updateAttack();
}

void Hrac::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

const int Hrac::getHealth() const {
    return this->health;
}

const int Hrac::getMaxHealth() const {
    return this->maxHealth;
}

void Hrac::setHealth(const int health) {
    this->health = health;
}

const std::string Hrac::getName() const {
    return this->name;
}

void Hrac::updateTexture(sf::String string) {
    if (this->player == 1) {
        if (!texture.loadFromFile("../assets/" + string)) {
            std::cout << "Could not load player1 texture" << std::endl;
            exit(2);
        }
    } else if (this->player == 2) {
        if (!texture.loadFromFile("../assets/" + string)) {
            std::cout << "Could not load player2 texture" << std::endl;
            exit(2);
        }
    }

    this->sprite.setTexture(texture,true);

}