#pragma once

#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include "Player.h"

enum GameState
{
    playing, menu, gameOver, exiting
};

class GameManager
{
    public:
        GameManager();

        /** Run the main game loop */
        void runGame();

        static forward_list<Entity*> entities;

    private:
        sf::RenderWindow _gameWindow;
        GameState _currentState;
        // Camera _gameCamera;
        // Player _player;

        void runFrame();
        void handleInput();
        void checkCollisions();
        void drawFrame();
};

#endif
