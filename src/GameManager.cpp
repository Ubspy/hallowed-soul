#include "GameManager.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

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

    _indicatorTotal = 0;

    _hitEnemy = nullptr;

    // Set default game state
    // TODO: If we have a main menu, change the default state to that
    _currentState = GameState::playing;

    // This defines where our viewport is set to start
    // TODO: We will probably be spawning the player in the start of the map
    _view.setViewport({0.0f, 0.0f, 1.0f, 1.0f});

    // The view will display the top quarter of the map (_gameWindow),
    // but will take up the full size of the RenderWindow. Therefore,
    // this should zoom in on the gameWindow.
    _gameWindow.setView(_view);
    this->_wave.setPlayer(this->_player);
    
    this->_entityVec.push_back(&_player);

    this->_player.spawn(sf::Vector2<float>(1280.0 / 2.0, 720.0 / 2.0));
}

void GameManager::runGame()
{
    // Game clock for tracking time
    sf::Clock gameClock;

    printf("BEFORE BEGIN WAVE\n");

    this->_wave.beginWave();

    printf("AFTER BEGIN WAVE\n");

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
            this->_currentState = GameState::exiting;
        }

        // Next step is to check the collisions on all of our entities
        checkCollisions();

        // Finally we want to draw the frame
        drawFrame(frameTime);

        // We also want to check if the game state is exit, if it is then we break
        if(_currentState == GameState::exiting)
        {
            // Clear enemy objects
            this->_wave.endWave();
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
                        this->_wave.getEnemy(i)->kill();
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
    drawMap();

    // Drawing an entity has two steps: calling the onDraw method to update the entity's sprite
    // and calling the game window draw function
    this->_player.onDraw();
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
    drawHealthHUD();
    drawHitIndicator(_hitEnemy, frameTime);
    drawEnemyHealth();
    drawRoundProgressHUD();

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

/*
Enemy* GameManager::rayCast(Entity &source, const sf::Vector2<float> &ray)
{
    // TODO: Add other entities
    std::vector<Enemy*> enemies = this->_wave.getEnemiesVec();  
    
    // Let's get the center point for the source
    sf::Vector2<float> sourceCenter(source.getPosition().x + source.getWidth() / 2.0,
        source.getPosition().y + source.getHeight() / 2.0);

#if DEBUG
    // Draw the ray cast line if DEBUG mode is on 
    sf::Vertex line[2];

    line[0].position = sourceCenter;
    line[0].color = sf::Color::Blue;
    line[1].position = sourceCenter + ray;
    line[1].color = sf::Color::Blue;

    this->_debugLines.push_back(line[0]);
    this->_debugLines.push_back(line[1]);
#endif

    for(int i = 0; i < enemies.size(); i++)
    {
        Enemy* currentEnemy = enemies.at(i);

        // Skip this loop is enemy is dead
        if(!currentEnemy->isAlive())
            continue;
    
        // There are four lines to check for intersection here, so we need to check all of them
        // First is the left-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    currentEnemy->getPosition().x, (currentEnemy->getPosition().y + currentEnemy->getHeight()),
                    currentEnemy->getPosition().x, currentEnemy->getPosition().y))
        {
            #if DEBUG
                 sf::Vertex line[2];

                 line[0].position = sf::Vector2<float>(currentEnemy->getPosition().x,
                         currentEnemy->getPosition().y + currentEnemy->getHeight());
                 line[0].color = sf::Color::Red;
                 line[1].position = currentEnemy->getPosition();
                 line[1].color = sf::Color::Red;

                this->_debugLines.push_back(line[0]);
                this->_debugLines.push_back(line[1]);
            #endif

            return currentEnemy;
        }

        // Then check the top-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    currentEnemy->getPosition().x, currentEnemy->getPosition().y,
                    (currentEnemy->getPosition().x + currentEnemy->getWidth()), currentEnemy->getPosition().y))
        {
            #if DEBUG
                sf::Vertex line[2];

                line[0].position = currentEnemy->getPosition();
                line[0].color = sf::Color::Red;
                line[1].position = sf::Vector2<float>(currentEnemy->getPosition().x + currentEnemy->getWidth(),
                         currentEnemy->getPosition().y);
                line[1].color = sf::Color::Red;

                this->_debugLines.push_back(line[0]);
                this->_debugLines.push_back(line[1]);
            #endif
            
            return currentEnemy;
        }

        // Then check the right-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    (currentEnemy->getPosition().x + currentEnemy->getWidth()), currentEnemy->getPosition().y,
                    (currentEnemy->getPosition().x + currentEnemy->getWidth()), (currentEnemy->getPosition().y + currentEnemy->getHeight())))
        {
            #if DEBUG
                sf::Vertex line[2];

                line[0].position = sf::Vector2<float>(currentEnemy->getPosition().x + currentEnemy->getWidth(),
                         currentEnemy->getPosition().y); 
                line[0].color = sf::Color::Red;
                line[1].position = sf::Vector2<float>(currentEnemy->getPosition().x + currentEnemy->getWidth(),
                         currentEnemy->getPosition().y + currentEnemy->getHeight());
                line[1].color = sf::Color::Red;

                this->_debugLines.push_back(line[0]);
                this->_debugLines.push_back(line[1]);
            #endif
            
            return currentEnemy;
        }
        
        // Lastly, the bottom-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    currentEnemy->getPosition().x, (currentEnemy->getPosition().y + currentEnemy->getHeight()),
                    (currentEnemy->getPosition().x + currentEnemy->getWidth()), (currentEnemy->getPosition().y + currentEnemy->getHeight())))
        {
             #if DEBUG
                sf::Vertex line[2];

                line[0].position = sf::Vector2<float>(currentEnemy->getPosition().x,
                         currentEnemy->getPosition().y + currentEnemy->getHeight()); 
                line[0].color = sf::Color::Red;
                line[1].position = sf::Vector2<float>(currentEnemy->getPosition().x + currentEnemy->getWidth(),
                         currentEnemy->getPosition().y + currentEnemy->getHeight());
                line[1].color = sf::Color::Red;

                this->_debugLines.push_back(line[0]);
                this->_debugLines.push_back(line[1]);
            #endif

            return currentEnemy;
        }
    }

    return nullptr;
}

bool linesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    // If the lines intersect, then the intersection point on the x-axis Ix has to be in between x1 and x2, and x3 and x4
    // If point Ix lies outside of either range, then it is not part of one segment, and then isn't on the intersection
    // We want to make sure this interval can exist
    // For the smaller point, we need the max from either interval, but we want the smallest of those two maxes
    // this will be the largest point on the lower interval, the next one will be the smallest point on the larger interval
    if(std::min(std::max(x1, x2), std::max(x3, x4)) < std::max(std::min(x3, x4), std::min(x1, x2)))
    {
        // If the furthest point on line 1 doesn't even reach the min on line two, then this interval doesn't exist
        // Here we want to say they don't interesct
        return false;
    }

    // If both lines are vertival, they only intersect if they're the same value
    if(x1 == x2 && x3 == x4)
    {
        return x1 == x4;
    }

    // To avoid a divide by zero, check for same x values, we can also use an easier algorithm if this is the case
    if(x1 == x2)
    {
        // All we need to do is see if the other line crosses the X point from the vertical line
        // Get the slope
        float slope = (y4 - y3) / (x4 - x3); 

        // We can solve for the intercept, so let's find that
        float intercept = y3 - slope * x3;

        // Find the Y point
        float intersectY = slope * x1 + intercept;

        // Now we can see if Y lies in the Y range 
        return intersectY < std::max(y1, y2) && intersectY > std::min(y1, y2);
    }
    else if(x3 == x4)
    {
        // This is the same idea as x1 == x2, just swap the values around
        float slope = (y2 - y1) / (x2 - x1);
        float intercept = y1 - slope * x1;
        float intersectY = slope * x3 + intercept;
         
        return intersectY < std::max(y3, y4) && intersectY > std::min(y3, y4);
    }

    // Now we want to calculate the slopes of both lines
    // If the two X values are the same, then set the slope to the maximum possible value
    // TODO: Maybe bad for performance to use the max number, idk how floating point math works
    float slope1 = (y2 - y1) / (x2 - x1);
    float slope2 = (y4 - y3) / (x4 - x3);

    // One thing to check here is if the lines are parallel, because if they are then they won't intersect, we check another line
    if(slope1 == slope2)
    {
        return false;
    }

    // Using y = m*x + b, we can solve for b and find the intersepts for line 1 and 2
    float b1 = y1 - slope1 * x1;
    float b2 = y3 - slope2 * x3;

    // We now have the equations for both lines, and we can find their intersect point by setting them equal
    // Iy = m1 * Ix + b1, Iy = m2 * Ix + b2, for some point (Ix, Iy), we can solve for Ix and get it's value 
    // There is no divide by zero here since we checked before if slope1 and slope 2 are the same
    float intersectX = (b2 - b1) / (slope1 - slope2); 

    // Finally, we need to see if this intersectX is in the range we talked about at the top of this function
    // If our intersectX is out of these ranges, there is no intersection on the limited segments
    // If not, then there is an intersection
    return !(intersectX < std::min({x1, x2, x3, x4}) || intersectX > std::max({x1, x2, x3, x4}));
} */
