#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "WaveManager.h"

enum GameState
{
    playing, menu, gameOver, exiting
};

class GameManager
{
    public:
        GameManager();

        // Run the main game loop 
        void runGame();

        const Entity* rayCast(Entity &source, sf::Vector2<float> &rayDir);

    private:
        sf::RenderWindow _gameWindow;
        sf::View _view;

        GameState _currentState;
        Player _player;
        WaveManager _wave;

        // Called from main loop, turns all the user inputs into game instructions
        void handleInput();

        // Called from handleInput(), will evaluate a keyboard event
        // Used if you want an action to happen on a keystroke
        void handleKeyboardEvent(sf::Event &kbdEvent);

        // Called from handleInput(), will evaluate a mose event
        // Used if you want an action to happen on scroll, click, or mouse move
        void handleMouseEvent(sf::Event &mouseEvent);

        // Called from the main game loop,
        // will update all of our game objects using the read inputs
        void updateEntities(sf::Time frameTime);

        // Called from main loop, will check for collisions between entities and objects
        void checkCollisions();
        
        // Called from main game loop, will render all of our objects and entities to the view
        void drawFrame();

        // Called from drawFrame(),
        // will move the current view based off of the player's location
        void updateView();
};
