#include "GameManager.h"
#include <cmath>

GameManager::GameManager()
    // First thing we want to do is create a window
    // TODO: Name and size subject to change
    : _gameWindow {sf::VideoMode(1280, 720), "Hallowed Soul"}
    // Initialize camera
    , _view {sf::FloatRect(0.0, 0.0, 1280.0 / 2.0, 720.0 / 2.0)}
{
    // Set default game state
    // TODO: If we have a main menu, change the default state to that
    _currentState = GameState::playing;

    // TODO: what does this do?
    _view.setViewport({0.0f, 0.0f, 1.0f, 1.0f});

    // The view will display the top quarter of the map (_gameWindow),
    // but will take up the full size of the RenderWindow. Therefore,
    // this should zoom in on the gameWindow.
    _gameWindow.setView(_view);
}

void GameManager::runGame()
{
    // Keep going while the window is open
    while(this->_gameWindow.isOpen())
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

void GameManager::updateEntities()
{
    this->_player.update();
    // TODO: Update other entities
}

void GameManager::drawFrame()
{
    // Clear current buffer
    _gameWindow.clear();

    // need to update the camera before drawing anything
    // updateView();

    this->_player.onDraw();
    this->_gameWindow.draw(this->_player.getSprite());
    // TODO: Add other entities

    // Finally, display the window
    _gameWindow.display();    
}

void GameManager::updateView()
{
    // TODO: this is a mess
    // I want to define a 100x50 rectangle in the middle of the view.
    // If the player walks outside of this rectangle, then we should
    // move the view to follow it and keep it in the rectangle.
    const int centerRectWidth = 100;
    const int centerRectHeight = 50;
    sf::Vector2i posInView = _gameWindow.mapCoordsToPixel(static_cast<sf::Vector2f>(this->_player.getPosition()));
    sf::Vector2i viewCenter = static_cast<sf::Vector2i>(_view.getSize() * 0.5f);
    sf::Vector2i displFromCenter = posInView - viewCenter;
    sf::Vector2i outsideRect {0, 0}; // Vector that gives us how outside of the rectangle we are
    if (displFromCenter.x < -(centerRectWidth/2))
        outsideRect.x = displFromCenter.x + (centerRectWidth/2);
    else if (displFromCenter.x > (centerRectWidth/2))
        outsideRect.x = displFromCenter.x - (centerRectWidth/2);
    
    if (displFromCenter.y < -(centerRectHeight/2))
        outsideRect.y = displFromCenter.y + (centerRectHeight/2);
    else if (displFromCenter.y > (centerRectHeight/2))
        outsideRect.y = displFromCenter.y - (centerRectHeight/2);

    sf::Vector2i topLeft = static_cast<sf::Vector2i>(_gameWindow.mapPixelToCoords({0, 0}));
    sf::Vector2i bottomRight = static_cast<sf::Vector2i>(_gameWindow.mapPixelToCoords(static_cast<sf::Vector2i>(_view.getSize())));
    sf::Vector2i translateView = outsideRect;
    if (topLeft.x + outsideRect.x < 0)
        translateView.x = -topLeft.x;
    else if (bottomRight.x + outsideRect.x > _gameWindow.getSize().x)
        translateView.x = _gameWindow.getSize().x - bottomRight.x;

    if (topLeft.y + outsideRect.y < 0)
        translateView.y = -topLeft.y;
    else if (bottomRight.y + outsideRect.y > _gameWindow.getSize().y)
        translateView.y = _gameWindow.getSize().y - bottomRight.y;

    _view.move(static_cast<sf::Vector2f>(translateView));

    _gameWindow.setView(_view);
}
