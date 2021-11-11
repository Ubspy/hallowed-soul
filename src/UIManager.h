#pragma once

#include <math.h>
#include "Player.h"
// #include "HealthBar.h"


/** Class for the player.
 * 
 * The Player is an Entity which is controlled by the player and responds to keyboard input.
 */
class UIManager
{
    public:
        UIManager();
        
        virtual Player* _player;
        sf::RenderWindow* _gameWindow;
        sf::View* _view;
        HealthBar _healthBar;
        

        

        /**
         * @brief establishes a player pointer that can be passed to the enemies
         * 
         * @param play player object passed by reference
         */ 
        void setData(Player &player, sf::RenderWindow &gameWindow, sf::View &view );

        /**
         * Implementation of onDraw()
         */
        void onDraw();

    private:
        // Constants for player movement
        const float _moveSpeed = 350;
        const float _dodgeSpeed = 1100;
        const float _friction = 1600;
        const float _dodgeFriction = 6000;
        const float _attackRange = 40;
        const float _deadZone = 0.01;
        const float _attackTime = 0.6;

        // Current time since last attack
        float _lastAttackTime;

};

