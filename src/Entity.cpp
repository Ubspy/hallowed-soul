#include "Entity.h"

Entity::Entity()
{
    _position = sf::Vector2<int>(0, 0);
    _velocity = sf::Vector2<int>(0, 0);
    _width = 0;
    _height = 0;
    _health = 100;
}

sf::Vector2i Entity::getPosition()
{
    return _position;
}

sf::Vector2i Entity::getVelocity()
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
    // First we want to check for the health to see if this entity is dead
    if(_health <= 0)
    {
        this->kill();
    }

    // Then we want to update the entity
    this->onUpdate();

    // After the update, we want to update the entity's position based off of it's velocity
    this->_position += this->_velocity;

    // The below / was added by Diesel, he's a good boy
    // Finally, we draw the entity  /
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
    // Default behavior is to just set the sprite's position I guess
    _sprite.setPosition(static_cast<sf::Vector2<float>>(_position));
}
