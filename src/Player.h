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

        /**
         * @brief Tells the player which direction it needs to be moving 
         *
         * @param moveDir The direction from either the controller, or a keyboard input
         *  these will be added later
         */
        void moveInDirection(sf::Vector2<float> moveDir);

        /**
         * @brief Tells the player which direction it needs to be dodging
         *
         * @param dodgeDir Pretty sure we don't need the direction, to be removed
         */
        void dodgeInDirection(sf::Vector2<float> dodgeDir);

        /**
         * @brief Tells the player it needs to be attacking 
         */
        void attack();

        /**
         * @brief Tells the player it needs to be countering
         */
        void counter();

        /**
         * @brief updates health upon being attacked
         * 
         * @param damage the amount of health to be removed
         */
        void getAttacked(int damage);

        /**
         * @brief checks if player is dodging
         * 
         * @return true if dodging
         */
        bool isDodging();

    private:
        // Constants for player movement
        const float _moveSpeed = 350;
        const float _dodgeSpeed = 1100;
        const float _friction = 1600;
        const float _dodgeFriction = 6000;
        const float _deadZone = 0.01;

        // TODO: Unsure if this is needed
        MoveState _currentMoveState;

        // Current direction to move in based off given user input
        sf::Vector2<float> _moveVec;
        sf::Vector2<float> _lastMoveVec;

        // Current direction player is dodging in, as well as the speed of the dodge
        sf::Vector2<float> _dodgeVec;

        /**
         * @brief Overrided function from Entity, auto called from GameManager
         *  Used to update the entity based off user input
         *
         * @param deltaTime Time between last update and this one
         */
        void onUpdate(float deltaTime);

        /**
         * @brief Overrided function from Entity, auto called from GameManager
         *  Used to handle collisions
         *
         * @param hitEntity
         */
        void onCollision(Entity &hitEntity); 

        /**
         * @brief Handles slowing down when player isn't moving in a particular direction
         *
         * @param velAxis The velocity axis we're checking
         * @param moveAxis The direction we're supposed to be moving
         * @param friction The friction for this type of movement
         * @param deltaTime The time needed to properly adjust for velocity and acceleration
         *
         * @return The new value for the velocity after slow down 
         */
        float checkDeadMoveAxis(float velAxis, float moveAxis, float friction, float deltaTime);

        /**
         * @brief Get the magnitude of a vector
         *
         * @param vec The vector to get the magnitude of
         *
         * @return The magnitude of the vector 
         */
        float getVectorMagnitude(sf::Vector2<float> vec);

        /**
         * @brief Get the unit vector of any vector
         *
         * @param vec The vector to get the unit of
         *
         * @return The unit vector 
         */
        sf::Vector2<float> getUnitVector(sf::Vector2<float> vec);
};
