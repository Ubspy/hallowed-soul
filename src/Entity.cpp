#include "Entity.h"
#include "GameManager.h"
#include "VectorUtil.h"
#include <iostream>

Entity::Entity(std::vector<Entity*> *entityVec) : _currentMoveState {Moving}
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

    // Set entity array
    this->_entityVec = entityVec;
}

const sf::Vector2<float>& Entity::getPosition() const
{
    return this->_position;
}

const sf::Vector2<float>& Entity::getVelocity() const
{
    return this->_velocity;
}

const int& Entity::getWidth() const
{
    return this->_width;
}

const int& Entity::getHeight() const
{
    return this->_height;
}

const int& Entity::getHealth() const
{
    return this->_health;
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
    if(_position.x<0){_position.x=0;}
    if(_position.x>1450){_position.x=1450;}
    if(_position.y<0){_position.y=0;}
    if(_position.y>1050){_position.y=1050;}

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

void Entity::spawn(sf::Vector2<float> spawnLocation)
{
    //this->_position = spawnLocation;
}

void Entity::kill()
{
    _isAlive = false;
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

Entity* Entity::rayCast(const sf::Vector2<float> &ray)
{
    // Let's get the center point for the source
    sf::Vector2<float> sourceCenter(this->_position.x + this->_width / 2.0,
        this->_position.y + this->_height / 2.0);

    for(int i = 0; i < this->_entityVec->size(); i++)
    {
        Entity* currentEntity = this->_entityVec->at(i);
        
        // Skip entity if it's the same as this one
        if(this == currentEntity)
        {
            continue;
        }

        // Skip this loop is enemy is dead
        if(!currentEntity->isAlive())
            continue;
    
        // There are four lines to check for intersection here, so we need to check all of them
        // First is the left-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    currentEntity->getPosition().x, (currentEntity->getPosition().y + currentEntity->getHeight()),
                    currentEntity->getPosition().x, currentEntity->getPosition().y))
        {
            return currentEntity;
        }

        // Then check the top-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    currentEntity->getPosition().x, currentEntity->getPosition().y,
                    (currentEntity->getPosition().x + currentEntity->getWidth()), currentEntity->getPosition().y))
        {
           return currentEntity;
        }

        // Then check the right-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    (currentEntity->getPosition().x + currentEntity->getWidth()), currentEntity->getPosition().y,
                    (currentEntity->getPosition().x + currentEntity->getWidth()), (currentEntity->getPosition().y + currentEntity->getHeight())))
        {
            return currentEntity;
        }
        
        // Lastly, the bottom-most line
        if(linesIntersect(sourceCenter.x, sourceCenter.y, (sourceCenter.x + ray.x), (sourceCenter.y + ray.y),
                    currentEntity->getPosition().x, (currentEntity->getPosition().y + currentEntity->getHeight()),
                    (currentEntity->getPosition().x + currentEntity->getWidth()), (currentEntity->getPosition().y + currentEntity->getHeight())))
        {
            return currentEntity;
        }
    }

    return nullptr;
}

bool Entity::linesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
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
}
