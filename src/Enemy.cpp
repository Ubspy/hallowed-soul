#include "Enemy.h"

Enemy::Enemy()
{
    health = 0;
    locationX = 0;
    locationY = 0;
    ammo = 0;
    isAlive = false;
}

void Enemy::spawn(int x, int y)
{
    health = 100;
    locationX = x;
    locationY = y;
    ammo = 100;
    isAlive = true;
    //Add to map
}

void Enemy::attack()
{
    //Attack logic
}

void Enemy::takeDamage(int damage)
{
    health = health - damage;
    if(health<=0)
    {
        this.kill();
    }
    else
    {

    }
}

int Enemy::getHealth()
{
    return health;
}

int Enemy::getLocationX()
{
    return locationX;
}

int Enemy::getLocationY()
{
    return locationY;
}

int Enemy::getAmmo()
{
    return ammo;
}

bool Enemy::getIsAlive()
{
    return isAlive;
}

void Enemy::kill()
{
    isAlive = false;
    //remove from map
    ~Enemy();
}

Enemy::~Enemy()
{

}