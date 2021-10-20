#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H
#include <vector>

class WaveManager
{
    private:
        int currentWave;
        int enemyCount;
        std::vector<int> enemies;
    public:
        WaveManager();

        bool waveOver();
        void beginWave();
        void endWave();
        int getWave();
        int getEnemiesRemaining();
        int getEnemy(int n);
};

#endif