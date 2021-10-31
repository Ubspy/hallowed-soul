#pragma once

#include <vector>
#include "Enemy.h"
#include "Player.h"

class WaveManager
{
    private:
        int currentWave;
        int enemyCount;
        int aliveEnemyCount;
        std::vector<Enemy*> enemies;
        Player* _player;
    public:
        WaveManager();

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
         * @brief if the current wave is over, ends it and begins anew
         *  calls waveOver, endWave, and beginWave
         */
        void updateWaves();

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

        /**
         * @brief fetches enemy at requested position
         * 
         * @param n enemy number
         * 
         * @return returns a pointer to the requested enemy
         */
        Enemy* getEnemy(int n);
};
