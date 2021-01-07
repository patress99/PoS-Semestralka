#include <SFML/Graphics.hpp>
#include <string>

class Player {

private:
    std::string name;
    float movementSpeed;
    int player;

    float attackCooldown;
    float attackCooldownMax;

    int health;
    int maxHealth;

    bool connected;

    sf::Sprite sprite;
    sf::Texture texture;

public:

    ~Player();
    Player(int player, std::string name, float spawnX, float spawnY);

    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;

    const int getHealth() const;
    const int getMaxHealth() const;
    bool isConnected() const;

    const std::string getName() const;
    void setConnected(bool connected);
    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);
    void setHealth(const int hp);
    void loseHp(const int value);

    void move(const float dirX, const float dirY);
    const bool canAttack();

    void updateTexture(sf::String string);

    void setAttackCooldown();
    void updateAttack();
    void update();

    sf::Sprite getSprite();

};