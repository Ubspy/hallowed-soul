#pragma once

#include <cmath>
#include "WaveManager.h"

class WaveBar
{
    public:
        float _health;
        WaveManager* _wave;
        sf::RenderWindow* _gameWindow;
        sf::View* _view;

        /**
         * @brief Called from UIManager's own setData(),
         *  Set pointers needed to get round information.
         */
        void setData(WaveManager* wave, sf::RenderWindow* gameWindow, sf::View* view);
        
        /**
         * @brief Called from UIManager onDraw(),
         *  Draw a heads up display on the current round information
         */
        void draw();
};
