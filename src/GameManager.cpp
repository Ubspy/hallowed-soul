#include "GameManager.h"

GameManager::GameManager()
    // First thing we want to do is create a window
    // TODO: Name and size subject to change
    : _gameWindow {sf::VideoMode(1280, 720), "Hallowed Soul"}
{
    // Set default game state
    // TODO: If we have a main menu, change the default state to that
    _currentState = GameState::playing;

    // Initialize player
    // Initialize camera
}

void GameManager::runGame()
{
    // Keep going while the window is open
    while(this->_gameWindow.isOpen())
    {
        // This is the main game loop, there's a specific order we want to execute our loop in
        // First we need to consider that the only thing that will change our objects is
        // input from the user, so that's the first thing we want to do
        this->handleInput();

        // Once input is handled, we now want to update all of our objects
        this->_player.update();
        // TODO: Update other entities

        // Next step is to check the collisions on all of our entities
        this->checkCollisions();

        // Finally we want to draw the frame
        this->drawFrame();

        // We also want to check if the game state is exit, if it is then we break
        if(this->_currentState == GameState::exiting)
        {
            break;
        }
    }
}

void GameManager::handleInput()
{
    sf::Event currentEvent;

    while(_gameWindow.pollEvent(currentEvent))
    {
        // TODO: Control variables? Maybe some config file?
        // First we want to check what type of event it is 
        switch(currentEvent.type)
        {
            case sf::Event::Closed:
            {
                this->_currentState = GameState::exiting;
                break;
            }
            default: // Otherwise just do nothing
                break;
        }
    }       

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->_player.moveInDirection(sf::Vector2<float>(0, -1));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->_player.moveInDirection(sf::Vector2<float>(0, 1));
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->_player.moveInDirection(sf::Vector2<float>(-1, 0));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->_player.moveInDirection(sf::Vector2<float>(1, 0));
    }
}

void GameManager::handleMouseEvent(sf::Event &mouseEvent)
{

}

void GameManager::checkCollisions()
{

}

void GameManager::drawFrame()
{

}
