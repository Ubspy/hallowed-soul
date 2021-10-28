#include "WaveManager.h"
#include "Enemy.h"
#include <stdexcept>

WaveManager::WaveManager()
{
    currentWave = 1;
    enemyCount = 0;
    aliveEnemyCount =0;
}

bool WaveManager::waveOver()
{
    for(int i=0; i<enemyCount; i++)
    {
        if(enemies.at(i)->getIsAlive())
        {
            return(false);
        }
    }
    return(true);
}

void WaveManager::beginWave()
{
    // For now, waves will progress linearly for simple demonstration sake
    enemyCount = currentWave;
    // Spawn enemies
    Enemy* temp = nullptr;
    for(int i=0; i<enemyCount; i++)
    {
        temp = new Enemy();
        enemies.push_back(temp);
    }
}

void WaveManager::endWave()
{
    // Clear gamestate
    while(enemies.size() > 0)
    {
        delete enemies.at(enemies.size()-1);
        enemies.pop_back();
    }
}

int WaveManager::getWave()
{
    return(currentWave);
}

int WaveManager::getEnemiesRemaining()
{
    int alive = 0;
    for(int i=0; i<enemyCount; i++)
    {
        if(enemies.at(i)->getIsAlive())
        {
            alive++;
        }
    }
    return(alive);
}

void WaveManager::updateWaves()
{
    if(waveOver())
    {
        endWave();
        beginWave();
    }
    else {}
}

void WaveManager::updateAliveEnemyCount()
{
    aliveEnemyCount = getEnemiesRemaining();
}

Enemy* WaveManager::getEnemy(int n)
{
    // Blah blah not how blah blah no enemies blah blah
    if(n<(int)enemies.size())
    {
        return(enemies.at(n));
    }
    // no clue how this is gonna work with enemies, god I wish we used rust
    //return(-1);
    throw std::runtime_error("literally how");
}