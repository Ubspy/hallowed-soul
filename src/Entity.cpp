#include "Entity.h"
#include "GameManager.h"

Entity::Entity()
{
    // Initialize position and velocity to have a position of <0, 0>
    _position = sf::Vector2<float>(0, 0);
    _velocity = sf::Vector2<float>(0, 0);

    // Load texture in from file
    // TODO: Does this need to by dynamic?
    _texture.loadFromFile("assets/textures/test.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin((int)(_texture.getSize().x / 2), (int)(_texture.getSize().y / 2));

    // Initialize entity with 0 size, and default health of 100
    _width = 0;
    _height = 0;
    _health = 100;

    // Entity starts as alive
    this->_isAlive = true;
}

const sf::Vector2<float>& Entity::getPosition() const
{
    return _position;
}

const sf::Vector2<float>& Entity::getVelocity() const
{
    return _velocity;
}

const int& Entity::getWidth() const
{
    return _width;
}

const int& Entity::getHeight() const
{
    return _height;
}

const int& Entity::getHealth() const
{
    return _health;
}

void Entity::update(float deltaTime)
{
    // When we update a frame we want to do a few things
    // First we want to check for the health to see if this entity is dead
    if(_health <= 0)
    {
        this->kill();
    }

    // Then we want to update the entity
    this->onUpdate(deltaTime);

    // After the update, we want to update the entity's position based off of it's velocity
    this->_position += this->_velocity * deltaTime;

    // The below '/' was added by Diesel, he's a good boy
    // Finally, we draw the entity  /
    this->onDraw();
}

void Entity::doDamage(int damage)
{
    this->_health -= damage;
}

bool Entity::isAlive()
{
    return this->_isAlive;
}

void Entity::kill()
{
    _isAlive = false;
}

void Entity::spawn(sf::Vector2<float> spawnLocation)
{

}

const sf::Sprite& Entity::getSprite() const
{
    return _sprite;
}

void Entity::onDraw()
{
    // Default behavior is to just set the sprite's position I guess
    _sprite.setPosition(_position);
}

void Entity::onCollision(Entity &hitEntity)
{

}
