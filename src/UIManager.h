#pragma once

#include <math.h>
#include "Player.h"
#include "WaveManager.h"
#include "HealthBar.h"
#include "WaveBar.h"


/** Class for the player.
 * 
 * The Player is an Entity which is controlled by the player and responds to keyboard input.
 */
class UIManager
{
    public:
        UIManager();
        
        Player* _player;
        WaveManager* _wave;
        sf::RenderWindow* _gameWindow;
        sf::View* _view;
        HealthBar _healthBar;
        WaveBar _waveBar;

        /**
         * @brief establishes a player pointer that can be passed to the enemies
         * 
         * @param play player object passed by reference
         */ 
        void setData(Player &player, WaveManager &_wave,  sf::RenderWindow &gameWindow, sf::View &view );

        /**
         * Implementation of onDraw()
         */
        void onDraw(sf::Time frameTime);

        /**
         * @brief Called from drawFrame(),
         *  This will draw the map as well as the tutorial sprite.
         */
        void drawMap();

    private:

};

