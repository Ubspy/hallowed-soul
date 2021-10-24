#pragma once

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

    private:
        sf::RenderWindow _gameWindow;
        GameState _currentState;
        Player _player;
        // Camera _gameCamera;

        void runFrame();
        void handleInput();
        void handleKeyboardEvent(sf::Event &kbdEvent);
        void handleMouseEvent(sf::Event &mouseEvent);
        void checkCollisions();
        void drawFrame();
};
