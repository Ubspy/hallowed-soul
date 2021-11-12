#pragma once

#include <vector>
#include "Enemy.h"
#include "Player.h"

/** Class which is used by GameManager to spawn and update hoards of enemies.
 * 
 * WaveManager exclusively owns the enemies of the game, so it is calling
 * the drawing and updating functions for them.
 */
class WaveManager
{
    private:
        int _currentWave;
        int _enemyCount;
        int _aliveEnemyCount;
        std::vector<Enemy*> _enemies;
        Player* _player;

    public:
        /** WaveManager constructor */
        WaveManager();

        ~WaveManager();
        sf::Text getHitIndicator(Enemy* e);

        /**
         * @brief establishes a player pointer that can be passed to the enemies
         * 
         * @param play player object passed by reference
         */ 
        void setPlayer(Player &play);

        /**
         * @brief determines if the current wave has no remaininig enemies
         * 
         * @return returns true if no enemies remain
         */
        bool waveOver();

        /**
         * @brief begins a new wave when called
         */
        void beginWave();

        /**
         * @brief ends the current wave when called
         */
        void endWave();

        /**
         * @brief gets current wave number
         * 
         * @return current wave
         */
        int getWave();

        /**
         * @brief gets total number of enemies in current wave (alive or dead)
         * 
         * @return total number of enemies
         */
        int getEnemies();

        /**
         * @brief gets number of remaining alive enemies in current wave
         * 
         * @return number of remaining enemies
         */
        int getEnemiesAlive();

        /**
         * @brief gets number of remaining enemies
         * 
         * @return number of remaining enemies
         */
        int getEnemiesRemaining();

        /**
         * @brief Updates the status of the enemies, and the current wave 
         *
         * @param deltaTime The time between the last update and this one (in seconds)
         */
        void update(float deltaTime);

        /**
         * @brief updates alive enemies member variable
         *  calls getEnemiesRemaining
         */
        void updateAliveEnemyCount();

        /**
         * @brief calls upon all enemies to update their position for the next frame
         * 
         * @param time used to adjust position in the event that frames take uneven calculation times
         */
        void updateEnemies(float time);

        /**
         * @brief calls upon all enemies to prepare for drawing
         */
        void waveDraw();

        sf::RectangleShape getHealthBarBorder(Enemy* e);

        sf::RectangleShape getHealthBar(Enemy* e);

        /**
         * @brief fetches enemy at requested position
         * 
         * @param n enemy number
         * 
         * @return returns a pointer to the requested enemy
         */
        Enemy* getEnemy(int n);
        const std::vector<Enemy*> &getEnemiesVec() const;
};
