#include "Enemy.h"

Enemy::Enemy()
{
    ammo = 0;
    isAlive = true;
    _position = sf::Vector2<float> (0,0);
    _velocity = sf::Vector2<float>(0, 0);
    _atkTime = 0;
    _attacking = false;
}

void Enemy::takeDamage(int damage)
{
    _health = _health - damage;
    if(_health<=0)
    {
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

void Enemy::setPlayer(Player* playerRef)
{
    _player = playerRef;
}

void Enemy::setFriends(std::vector<Enemy*>& friendRef)
{
    friends = &friendRef;
}

void Enemy::onUpdate(float deltaTime)
{
    if(((_position.x-_player->getPosition().x<30&&_position.x-_player->getPosition().x>-30
            &&_position.y-_player->getPosition().y<30&&_position.y-_player->getPosition().y>-30)
            &&!_player->isDodging())||_attacking)
    {
        _attacking = true;
        _velocity = sf::Vector2<float> (0,0);
        _atkTime += deltaTime;
        if(_atkTime >= 1)
        {
            _attacking = false;
            _atkTime = 0;
            _player->getAttacked(10);
        }
    }
    else
    {
        this->_velocity = sf::Vector2<float>(this->_player->getPosition().x-this->_position.x,
                this->_player->getPosition().y-this->_position.y);
        for(int i=0; i<friends->size(); i++)
        {
            if((_position.x-friends->at(i)->getPosition().x<35&&_position.x-friends->at(i)->getPosition().x>-35
                    &&_position.y-friends->at(i)->getPosition().y<35&&_position.y-friends->at(i)->getPosition().y>-35)
                    &&friends->at(i)!=this&&friends->at(i)->getIsAlive())
            {
                if(_position.x-friends->at(i)->getPosition().x<30&&_velocity.x>0)
                {
                    _velocity.x = 0;
                }
                if(_position.x-friends->at(i)->getPosition().x>-30&&_velocity.x<0)
                {
                    _velocity.x = 0;
                }
                if(_position.y-friends->at(i)->getPosition().y<30&&_velocity.y>0)
                {
                    _velocity.y = 0;
                }
                if(_position.y-friends->at(i)->getPosition().y>-30&&_velocity.y<0)
                {
                    _velocity.y = 0;
                }
            }
        }
        if(_velocity!=sf::Vector2<float> (0,0))
        {
            this->_velocity = this->_velocity / (std::sqrt(this->_velocity.x*this->_velocity.x + this->_velocity.y*this->_velocity.y));
            this->_velocity *= deltaTime * 5000;
        }
    }
}

void Enemy::kill()
{
    isAlive = false;
}

Enemy::~Enemy()
{

}
