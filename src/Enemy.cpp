#include "Enemy.h"
#include <cmath>

Enemy::Enemy()
{
    ammo = 0;
    isAlive = true;
    _position = sf::Vector2<float> (0,0);
    _velocity = sf::Vector2<float>(0, 0);
}

void Enemy::attack()
{
    //Attack logic
}

void Enemy::takeDamage(int damage)
{
    _health = _health - damage;
    if(_health<=0)
    {
        // the operator "this" does not exist in c++, just call kill()
        kill();
    }
    else
    {

    }
}

int Enemy::getHealth()
{
    return _health;
}

int Enemy::getAmmo()
{
    return ammo;
}

bool Enemy::getIsAlive()
{
    return isAlive;
}

void Enemy::spawn(sf::Vector2<float> pos)
{
    _position = pos;
}

void Enemy::updatePlayerLocation(sf::Vector2<float> playerPos)
{
    this->_playerPos = playerPos;
}

void Enemy::onUpdate(float deltaTime)
{
    this->_velocity = sf::Vector2<float>(this->_playerPos.x-this->_position.x,
            this->_playerPos.y-this->_position.y);

    printf("x: %f, y: %f\n", this->_velocity.x, this->_velocity.y);
    this->_velocity = this->_velocity / (std::sqrt(this->_velocity.x*this->_velocity.x + this->_velocity.y*this->_velocity.y));
    this->_velocity *= deltaTime * 5000;
}

void Enemy::kill()
{
    isAlive = false;
}

Enemy::~Enemy()
{

}
