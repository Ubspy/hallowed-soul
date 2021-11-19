#include "GameManager.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <fstream>

// bool linesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

GameManager::GameManager() : 
    // First thing we want to do is create a window
    // TODO: Name and size subject to change
    _gameWindow {sf::VideoMode(1280, 720), "Hallowed Soul"}, 
    // Initialize the view (camera) 
    _view {sf::FloatRect(0.0, 0.0, 1280.0 / 2.0, 720.0 / 2.0)},
    _entityVec(),
    _player {&_entityVec},
    _wave {&_entityVec}
{
    if (!_font.loadFromFile("fonts/Helvetica.ttf"))
    {
        printf("ERROR: font can not be loaded!!");
    }

    if (!_titleFont.loadFromFile("fonts/Title.ttf"))
    {
        printf("ERROR: font can not be loaded!!");
    }

    if (!_deathFont.loadFromFile("fonts/DeathText.ttf"))
    {
        printf("ERROR: font can not be loaded!!");
    }

    _indicatorTotal = 0;

    _enemyDamage = 0;

    _hitEnemy = nullptr;

    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open())
    {
        highScoreFile >> _highScore;
        if (highScoreFile.fail())
        {
            std::cout << "Error: Couldn't read high score. Will overwrite highscore.txt.\n";
            highScoreFile.clear();
            _highScore = 0;
        }
    }
    else
    {
        std::cout << "Error: Couldn't read high score. Will overwrite highscore.txt.\n";
    }

    // Set default game state
    // TODO: If we have a main menu, change the default state to that
    _currentState = GameState::menu;

    // This defines where our viewport is set to start
    // TODO: We will probably be spawning the player in the start of the map
    _view.setViewport({0.0f, 0.0f, 1.0f, 1.0f});

    this->_wave.setPlayer(this->_player);
    
    this->_UIManager.setData(_player, _wave, _gameWindow, _view);
    
    this->_entityVec.push_back(&_player);

    this->_player.spawn(sf::Vector2<float>(1280.0 / 2.0, 720.0 / 2.0));
}

void GameManager::displayStartScreen()
{
    while(_currentState == GameState::menu)
    {
        startScreenHandleInput();

        drawStartScreen();

        if(_currentState == GameState::playing)
        {
            runGame();
        }
        if(_currentState == GameState::exiting)
        {
            _gameWindow.close();
            break;
        }
    }
}

void GameManager::displayDeathScreen()
{
    sf::Clock gameClock;
    double i = 0;
    while(1)
    {
        sf::Time frameTime = gameClock.restart();
        i = i + frameTime.asSeconds();

        deathScreenHandleInput();

        drawDeathScreen(i);

        if(_currentState == GameState::exiting)
        {
            _gameWindow.close();
            break;
        }
    }
}

