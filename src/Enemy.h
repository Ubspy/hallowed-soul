#pragma once
#include "Entity.h"

class Enemy : public Entity
{
    private:
        sf::Vector2<float> _playerPos;
        int ammo;
        bool isAlive;
        
    public:
        Enemy();

        void attack();
        void takeDamage(int damage);
        int getHealth();
        int getAmmo();
        bool getIsAlive();
        void spawn(sf::Vector2<float> pos);

        void updatePlayerLocation(sf::Vector2<float> playerPos);
        void onUpdate(float deltaTime);
        void onCollision(Entity &hitEntity) {}

        void kill();
        

        ~Enemy();
};
