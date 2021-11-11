#pragma once

#include <math.h>
#include "Player.h"
#include "HealthBar.h"


/** Class for the player.
 * 
 * The Player is an Entity which is controlled by the player and responds to keyboard input.
 */
class UIManager
{
    public:
        UIManager();
        
        Player* _player;
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

};

