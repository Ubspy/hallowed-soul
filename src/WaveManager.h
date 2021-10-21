#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H
#include <vector>
#include "Enemy.h"

class WaveManager
{
    private:
        int currentWave;
        int enemyCount;
        std::vector<Enemy*> enemies;
    public:
        WaveManager();

        bool waveOver();
        void beginWave();
        void endWave();
        int getWave();
        int getEnemiesRemaining();
        Enemy* getEnemy(int n);
};

#endif