void GameManager::startScreenHandleInput()
{
    sf::Event currentEvent;

    while(_gameWindow.pollEvent(currentEvent))
    {
        switch(currentEvent.type)
        {
            case sf::Event::KeyPressed:
            {
                this->handleKeyboardEvent(currentEvent);
                break;
            }
            case sf::Event::Closed:
            {
                this->_currentState = GameState::exiting;
                break;
            }
            default: // Otherwise just do nothing
                break;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        _currentState = GameState::playing;
    }
}

void GameManager::deathScreenHandleInput()
{
    sf::Event currentEvent;

    while(_gameWindow.pollEvent(currentEvent))
    {
        switch(currentEvent.type)
        {
            case sf::Event::KeyPressed:
            {
                this->handleKeyboardEvent(currentEvent);
                break;
            }
            case sf::Event::Closed:
            {
                this->_currentState = GameState::exiting;
                break;
            }
            default: // Otherwise just do nothing
                break;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        _currentState = GameState::exiting;
    }
}

void GameManager::runGame()
{
    // The view will display the top quarter of the map (_gameWindow),
    // but will take up the full size of the RenderWindow. Therefore,
    // this should zoom in on the gameWindow.
    _gameWindow.setView(_view);

    // Game clock for tracking time
    sf::Clock gameClock;

    this->_wave.beginWave();

    // Keep going while the window is open
    while(this->_gameWindow.isOpen())
    {
        // Update the game clock and get the frame time
        sf::Time frameTime = gameClock.restart();

        // This is the main game loop, there's a specific order we want to execute our loop in
        // First we need to consider that the only thing that will change our objects is
        // input from the user, so that's the first thing we want to do
        handleInput();

        // Once input is handled, we now want to update all of our objects
        updateEntities(frameTime);

        if(!this->_player.isAlive())
        {
            printf("YOU DIED!!!!!\n");
            this->_currentState = GameState::gameOver;
        }

        // Next step is to check the collisions on all of our entities
        checkCollisions();

        // Finally we want to draw the frame
        drawFrame(frameTime);

        //printf("FPS: %f\n", 1/frameTime.asSeconds());

        // We also want to check if the game state is exit, if it is then we break
        if(_currentState == GameState::gameOver)
        {
            // Clear enemy objects
            this->_wave.endWave();
            updateHighScoreFile();
            displayDeathScreen();
            break;
        }
        if(_currentState == GameState::exiting)
        {
            // Clear enemy objects
            this->_wave.endWave();
            updateHighScoreFile();
            _gameWindow.close();
            break;
        }
    }
}

void GameManager::handleInput()
{
    // Event object for the current event we're handling
    sf::Event currentEvent;

    // We want to poll all avalible events in the game
    // TODO: This may be unnecessary and slow, since this while loop could be processing up to 50 events at once
    // We may not even need this at all
    while(_gameWindow.pollEvent(currentEvent))
    {
        // TODO: Control variables? Maybe some config file?
        // First we want to check what type of event it is 
        switch(currentEvent.type)
        {
            case sf::Event::KeyPressed:
            {
                this->handleKeyboardEvent(currentEvent);
                break;
            }
            case sf::Event::Closed:
            {
                this->_currentState = GameState::exiting;
                break;
            }
            default: // Otherwise just do nothing
                break;
        }
    }       

    // The following four if statements will tell the player it needs to be moving
    // in the direction based off of the directional keys pressed.
    // We are using all ifs here because we want diagonal movement to be possible
    // Additionally, we're not using the above loop to check because we don't just want to
    // move up when the up key is pressed, we want to continue moving up while whenever the
    // up key is held, this solves that issue
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // Up is negative y direction
        this->_player.moveInDirection(sf::Vector2<float>(0, -1));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // Down is positive y direction
        this->_player.moveInDirection(sf::Vector2<float>(0, 1));
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // Left is negative x direction
        this->_player.moveInDirection(sf::Vector2<float>(-1, 0));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // Right is positive x direction
        this->_player.moveInDirection(sf::Vector2<float>(1, 0));
    }

}

void GameManager::handleKeyboardEvent(sf::Event &kdbEvent)
{
    switch(kdbEvent.key.code)
    {
        case sf::Keyboard::Space:
        {
            this->_player.dodgeInDirection(sf::Vector2<float>(0, 0));
            break;
        }
        case sf::Keyboard::Backspace:
        {
#if DEBUG
            // THE KILL BUTTON
            for(int i=0; i<this->_wave.getEnemies(); i++)
            {
                try
                {
                    if(this->_wave.getEnemy(i)->isAlive())
                    {
                        this->_wave.getEnemy(i)->doDamage(100);
                        break;
                    }
                }
                catch(const std::exception& e)
                {
                    break;
                }
            }
#endif
        }
        case sf::Keyboard::LShift:
        {
            /*
            Enemy* hitEnemy = this->rayCast(this->_player,
                    this->_player.getLastMoveDirection() * this->_player.getAttackRange());

            if(hitEnemy != nullptr)
            {
                this->_player.attack(hitEnemy);
                _indicatorTotal = 0;
                _hitEnemy = hitEnemy;
                //drawHitIndicator(hitEnemy);
            } */

            this->_player.attack();
        }
        default:
            // Do nothing
            break;
    }
}

void GameManager::handleMouseEvent(sf::Event &mouseEvent)
{
    // TODO: Do we need this?
    // If we implement menus we will, but consider remove otherwise
}

void GameManager::checkCollisions()
{
    // TODO: Check for collision between dynamic entities and other entities
}

void GameManager::updateEntities(sf::Time frameTime)
{
    // TODO: Update other entities

    // Update player
    this->_player.update(frameTime.asSeconds());

    // Update the enemy wave manager 
    this->_wave.update(frameTime.asSeconds());
}

void GameManager::drawFrame(sf::Time frameTime)
{
    // Clear current buffer
    _gameWindow.clear();

    // Now update the position of the view as nessisary.
    updateViewLocked();

    // Draw the temporary background before anything else
    _UIManager.drawMap();

    // Drawing an entity has two steps: calling the draw method to update the entity's sprite
    // and calling the game window draw function
    this->_player.onDrawBase();
    this->_wave.waveDraw();
    this->_gameWindow.draw(this->_player.getSprite());
    for(int i=0; i<this->_wave.getEnemies(); i++)
    {
        if(this->_wave.getEnemy(i)->isAlive())
        {
            this->_gameWindow.draw(this->_wave.getEnemy(i)->getSprite());
        }
    }
    // TODO: Add other entities

    // Draw the HUD over most things
    drawHitIndicator(_hitEnemy, frameTime);
    drawEnemyHealth();
    _UIManager.onDraw(frameTime);

    if(_player.isRed())
    {
        drawRed();
    }
    
    #if DEBUG
        this->debugDraw();
    #endif

    // Finally, display the window
    _gameWindow.display();    
}

void GameManager::debugDraw()
{
    for(int i = 0; i < (this->_debugLines.size()); i += 2)
    {
        sf::Vertex currentLine[2];
        currentLine[0] = this->_debugLines.at(i);
        currentLine[1] = this->_debugLines.at(i + 1);

        this->_gameWindow.draw(currentLine, 2, sf::Lines);
    }
}

int GameManager::getHighScore()
{
    return _highScore;
}

void GameManager::updateHighScoreFile()
{

    // If new high score
    if (_wave.getWave() > getHighScore())
    {
        // Open a file and record high score
        std::ofstream of("highscore.txt");
        if (of.is_open())
            of << _wave.getWave();
        if (!of.is_open() || of.fail())
            std::cout << "Error: couldn't write to high score file\n";
    }
}
