#pragma once

#include <vector>
#include <cmath>

#include "Entity.h"
#include "Player.h"

/** Enemy class */
class Enemy : public Entity
{
    private:
        int ammo;
        float _atkTime;
        bool _attacking;
        Player* _player;
        std::vector<Enemy*>* friends;
        
    public:
        Enemy();

        /**
         * @brief changes enemy health amount
         * 
         * @param damage amount to remove from health
         */
        void takeDamage(int damage);

        /**
         * @brief get current ammo
         *  note: ammo not currently in use
         * 
         * @return ammo
         */
        int getAmmo();
        
        /**
         * @brief get if the enemy is alive
         * 
         * @return true if alive
         */
        bool getIsAlive();

        /**
         * @brief sets position to chosen location
         * 
         * @param pos the position chosen to spawn at
         */
        void spawn(sf::Vector2<float> pos);

        /**
         * @brief establishes player pointer
         * 
         * @param playerRef a pointer to the player, as to be sent from WaveManager
         */
        void setPlayer(Player* playerRef);

        /**
         * @brief establishes pointer to other enemies
         * 
         * @param friendRef reference to enemy vector
         */
        void setFriends(std::vector<Enemy*>& friendRef);


        /**
         * @brief basic AI structure, determines movement/attacks
         * 
         * @param deltaTime time since last frame
         */
        void onUpdate(float deltaTime);

        /**
         * @brief does nothing, exists for pure virtual override
         */
        void onCollision(Entity &hitEntity) {}

        ~Enemy();
};
