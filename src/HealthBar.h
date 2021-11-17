#pragma once

#include <cmath>
#include "Player.h"

class HealthBar
{
    public:
        Player* _player;
        sf::RenderWindow* _gameWindow;
        sf::View* _view;

        /**
         * @brief Called from UIManager's own setData().
         *  Set pointers needed to get health information.
         */
        void setData(Player* player, sf::RenderWindow* gameWindow, sf::View* view);

        /**
         * @brief Called from UIManager onDraw(),
         *  Draw the players health heads up display
         */
        void draw();
};
