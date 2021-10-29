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

void Enemy::onUpdate(float deltaTime, sf::Vector2<float> player)
{
    this->_velocity = sf::Vector2<float>(player.x-this->_position.x,player.y-this->_position.y);
    this->_velocity = this->_velocity / (std::sqrt(this->_velocity.x*this->_velocity.x + this->_velocity.y*this->_velocity.y));
    this->_velocity *= deltaTime * 50;
}

void Enemy::update(float deltaTime, sf::Vector2<float> player)
{
    // Code borrowed from Entity, but needs to take an additional argument
    if(_health <= 0)
    {
        this->kill();
    }

    // Then we want to update the entity
    this->onUpdate(deltaTime, player);

    // After the update, we want to update the entity's position based off of it's velocity
    this->_position += this->_velocity;

    // The below '/' was added by Diesel, he's a good boy
    // Finally, we draw the entity  /
    this->onDraw();
}

Enemy::~Enemy()
{

}
