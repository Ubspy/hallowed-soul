#include "WaveManager.h"

WaveManager::WaveManager()
{
    currentWave = 1;
    enemyCount = 0;
}

bool WaveManager::waveOver()
{
    // This is not how I plan to check in final, but enemies don't exist yet
    if(enemyCount == 0)
    {
        return(true);
    }
    return(false);
}

void WaveManager::beginWave()
{
    // Spawn enemies
}

void WaveManager::endWave()
{
    // Clear gamestate
}

int WaveManager::getWave()
{
    return(currentWave);
}

int WaveManager::getEnemiesRemaining()
{
    // This is not how I plan to return in final, but enemies don't exist yet
    return(enemyCount);
}

int WaveManager::getEnemy(int n)
{
    // Blah blah not how blah blah no enemies blah blah
    if(n<enemies.size())
    {
        return enemies.at(n);
    }
    // no clue how this is gonna work with enemies, god I wish we used rust
    return(-1);
}