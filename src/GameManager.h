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
        /**
         * @brief Default constructor
         */
        GameManager();

        /**
         * @brief Run the main game loop 
         */
        void runGame();

    private:
        sf::RenderWindow _gameWindow;
        sf::View _view;

        GameState _currentState;
        Player _player;

        /**
         * @brief Called from main loop, turns all the user inputs into game instructions
         */
        void handleInput();

        /**
         * @brief Called from handleInput(), will evaluate a keyboard event
         *  Used if you want an action to happen on a keystroke
         *
         * @param kbdEvent The keyboard event we're handling
         */
        void handleKeyboardEvent(sf::Event &kbdEvent);


        /**
         * @brief Called from handleInput(), will evaluate a mose event
         *  Used if you want an action to happen on scroll, click, or mouse move        *
         * 
         * @param mouseEvent The mose event we're handling
         */
        void handleMouseEvent(sf::Event &mouseEvent);

        /**
         * @brief Called from the main game loop
         *  will update all of our game objects using the read inputs
         *
         * @param frameTime The time between the last frame and this one
         */
        void updateEntities(sf::Time frameTime);

        /**
         * @brief Called from main loop,
         *  will check for collisions between entities and objects
         */
        void checkCollisions();
        
        /**
         * @brief Called from main game loop,
         *  will render all of our objects and entities to the view
         */
        void drawFrame();

        /**
         * @brief Called from drawFrame(),
         *  will move the current view based off of the player's location
         */
        void updateView();
};
