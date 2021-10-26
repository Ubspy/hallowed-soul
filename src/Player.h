#pragma once

#include "Entity.h"
#include <math.h>

enum MoveState
{
    Moving, Dodging, None
};

class Player : public Entity
{
    public:
        Player();

        // Tells the player which direction it needs to be moving 
        void moveInDirection(sf::Vector2<float> moveDir);

        // Tells the player which direction it needs to be dodging
        void dodgeInDirection(sf::Vector2<float> dodgeDir);

        // Tells the player it needs to be attacking 
        void attack();

        // Tells the player it needs to be countering
        void counter();

    private:
        const float _moveSpeed = 500;
        MoveState _currentMoveState;

        // Current direction to move in based off given user input
        sf::Vector2<float> _moveVec;

        // Function to call once every frame
        void onUpdate(float deltaTime);

        // Function to handle collision with other entities
        void onCollision(Entity &hitEntity); 
};
