#include "Entity.h"

Entity::Entity()
{
    _position = sf::Vector2<int>(0, 0);
    _velocity = sf::Vector2<int>(0, 0);
    _width = 0;
    _height = 0;
    _health = 100;
}

sf::Vector2<int> Entity::getPosition()
{
    return _position;
}

sf::Vector2<int> Entity::getVelocity()
{
    return _velocity;
}

int Entity::getWidth()
{
    return _width;
}

int Entity::getHeight()
{
    return _height;
}

void Entity::update()
{
    // When we update a frame we want to do a few things
    // The first of which is we want to update the position using our velocity
    _position += _velocity;

    // Then we want to check for the health
    if(_health <= 0)
    {
        this->kill();
    }

    // We also want to call the overridable function, and then draw it
    this->onUpdate();
    this->onDraw();
}

void Entity::kill()
{

}

void Entity::spawn(sf::Vector2<int> spawnLocation)
{

}

void Entity::onDraw()
{

}
