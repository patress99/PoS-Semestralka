#include <SFML/Graphics.hpp>

class Hrac {

private:
    int health;
    sf::Sprite* sprite;
    sf::Texture* texture;
public:
    ~Hrac();
    Hrac(float spawnX, float spawnY);
    void setHealth(int health);
    const int getHealth();
    sf::Sprite& getSprite();
};
