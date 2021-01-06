#include <iostream>
#include "Player.h"

Player::~Player() {

}

Player::Player(int player, std::string name, float spawnX, float spawnY) {

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

const bool Player::canAttack() {
    if (this->attackCooldown >= this->attackCooldownMax) {
        this->attackCooldown = 0.f;
        return true;
    }

    return false;
}

void Player::move(const float dirX, const float dirY) {
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::loseHp(const int value) {
    this->health -= value;
    if (this->health < 0)
        this->health = 0;
}

void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

void Player::setPosition(const sf::Vector2f pos) {
    this->sprite.setPosition(pos);
}

const sf::FloatRect Player::getBounds() const {
    return this->sprite.getGlobalBounds();
}

const sf::Vector2f &Player::getPos() const {
    return this->sprite.getPosition();
}


void Player::updateAttack() {
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.5f;
}

void Player::update() {
    this->updateAttack();
}

void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

const int Player::getHealth() const {
    return this->health;
}

const int Player::getMaxHealth() const {
    return this->maxHealth;
}

void Player::setHealth(const int health) {
    this->health = health;
}

const std::string Player::getName() const {
    return this->name;
}

void Player::updateTexture(sf::String string) {
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