#include "GameManager.h"

void GameManager::updateViewLocked()
{
    sf::View view = _gameWindow.getView();
    const sf::Vector2f &playerLocation = this->_player.getPosition();
    const sf::Vector2f &viewSize = _view.getSize();
    sf::Vector2f mapSize{1500.0, 1125.0}; // this can probably be moved to a member variable later when the map is made.

    view.setCenter(this->_player.getPosition());

    if (playerLocation.x < viewSize.x / 2) // If camera view is extends past left side of the map.
    {
        view.setCenter(sf::Vector2f{viewSize.x / 2, view.getCenter().y});
    }
    else if (playerLocation.x + viewSize.x / 2 > mapSize.x) // If camera view is extends past right side of the map.
    {
        view.setCenter(sf::Vector2f{mapSize.x - (viewSize.x / 2), view.getCenter().y});
    }

    if (playerLocation.y < viewSize.y / 2) // If camera view is extends past top side of the map.
    {
        view.setCenter(sf::Vector2f{view.getCenter().x, viewSize.y / 2});
    }
    else if (playerLocation.y + viewSize.y / 2 > mapSize.y) // If camera view is extends past bottom side of the map.
    {
        view.setCenter(sf::Vector2f{view.getCenter().x, mapSize.y - (viewSize.y / 2)});
    }

    _gameWindow.setView(view);
}

void GameManager::drawRed()
{
    sf::Texture texture;
    texture.loadFromFile("assets/textures/red.png");
    texture.setRepeated(true);

    sf::IntRect rectSourceSprite(0, 0, 1500, 1125);
    sf::Sprite sprite(texture, rectSourceSprite);

    this->_gameWindow.draw(sprite);
}

void GameManager::drawEnemyHealth()
{
    for(int i=0; i<this->_wave.getEnemies(); i++)
    {
        if(this->_wave.getEnemy(i)->isAlive())
        {
            _gameWindow.draw(this->_wave.getHealthBarBorder(this->_wave.getEnemy(i)));
            _gameWindow.draw(this->_wave.getHealthBar(this->_wave.getEnemy(i)));
        }
    }
}

void GameManager::drawHitIndicator(Enemy* e, sf::Time frameTime)
{
    if(e!=nullptr)
    {
        _indicatorTotal = frameTime.asSeconds() + _indicatorTotal;
        _hitIndicator = this->_wave.getHitIndicator(e);
        _hitIndicator.setFont(_font);
        if(e->isAlive() && _indicatorTotal <= 1)
        {
            _gameWindow.draw(_hitIndicator);
        }
    }
}

void GameManager::drawStartScreen()
{
    _gameWindow.clear();
    sf::Text highScore;
    highScore = getHighScoreText();
    highScore.setCharacterSize(90);
    highScore.setPosition(340, 450);
    highScore.setOutlineThickness(8);
    highScore.setOutlineColor(sf::Color::Black);
    
    sf::Texture texture;
    texture.loadFromFile("assets/textures/start.png");
    texture.setRepeated(true);

    sf::IntRect rectSourceSprite(150, 225, 1500, 1125);
    sf::Sprite sprite(texture, rectSourceSprite);

    _gameWindow.draw(sprite);
    _gameWindow.draw(getTitle());
    _gameWindow.draw(highScore);
    _gameWindow.draw(getStartText());
    _gameWindow.display();
}

sf::Text GameManager::getTitle()
{
    sf::Text title;
    title.setString("HALLOWED SOUL");
    title.setFont(_titleFont);
    title.setCharacterSize(150);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(5);
    title.setPosition(210,-10);
    return title;
}

sf::Text GameManager::getStartText()
{
    sf::Text title;
    title.setString("<Press SPACE to Start>");
    title.setFont(_font);
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(5);
    title.setPosition(290,600);
    return title;
}

sf::Text GameManager::getHighScoreText()
{
    sf::Text text;
    text.setString("High score: " + std::to_string(getHighScore()));
    text.setFont(_font);
    return text;
}

sf::Text GameManager::getGameOverText()
{
    sf::Text text;
    text.setString("GAME OVER");
    text.setFont(_deathFont);
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::White);
    text.setPosition(190,0);
    
    return text;
}

void GameManager::drawDeathScreen(double time)
{
    int rounded = round(time);
    _gameWindow.setView(_view);
    _gameWindow.clear(sf::Color::Black);
    sf::Text gameOver = getGameOverText();
    sf::Text yourScore;
    sf::Text highScore = getHighScoreText();
    sf::Text newHighScore;
    sf::Text instructions;
    yourScore.setString("Your score: " + std::to_string(_wave.getWave()));
    newHighScore.setString("New High Score!!!");
    instructions.setString("<Press SPACE to exit>");
    yourScore.setFont(_font);
    newHighScore.setFont(_font);
    instructions.setFont(_font);
    yourScore.setCharacterSize(30);
    highScore.setCharacterSize(30);
    newHighScore.setCharacterSize(30);
    instructions.setCharacterSize(30);
    yourScore.setPosition(222,160);
    highScore.setPosition(225,200);
    newHighScore.setPosition(195,240);
    instructions.setPosition(165,300);
    if(time<=8.5)
    {
        gameOver.setFillColor(sf::Color(255,255,255,time*30));
        yourScore.setFillColor(sf::Color::Black);
        highScore.setFillColor(sf::Color::Black);
        newHighScore.setFillColor(sf::Color::Black);
    }
    if((time>=2) && (time<=10.5))
    {
        yourScore.setFillColor(sf::Color(255,255,255,(time-2)*30));
        highScore.setFillColor(sf::Color::Black);
        newHighScore.setFillColor(sf::Color::Black);
    }
    if((time>=4)&&(time<=12.5))
    {
        highScore.setFillColor(sf::Color(255,255,255,(time-4)*30));
        newHighScore.setFillColor(sf::Color::Black);
    }
    if((time>=6) && (time<=14.5) &&(_wave.getWave() >= getHighScore()))
    {
        if((rounded % 2) ==0)
        {
            newHighScore.setFillColor(sf::Color(255,0,0,(time-6)*30));
        }
        else
        {
            newHighScore.setFillColor(sf::Color::Black);
        }
    }
    if((time>14.5) && (_wave.getWave() > getHighScore()))
    {
        if((rounded % 2) == 0)
        {
            newHighScore.setFillColor(sf::Color::Red);
        }
        else
        {
            newHighScore.setFillColor(sf::Color::Black);
        }
    }
    if(_wave.getWave() <= getHighScore())
    {
        newHighScore.setFillColor(sf::Color::Black);
    }
    instructions.setFillColor(sf::Color::White);
    _gameWindow.draw(gameOver);
    _gameWindow.draw(yourScore);
    _gameWindow.draw(highScore);
    _gameWindow.draw(newHighScore);
    _gameWindow.draw(instructions);
    
    _gameWindow.display();
}