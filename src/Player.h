#include "Entity.h"
#include <math.h>

class Player : public Entity
{
    public:
        Player();

        void moveInDirection(sf::Vector2<float> moveDir);
        void dodgeInDirection(sf::Vector2<float> dodgeDir);
        void attack();
        void counter();

    private:
        float _moveSpeed = 10;
};
