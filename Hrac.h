#include <SFML/Graphics.hpp>

class Hrac {

private:
    int health;
    sf::Sprite sprite;
public:
    ~Hrac();
    Hrac(sf::Texture& texture, float spawnX, float spawnY);
    void setHealth(int health);
    int getHealth();
    sf::Sprite getSprite();
};
