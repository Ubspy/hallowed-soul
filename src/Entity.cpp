#include "Entity.h"
#include "GameManager.h"

Entity::Entity()
    : _position {0, 0}
    , _velocity {0, 0}
    , _width {0}
    , _height {0}
    , _health {100}
{
    // register with the GameManager so that it can update and draw me
    GameManager::entities.push_front(this);
}

Entity::~Entity()
{
    // Un-register with the GameManager so that it doesn't think I exist
    GameManager::entities.remove(this);
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
    // The first of which is we want to update the position using our velocity
    _position += _velocity;

    // Then we want to check for the health
    if(_health <= 0)
    {
        this->kill();
    }

    // We also want to call the overridable function
    this->onUpdate();
}

void Entity::kill()
{

}

void Entity::spawn(sf::Vector2i spawnLocation)
{

}

sf::Sprite& Entity::getSprite()
{
    return _sprite;
}

void Entity::onDraw()
{
    // Default behavior is to just set the sprite's position I guess
    _sprite.setPosition(static_cast<sf::Vector2f>(_position));
}

void Entity::onCollision(Entity* hitEntity) {}

void Entity::onUpdate() {}
