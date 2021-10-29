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
        const float _moveSpeed = 350;
        const float _dodgeSpeed = 1100;
        const float _friction = 8;
        const float _dodgeFriction = 5;
        const float _deadZone = 0.01;

        MoveState _currentMoveState;

        // Current direction to move in based off given user input
        sf::Vector2<float> _moveVec;

        // Current direction player is dodging in, as well as the speed of the dodge
        sf::Vector2<float> _dodgeVec;

        // Function to call once every frame
        void onUpdate(float deltaTime, sf::Vector2<float> player);

        // Function to handle collision with other entities
        void onCollision(Entity &hitEntity); 

        // Handles slowing down when player isn't moving in a particular direction
        float checkDeadMoveAxis(float axis, float moveAxis, float friction);

        sf::Vector2<float> getUnitVector(sf::Vector2<float> vec);
};
