#include "Player.h"

Player::Player()
{

}

// Pure virtuan function from the Entity class
void Player::onUpdate()
{

}

void Player::moveInDirection(sf::Vector2<float> moveDir)
{
    // We want to round the product of the given moveDir and the private moveSpeed var 
    this->_velocity = sf::Vector2<int>(round(moveDir.x * this->_moveSpeed),
            round(moveDir.y * this->_moveSpeed)); 
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
