#include "Enemy.h"

Enemy::Enemy(std::vector<Entity*> *entityVec) : Entity(entityVec)
{
    _ammo = 0;
    _atkTime = 0;
    _attacking = false;
    _speed = (float)50;
    _stun = (float)0;
    srand(time(0));

    setTexture("assets/textures/skeleton.png");
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
    sf::Vector2<float> playerDisplacement(this->_player->getPosition().x +
            this->_player->getWidth() - (this->_position.x + this->_width),
            this->_player->getPosition().y + this->_player->getHeight() - 
            (this->_position.y + this->_height));

    if(VectorUtil::getVectorMagnitude(playerDisplacement) >= 50)
    {
        this->_velocity = VectorUtil::getUnitVector(playerDisplacement);
    }
    else
    {
        this->_velocity = sf::Vector2<float>(0, 0);
        
        // If it's the first time the enemy is within range,
        // get the player position to attack in
        this->_attackDir = VectorUtil::getUnitVector(playerDisplacement) * _attackRange;
        this->_attacking = true;
    }
    
    // Entity* hitEntity = this->rayCast(this->_velocity * this->_attackRange);

    if(_attacking)
    {
        _attacking = true;
        _velocity = sf::Vector2<float> (0,0);
        _atkTime += deltaTime;

        // TODO: Scale this with save
        if(_atkTime >= 0.65)
        {
            _attacking = false;
            _atkTime = 0;
            // _player->doDamage(10);
            
            Entity* hitEntity = this->rayCast(this->_attackDir);

            if(hitEntity == _player)
            {
                hitEntity->doDamage((rand()%6)+(rand()%6)+3);
            }
        }
    }
    else
    {
        if(_stun > (float)0)
        {
            _stun -= deltaTime;
            _velocity = sf::Vector2<float>(0,0);
        }
        
        // begin the great if-ening
        // time to answer the age old question: can raycasting deliver more accurate collisions?
        // HOLY FUCKING LAG
        // so the lag issue was solved by removing debug printf statements in entity.cpp. Great Success!
        Entity* ahead = rayCast(sf::Vector2<float>(31,-30));
        if(ahead != nullptr && ahead->getEntityType() == EntityType::ENEMY)
        {
            if(_velocity.x>0)
            {
                _velocity.x=0;
                if(_velocity.y>0){_velocity.y=1;}
                if(_velocity.y<0){_velocity.y=-1;}
            }   
        }
        ahead = rayCast(sf::Vector2<float>(31,30));
        if(ahead != nullptr && ahead->getEntityType() == EntityType::ENEMY)
        {
            if(_velocity.x>0)
            {
                _velocity.x=0;
                if(_velocity.y>0){_velocity.y=1;}
                if(_velocity.y<0){_velocity.y=-1;}
            } 
        }
        ahead = rayCast(sf::Vector2<float>(30,31));
        if(ahead != nullptr && ahead->getEntityType() == EntityType::ENEMY)
        {
            if(_velocity.y>0)
            {
                _velocity.y=0;
                if(_velocity.x>0){_velocity.x=1;}
                if(_velocity.x<0){_velocity.x=-1;}
            } 
        }
        ahead = rayCast(sf::Vector2<float>(-30,31));
        if(ahead != nullptr && ahead->getEntityType() == EntityType::ENEMY)
        {
            if(_velocity.y>0)
            {
                _velocity.y=0;
                if(_velocity.x>0){_velocity.x=1;}
                if(_velocity.x<0){_velocity.x=-1;}
            } 
        }
        ahead = rayCast(sf::Vector2<float>(-31,30));
        if(ahead != nullptr && ahead->getEntityType() == EntityType::ENEMY)
        {
            if(_velocity.x<0)
            {
                _velocity.x=0;
                if(_velocity.y>0){_velocity.y=1;}
                if(_velocity.y<0){_velocity.y=-1;}
            } 
        }
        ahead = rayCast(sf::Vector2<float>(-31,-30));
        if(ahead != nullptr && ahead->getEntityType() == EntityType::ENEMY)
        {
            if(_velocity.x<0)
            {
                _velocity.x=0;
                if(_velocity.y>0){_velocity.y=1;}
                if(_velocity.y<0){_velocity.y=-1;}
            } 
        }
        ahead = rayCast(sf::Vector2<float>(-30,-31));
        if(ahead != nullptr && ahead->getEntityType() == EntityType::ENEMY)
        {
            if(_velocity.y<0)
            {
                _velocity.y=0;
                if(_velocity.x>0){_velocity.x=1;}
                if(_velocity.x<0){_velocity.x=-1;}
            } 
        }
        ahead = rayCast(sf::Vector2<float>(30,-31));
        if(ahead != nullptr && ahead->getEntityType() == EntityType::ENEMY)
        {
            if(_velocity.y<0)
            {
                _velocity.y=0;
                if(_velocity.x>0){_velocity.x=1;}
                if(_velocity.x<0){_velocity.x=-1;}
            } 
        }

        if(_velocity!=sf::Vector2<float> (0,0))
        {
            this->_velocity *= _speed;
        }
    }
}

void Enemy::onDraw()
{
    Entity::onDraw();
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
