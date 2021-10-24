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
    , _view {sf::FloatRect(0.0, 0.0, 1280/2, 720/2)}
{
    _view.setViewport({0.0f, 0.0f, 1.0f, 1.0f});
    // The view will display the top quarter of the map (_gameWindow),
    // but will take up the full size of the RenderWindow. Therefore,
    // this should zoom in on the gameWindow.
    _gameWindow.setView(_view);
}

int GameManager::runGame()
{
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

    // I want to define a 100x50 rectangle in the middle of the view.
    // If the player walks outside of this rectangle, when we should
    // move the view to follow it and keep it in the rectangle.
    sf::Vector2i posInView = _gameWindow.mapCoordsToPixel(static_cast<sf::Vector2f>(testEntity.getPosition()));
    sf::Vector2i center = static_cast<sf::Vector2i>(_view.getCenter());

    // Draw every entity
    for ( auto it = entities.begin(); it != entities.end(); ++it )
    {
        (*it)->onDraw();
        _gameWindow.draw((*it)->getSprite());
    }

    // Finally, display the window
    _gameWindow.display();    
}
