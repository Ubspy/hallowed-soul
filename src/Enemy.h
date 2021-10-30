#pragma once
#include "Entity.h"

class Enemy : public Entity
{
    private:
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

        void onUpdate(float deltaTime, sf::Vector2<float> player);
        void update(float deltaTime, sf::Vector2<float> player);
        void onCollision(Entity &hitEntity) {}

        void kill();
        

        ~Enemy();
};
