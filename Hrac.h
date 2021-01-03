#include <SFML/Graphics.hpp>

class Hrac {

private:
    float positionX;
    float positionY;
    int health;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    ~Hrac();
    Hrac(float spawnX, float spawnY);
    void setHealth(int health);
    const int getHealth();
    void moveRight();
    void moveLeft();
    void jump();
    const float getPositionX();
    const float getPositionY();
    void setPositionX(float pos);
    void setPositionY(float pos);
    sf::Sprite& getSprite();
};
