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
