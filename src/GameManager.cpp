#include "GameManager.h"
#include "TestEntity.h"

std::forward_list<Entity*> GameManager::entities;

GameManager::GameManager()
    // First thing we want to do is create a window
    // TODO: Name and size subject to change
    : _gameWindow {sf::VideoMode(1280, 720), "Hallowed Soul"}
    // Set default game state
    // TODO: If we have a main menu, change the default state to that
    , _currentState {GameState::playing}
    // Initialize player
    // Initialize camera
    , _view {sf::FloatRect(0.0, 0.0, 1280, 720)}
{
    _gameWindow.setView(_view);
}

int GameManager::runGame()
{

    TestEntity e;
    // Keep going while the window is open
    while(_gameWindow.isOpen())
    {
        // This is the main game loop, there's a specific order we want to execute our loop in
        // First we need to consider that the only thing that will change our objects is
        // input from the user, so that's the first thing we want to do
        handleInput();

        // Once input is handled, we now want to update all of our objects
        updateEntities();

        // Next step is to check the collisions on all of our entities
        checkCollisions();

        // Finally we want to draw the frame
        drawFrame();

        // We also want to check if the game state is exit, if it is then we break
        if(_currentState == GameState::exiting)
        {
            _gameWindow.close();
            break;
        }
    }
    return 0;
}

void GameManager::handleInput()
{
    sf::Event currentEvent;

    while(_gameWindow.pollEvent(currentEvent))
    {
        // Close window: exit
        if (currentEvent.type == sf::Event::Closed)
            _currentState = exiting;
    }       
}

void GameManager::checkCollisions()
{

}

void GameManager::updateEntities()
{
    for ( auto it = entities.begin(); it != entities.end(); ++it )
    {
        (*it)->update();
    }
}

void GameManager::drawFrame()
{
    // Clear current buffer
    _gameWindow.clear();

    // Draw every entity
    for ( auto it = entities.begin(); it != entities.end(); ++it )
    {
        (*it)->onDraw();
        _gameWindow.draw((*it)->getSprite());
    }

    // Finally, display the window
    _gameWindow.display();    
}
