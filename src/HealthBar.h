#pragma once

#include <cmath>
#include "Player.h"
// #include "UIManager.h"

class HealthBar
{
    public:
        float _health;
        // HealthBar();
        Player* _player;
        sf::RenderWindow* _gameWindow;
        sf::View* _view;

        void setData(Player* player, sf::RenderWindow* gameWindow, sf::View* view);

        void draw();
};
