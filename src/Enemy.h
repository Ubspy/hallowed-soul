#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity
{
    private:
        int ammo;
        bool isAlive;
        float _atkTime;
        bool _attacking;
        Player* _player;
        
    public:
        Enemy();

        /**
         * @brief changes enemy health amount
         * 
         * @param damage amount to remove from health
         */
        void takeDamage(int damage);

        /**
         * @brief get current health
         * 
         * @return health
         */
        int getHealth();

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
         * @brief basic AI structure, determines movement/attacks
         * 
         * @param deltaTime time since last frame
         */
        void onUpdate(float deltaTime);

        /**
         * @brief does nothing, exists for pure virtual override
         */
        void onCollision(Entity &hitEntity) {}


        /**
         * @brief kills enemy
         */
        void kill();
        

        ~Enemy();
};
