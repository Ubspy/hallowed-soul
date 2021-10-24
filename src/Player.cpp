#include "Player.h"

Player::Player() : _moveVec(sf::Vector2<int>(0, 0))
{
    _currentMoveState = None;
}

// Pure virtuan function from the Entity class
void Player::onUpdate()
{
    // At this point, we want to slow down if we are not currently moving 
    if(this->_moveVec.x == 0 && this->_moveVec.y == 0) 
    {
        // TODO: Slow down
        this->_velocity = sf::Vector2<int>(0, 0);
    }

    this->_velocity = this->_moveVec;
    this->_moveVec = sf::Vector2<int>(0, 0);
}

void Player::onCollision(Entity &hitEntity)
{

}

void Player::moveInDirection(sf::Vector2<float> moveDir)
{
    // We want to round the product of the given moveDir and the private moveSpeed var 
    this->_moveVec += sf::Vector2<int>(round(moveDir.x * this->_moveSpeed),
            round(moveDir.y * this->_moveSpeed)); 

    // We also want to tell the player it was given input, as to now slow its input down
    this->_currentMoveState = MoveState::Moving;
}

void Player::dodgeInDirection(sf::Vector2<float> dodgeDir)
{
    
}

void Player::attack()
{

}

void Player::counter()
{

}
