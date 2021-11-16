#include "Enemy.h"

// TODO: Fix this, pass an actual pointer
Enemy::Enemy(std::vector<Entity*> *entityVec) : Entity(entityVec)
{
    _ammo = 0;
    _position = sf::Vector2<float> (0,0);
    _velocity = sf::Vector2<float>(0, 0);
    _atkTime = 0;
    _attacking = false;
    _speed = (float)50;
    _stun = (float)0;

    this->setTexture("assets/textures/test.png");
}

int Enemy::getAmmo()
{
    return _ammo;
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
    _friends = &friendRef;
}

void Enemy::onUpdate(float deltaTime)
{
    if(((_position.x-_player->getPosition().x<30&&_position.x-_player->getPosition().x>-30
            &&_position.y-_player->getPosition().y<30&&_position.y-_player->getPosition().y>-30))
            ||_attacking)
    {
        // If it's the first time the enemy is within range,
        // get the player position to attack in
        if(!this->_attacking)
        {
            this->_attackDir = VectorUtil::getUnitVector(this->_player->getCetnerPosition()
                    - this->getCetnerPosition());
        }

        _attacking = true;
        _velocity = sf::Vector2<float> (0,0);
        _atkTime += deltaTime;

        if(_atkTime >= 1.25)
        {
            _attacking = false;
            _atkTime = 0;
            // _player->doDamage(10);
            
            Entity* hitEntity = this->rayCast(this->_attackDir * this->_attackRange);

            if(hitEntity != nullptr && hitEntity->getEntityType() == PLAYER)
            {
                hitEntity->doDamage(10);
            }
        }
    }
    else
    {
        this->_velocity = sf::Vector2<float>(this->_player->getPosition().x-this->_position.x,
                this->_player->getPosition().y-this->_position.y);
        if(_stun > (float)0)
        {
            _stun -= deltaTime;
            _velocity = sf::Vector2<float>(0,0);
        }
        for(int i=0; i<(int)_friends->size(); i++)
        {
            if((_position.x-_friends->at(i)->getPosition().x<35&&_position.x-_friends->at(i)->getPosition().x>-35
                    &&_position.y-_friends->at(i)->getPosition().y<35&&_position.y-_friends->at(i)->getPosition().y>-35)
                    &&_friends->at(i)!=this&&_friends->at(i)->isAlive())
            {
                if(_position.x-_friends->at(i)->getPosition().x<30&&_velocity.x>0)
                {
                    _velocity.x = 0;
                }
                if(_position.x-_friends->at(i)->getPosition().x>-30&&_velocity.x<0)
                {
                    _velocity.x = 0;
                }
                if(_position.y-_friends->at(i)->getPosition().y<30&&_velocity.y>0)
                {
                    _velocity.y = 0;
                }
                if(_position.y-_friends->at(i)->getPosition().y>-30&&_velocity.y<0)
                {
                    _velocity.y = 0;
                }
            }
        }
        if(_velocity!=sf::Vector2<float> (0,0))
        {
            this->_velocity = VectorUtil::getUnitVector(this->_velocity); 
            this->_velocity *= _speed;
        }
    }
}

void Enemy::doDamage(int damage)
{
    _health -= damage;
    _attacking = false;
    _stun = 0.5;
}

EntityType Enemy::getEntityType()
{
    return EntityType::ENEMY; 
}

Enemy::~Enemy()
{

}
