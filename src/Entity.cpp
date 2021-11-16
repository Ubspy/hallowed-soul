#include "Entity.h"
#include "GameManager.h"
#include "VectorUtil.h"
#include <iostream>

Entity::Entity() : _currentMoveState {Moving}
{
    // Initialize position and velocity to have a position of <0, 0>
    _position = sf::Vector2<float>(0, 0);
    _velocity = sf::Vector2<float>(0, 0);
 
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

    // Accumulate time here for animation purposes
    animationData.timeAccumulated += deltaTime;
}

void Entity::onDrawBase()
{
    if (animationData.timeAccumulated >= getSecondsPerFrame())
    {
        animationData.timeAccumulated = 0;
        animationData.currentFrame.x++;
        if (_currentMoveState == Moving)
            animationData.currentFrame.x %= animationData.numWalkingFrames;
        else if (_currentMoveState == AttackTriggered)
        {
            animationData.currentFrame.x = 0;
            _currentMoveState = Attacking;
        }
        else if (_currentMoveState == Attacking)
        {
            if (animationData.currentFrame.x == animationData.numAttackingFrames)
            {
                animationData.currentFrame.x = 0;
                _currentMoveState = Moving;
            }
        }
    }
    setSpriteDirection();
    switch (_currentMoveState)
    {
        case Moving:
        {
            setWalkingFrame();
            break;
        }
        case Attacking:
        {
            setAttackingFrame();
            break;
        }
        default: ;
    }
    onDraw();
    updateTextureRect();
    // Default behavior is to just set the sprite's position I guess
    _sprite.setPosition(_position);
}

void Entity::onDraw()
{
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

void Entity::setTexture(std::string path)
{
    // Load texture in from file
    // TODO: Does this need to by dynamic?
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
    //_sprite.setOrigin((int)(_texture.getSize().x / 2), (int)(_texture.getSize().y / 2));

    // Set width and height from the sprite
    _width = _texture.getSize().x / animationData.numCols;
    _height = _texture.getSize().y / animationData.numRows;
    _sprite.setTextureRect({animationData.currentFrame.x * _width, animationData.currentFrame.y * _height, _width, _height});
}

float Entity::getSecondsPerFrame() const
{
    switch (_currentMoveState)
    {
        case Moving:
        {
            const float framesPerPixelTraveled = 0.1;
            float fps = VectorUtil::getVectorMagnitude(_velocity) * framesPerPixelTraveled;
            return 1/fps;
            break;
        }
        case Attacking:
        {
            return 0.05;
            break;
        }
        default:
        {
            return 0.1;
            break;
        }
    }
}

void Entity::updateTextureRect()
{
    sf::Vector2i topLeft {animationData.currentFrame.x * _width, animationData.currentFrame.y * _height};
    _sprite.setTextureRect({topLeft.x, topLeft.y, _width, _height});
}

void Entity::setSpriteDirection()
{
    if (_velocity.y < 0 && -_velocity.y > std::abs(_velocity.x))
        animationData.direction = animationData.Direction::Up;
    else if (_velocity.x < 0 && -_velocity.x > std::abs(_velocity.y))
        animationData.direction = animationData.Direction::Left;
    else if (_velocity.y > 0 && _velocity.y > std::abs(_velocity.x))
        animationData.direction = animationData.Direction::Down;
    else if (_velocity.x > 0 && _velocity.x > std::abs(_velocity.y))
        animationData.direction = animationData.Direction::Right;
}

void Entity::setWalkingFrame()
{
    if (animationData.direction == animationData.Direction::Up)
        animationData.currentFrame.y = animationData.upWalkRow;
    else if (animationData.direction == animationData.Direction::Left)
        animationData.currentFrame.y = animationData.leftWalkRow;
    else if (animationData.direction == animationData.Direction::Down)
        animationData.currentFrame.y = animationData.downWalkRow;
    else if (animationData.direction == animationData.Direction::Right)
        animationData.currentFrame.y = animationData.rightWalkRow;
}

void Entity::setAttackingFrame()
{
    if (animationData.direction == animationData.Direction::Up)
        animationData.currentFrame.y = animationData.upAttackRow;
    else if (animationData.direction == animationData.Direction::Left)
        animationData.currentFrame.y = animationData.leftAttackRow;
    else if (animationData.direction == animationData.Direction::Down)
        animationData.currentFrame.y = animationData.downAttackRow;
    else if (animationData.direction == animationData.Direction::Right)
        animationData.currentFrame.y = animationData.rightAttackRow;
}

void Entity::setAttackState()
{
    _currentMoveState = AttackTriggered;
}

void Entity::onCollision(Entity &hitEntity)
{

}
