#pragma once

#define DEBUG 1

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <cmath>
#include <stdexcept>
#include <limits>
#include "Player.h"
#include "WaveManager.h"
#include "UIManager.h"

/** Enum representing the game state. */
enum GameState
{
    /** Game is currently being played. */
    playing,

    /** On the main menu. */
    menu,

    /** Game is complete. */
    gameOver,

    /** Window is closing. */
    exiting
};

/** Class which handles the main loop, timing, and game logic. 
 * 
 * Calls drawing and updating functions explicitly on the Player and non-enemy Entities.
 * Enemies are fully handled and owned by WaveManager; GameManager calls WaveManager's
 * drawing and updating functions to control Enemies.
 */
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

        Enemy* rayCast(Entity &source, const sf::Vector2<float> &rayDir);

    private:

        Enemy* _hitEnemy;

        sf::Text _hitIndicator;

        /** The window we are displaying in */
        sf::RenderWindow _gameWindow;

        /** The view, or "camera" that we are using to display the world. */
        sf::View _view;

        /** The current game state. */
        GameState _currentState;

        /** The player. */
        Player _player;

        /** The WaveManager, which owns all Enemies. */
        WaveManager _wave;

        UIManager _UIManager;

        sf::Font _font;

        float _indicatorTotal;

        std::vector<sf::Vertex> _debugLines;

        void debugDraw();

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
        void drawFrame(sf::Time frameTime);

        /**
         * @brief Called from drawFrame(),
         *  will move the current view based off of the player's location
         */
        void updateViewLocked();

        void drawEnemyHealth();

        void drawHitIndicator(Enemy* e, sf::Time frameTime);
};
