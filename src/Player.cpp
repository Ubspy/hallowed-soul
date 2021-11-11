#include "Player.h"
#include <cmath>

Player::Player() : 
    // Initialize movement vector to <0, 0>
    _moveVec(sf::Vector2<float>(0, 0)),
    _dodgeVec(sf::Vector2<float>(0, 0))
{
    // Set default move state to None
    _currentMoveState = None;
    _texture.loadFromFile("assets/textures/sprite_test.png");
    _width = _texture.getSize().x / animationData.numCols;
    _height = _texture.getSize().y / animationData.numRows;
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0, _height*animationData.upWalkRow, _width, _height});
}

// TODO: Dodging and then moving in a different direction causes it to zip around at mach 6

// Pure virtual function from the Entity class
void Player::onUpdate(float deltaTime)
{
    // At this point, we want to slow down if we are not currently moving 
    // We want to individually check each movement axis to see if we need to slow them
    this->_velocity.x = this->checkDeadMoveAxis(this->_velocity.x, this->_moveVec.x,
            this->_friction, deltaTime);
    this->_velocity.y = this->checkDeadMoveAxis(this->_velocity.y, this->_moveVec.y,
            this->_friction, deltaTime);

    // If there is movement on both axes, then we want to do something special
    if(this->_moveVec.x != 0 && this->_moveVec.y != 0)
    {
        // We want to get the magnitude of the moveVector to make sure we're not moving
        // more when moving diagonally vs laterally
        sf::Vector2<float> moveVecUnit = this->getUnitVector(this->_moveVec);

        // Set the current velocity to the movement vector
        // We want to multiply by the private move speed var so we don't move at
        // a snail's pace, this can be edited for better feeling movement before compile
        this->_velocity.x = (abs(this->_velocity.x + moveVecUnit.x * this->_friction *
            deltaTime)) > this->_moveSpeed ? (this->_velocity.x < 0 ? -this->_moveSpeed :
            this->_moveSpeed) : this->_velocity.x + moveVecUnit.x * this->_friction * deltaTime;       

        this->_velocity.y = (abs(this->_velocity.y + moveVecUnit.y * this->_friction * 
            deltaTime)) > this->_moveSpeed ? (this->_velocity.y < 0 ? -this->_moveSpeed :
            this->_moveSpeed) : this->_velocity.y + moveVecUnit.y * this->_friction * deltaTime;
    }  

    if(this->_dodgeVec.x != 0 || this->_dodgeVec.y != 0)
    {
        // TODO: There needs to be a better way to call this function
        this->_dodgeVec.x = this->checkDeadMoveAxis(this->_dodgeVec.x, 0, this->_dodgeFriction,
                deltaTime);
        this->_dodgeVec.y = this->checkDeadMoveAxis(this->_dodgeVec.y, 0, this->_dodgeFriction,
                deltaTime);

        this->_velocity += this->_dodgeVec;
    } 

    // Only if the current move vector is non zero
    if(this->_moveVec.x != 0 || this->_moveVec.y != 0)
    {
        // Set previous move vector for dodging
        this->_lastMoveVec = this->_moveVec;
    }

    // Reset the movement vector to <0, 0>
    this->_moveVec = sf::Vector2<float>(0, 0);

    animationData.timeAccumulated += deltaTime;
}

void Player::onDraw()
{
    Entity::onDraw();
    if (animationData.timeAccumulated >= getSecondsPerFrame())
    {
        animationData.timeAccumulated = 0;
        animationData.animationFrame = (animationData.animationFrame + 1) % animationData.numWalkingFrames;
    }
    updateTextureRect();
}

void Player::updateTextureRect()
{
    if (_velocity.y < 0)
        animationData.currentRow = animationData.upWalkRow;
    else if (_velocity.x < 0)
        animationData.currentRow = animationData.leftWalkRow;
    else if (_velocity.y > 0)
        animationData.currentRow = animationData.downWalkRow;
    else if (_velocity.x > 0)
        animationData.currentRow = animationData.rightWalkRow;
    sf::Vector2i topLeft {animationData.animationFrame * _width, animationData.currentRow * _height};
    _sprite.setTextureRect({topLeft.x, topLeft.y, _width, _height});
}

float Player::checkDeadMoveAxis(float velAxis, float moveAxis, float friction, float deltaTime)
{
    if(moveAxis == 0) 
    {
        // We want to decrease the x and y components of velocity by the friction each frame
        if(abs(velAxis) - friction * deltaTime >= this->_deadZone)
        {
            return velAxis + (velAxis > 0 ? -friction : friction) * deltaTime;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        // I'm sorry, this is so fucking gross
        // TODO: Fix this mess
        return (abs(velAxis + moveAxis * this->_friction * deltaTime)) >
            this->_moveSpeed / this->getVectorMagnitude(this->_moveVec) ?
            (velAxis < 0 ? -this->_moveSpeed : this->_moveSpeed) /
            this->getVectorMagnitude(this->_moveVec) :
            velAxis + moveAxis * this->_friction * deltaTime;
    }
}

void Player::onCollision(Entity &hitEntity)
{

}

void Player::moveInDirection(sf::Vector2<float> moveDir)
{
    // We want to round the product of the given moveDir
    this->_moveVec += moveDir;

    // We also want to tell the player it was given input, as to now slow its input down
    this->_currentMoveState = MoveState::Moving;
}

void Player::dodgeInDirection(sf::Vector2<float> dodgeDir)
{
    // The first thing we want to do is set the dodge vector now
    this->_dodgeVec = this->getUnitVector(this->_lastMoveVec) * this->_dodgeSpeed;

    // When we dodge, we want to set the state of movement to dodging 
    this->_currentMoveState = MoveState::Dodging;
}

float Player::getVectorMagnitude(sf::Vector2<float> vec) const
{
    // Get the magnitude using the magnitude formula
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2<float> Player::getUnitVector(sf::Vector2<float> vec) const
{
    // Get the unit vector using the above magnitude
    return vec / this->getVectorMagnitude(vec);
}

void Player::attack(Entity* toAttack)
{
    // TODO: Change this
    toAttack->doDamage(40);
}

void Player::counter()
{
    
}

bool Player::isDodging()
{
    if(_currentMoveState==Dodging)
    {
        return(true);
    }
    return(false);
}

const sf::Vector2<float>& Player::getLastMoveDirection() const
{
    return this->_lastMoveVec;
}

const float& Player::getAttackRange() const
{
    return this->_attackRange;
}

float Player::getSecondsPerFrame() const
{
    const float maxFPS = 20;
    float fps = getVectorMagnitude(_velocity) * maxFPS / _moveSpeed;
    return 1/fps;
}
