#pragma once

#include "Entity.h"
#include <math.h>
#include <stdlib.h>

enum MoveState
{
    Moving, Dodging, None
};

class Player : public Entity
{
    public:
        Player();

        void moveInDirection(sf::Vector2<float> moveDir);
        void dodgeInDirection(sf::Vector2<float> dodgeDir);
        void attack();
        void counter();

    private:
        const float _moveSpeed = 1;
        MoveState _currentMoveState;

        sf::Vector2<int> _moveVec;

        void onUpdate();
        void onCollision(Entity &hitEntity); 
};
