#include "GameManager.h"

void GameManager::drawRoundProgressHUD()
{
    float enemiesAlive = (float)this->_wave.getEnemiesAlive();
    float totalEnemies = (float)this->_wave.getEnemies();
    int currWave = this->_wave.getWave();
    
    const int lineSize = 2;
    const sf::Vector2<float> viewCenter = _gameWindow.getView().getCenter();
    const sf::Vector2<float> &viewSize = _view.getSize();
    const sf::Vector2<float> barOutterSize{100.f, 5.f};
    const sf::Vector2<float> barInnerSize{barOutterSize.x * (enemiesAlive / totalEnemies), barOutterSize.y};
    const sf::Vector2<int> padding{2 + lineSize, 2 + lineSize};
    const sf::Vector2<float> barPosition{viewCenter.x - padding.x - barOutterSize.x / 2, viewCenter.y + padding.y + barOutterSize.y - viewSize.y / 2};

    // This is the outside grey/black rectangle.
    sf::RectangleShape outsideRect(barOutterSize);
    outsideRect.setPosition(barPosition);
    outsideRect.setFillColor(sf::Color(45, 45, 45, 255));
    outsideRect.setOutlineColor(sf::Color::Black);
    outsideRect.setOutlineThickness(lineSize);
    _gameWindow.draw(outsideRect);

    // This is the inside purple rectangle.
    sf::RectangleShape insideRect(barInnerSize);
    insideRect.setPosition(barPosition);
    insideRect.setFillColor(sf::Color(128, 0, 187, 255));
    _gameWindow.draw(insideRect);

    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("fonts/Helvetica.ttf"))
    {
        printf("ERROR: font can not be loaded!!");
    }

    // Current wave number text
    text.setFont(font);
    text.setString(std::to_string(currWave));
    text.setCharacterSize(lineSize * 2 + barOutterSize.y);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);

    text.setPosition(sf::Vector2f{barPosition.x - padding.x - (text.getGlobalBounds().left + text.getGlobalBounds().width), barPosition.y + lineSize - (text.getGlobalBounds().top + text.getGlobalBounds().height) / 2});
    _gameWindow.draw(text);
}

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

void GameManager::drawMap()
{
    sf::Texture texture;
    texture.loadFromFile("assets/textures/temp_floor_128.png");
    texture.setRepeated(true);

    sf::IntRect rectSourceSprite(0, 0, 1500, 1125);
    sf::Sprite sprite(texture, rectSourceSprite);

    this->_gameWindow.draw(sprite);
}

void GameManager::drawHealthHUD()
{
    const int lineSize = 2;
    const sf::Vector2<float> viewCenter = _gameWindow.getView().getCenter();
    const sf::Vector2<float> &viewSize = _view.getSize();
    const sf::Vector2<float> barOutterSize{100.f, 10.f};
    const sf::Vector2<float> barInnerSize{barOutterSize.x * ((float)_player.getHealth() / 100), barOutterSize.y};
    const sf::Vector2<int> padding{5 + lineSize, 5 + lineSize};
    const sf::Vector2<float> barPosition{viewCenter.x + padding.x - (viewSize.x / 2), viewCenter.y - padding.y - barOutterSize.y + viewSize.y / 2};

    // This is the outside grey/black rectangle.
    sf::RectangleShape outsideRect(barOutterSize);
    outsideRect.setPosition(barPosition);
    outsideRect.setFillColor(sf::Color(45, 45, 45, 255));
    outsideRect.setOutlineColor(sf::Color::Black);
    outsideRect.setOutlineThickness(lineSize);
    _gameWindow.draw(outsideRect);

    // This is the inside red rectangle.
    sf::RectangleShape insideRect(barInnerSize);
    insideRect.setPosition(barPosition);
    insideRect.setFillColor(sf::Color(255, 0, 0, 255));
    _gameWindow.draw(insideRect);
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

void GameManager::drawHitIndicator(Enemy* e)
{
    //sf::Clock gameClock;
    //sf::Time time = gameClock.restart();
    
    //std::cout<<frameTime.asSeconds()<<std::endl;

    if(e!=nullptr)
    {
        hitIndicator = this->_wave.getHitIndicator(e);
        hitIndicator.setFont(font);
        if(e->isAlive())
        {
            _gameWindow.draw(hitIndicator);
        }
        //_hitEnemy = nullptr;
    }
    else
    {
        //text.setFillColor(sf::Color::Transparent);
        //text.setOutlineColor(sf::Color::Transparent);
    }
    
    //hitIndicator
}
