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

        int _newWaveMatcher;
        float _timeElapsed;
        bool _isDrawingNotif = false;

        /**
         * @brief Called from UIManager's own setData().
         *  Set pointers needed to get round information.
         */
        void setData(WaveManager* wave, sf::RenderWindow* gameWindow, sf::View* view);
        
        /**
         * @brief Called from UIManager onDraw(),
         *  Draw a heads up display on the current round information
         */
        void draw(sf::Time frameTime);

        /**
         * @brief Called from UIManager onDraw().
         *  Sets member variable _deltaTime for later use.
         */
        void setDeltaTime();

        /**
         * @brief Called from WaveBar draw(),
         *  Set pointers needed to get round information.
         */
        void drawWaveNotification(sf::Time frameTime);
};
