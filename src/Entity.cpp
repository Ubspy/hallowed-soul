#include "Entity.h"
#include "GameManager.h"
#include "VectorUtil.h"

Entity::Entity()
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

    _currentMoveState = Moving;
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
        animationData.currentFrame.x = (animationData.currentFrame.x + 1) % animationData.numWalkingFrames;
    }
    onDraw();
    updateTextureRect();
    // Default behavior is to just set the sprite's position I guess
    _sprite.setPosition(_position);
}

void Entity::onDraw()
{
    setWalkingFrame();
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
    const float framesPerPixelTraveled = 0.1;
    float fps = VectorUtil::getVectorMagnitude(_velocity) * framesPerPixelTraveled;
    return 1/fps;
}

void Entity::updateTextureRect()
{
    sf::Vector2i topLeft {animationData.currentFrame.x * _width, animationData.currentFrame.y * _height};
    _sprite.setTextureRect({topLeft.x, topLeft.y, _width, _height});
}

void Entity::setWalkingFrame()
{
    if (_velocity.y < 0 && -_velocity.y > std::abs(_velocity.x))
        animationData.currentFrame.y = animationData.upWalkRow;
    else if (_velocity.x < 0 && -_velocity.x > std::abs(_velocity.y))
        animationData.currentFrame.y = animationData.leftWalkRow;
    else if (_velocity.y > 0 && _velocity.y > std::abs(_velocity.x))
        animationData.currentFrame.y = animationData.downWalkRow;
    else if (_velocity.x > 0 && _velocity.x > std::abs(_velocity.y))
        animationData.currentFrame.y = animationData.rightWalkRow;
}

void Entity::onCollision(Entity &hitEntity)
{

}
