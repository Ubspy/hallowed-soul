#pragma once

#include <vector>
#include "Enemy.h"

class WaveManager
{
    private:
        int currentWave;
        int enemyCount;
        int aliveEnemyCount;
        std::vector<Enemy*> enemies;
    public:
        WaveManager();

        bool waveOver();
        void beginWave(sf::Vector2<float> player);
        void endWave();
        int getWave();
        int getEnemies();
        int getEnemiesRemaining();
        void updateWaves(sf::Vector2<float> player);
        void updateAliveEnemyCount();
        void updateEnemies(float time, sf::Vector2<float> player);
        void waveDraw();
        Enemy* getEnemy(int n);
};
