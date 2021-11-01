#include "WaveManager.h"
#include "Enemy.h"
#include <stdexcept>
#include <time.h>
#include <cstdlib>

WaveManager::WaveManager()
{
    currentWave = 0;
    enemyCount = 0;
    aliveEnemyCount =0;
}

void WaveManager::setPlayer(Player &play)
{
    _player = &play;
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
    currentWave++;
    // For now, waves will progress linearly for simple demonstration sake
    enemyCount = currentWave;
    aliveEnemyCount = currentWave;
    // Spawn enemies
    Enemy* temp = nullptr;
    for(int i=0; i<enemyCount; i++)
    {
        temp = new Enemy();
        sf::Vector2<float> spawn;
        bool loop;
        srand(time(0));
        do {
            spawn = sf::Vector2<float> (rand()%1450, rand()%1125);
            if(spawn.x-_player->getPosition().x<100&&spawn.x-_player->getPosition().x>-100
                    &&spawn.y-_player->getPosition().y<100&&spawn.y-_player->getPosition().y>-100)
            {
                loop = true;
            }
            else
            {
                loop = false;
                for(int j=0; j<i; j++)
                {
                    if(spawn.x-enemies.at(j)->getPosition().x<30&&spawn.x-enemies.at(j)->getPosition().x>-30
                            &&spawn.y-enemies.at(j)->getPosition().y<30&&spawn.y-enemies.at(j)->getPosition().y>-30)
                    {
                        loop = true;
                        break;
                    }
                }
            }
        }while(loop);
        temp->spawn(spawn); 
        temp->setPlayer(_player);
        temp->setFriends(enemies);
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

int WaveManager::getEnemies()
{
    return(enemyCount);
}

int WaveManager::getEnemiesAlive()
{
    return(aliveEnemyCount);
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

void WaveManager::updateEnemies(float time)
{
    for(int i=0; i<enemyCount; i++)
    {
        if(enemies.at(i)->getIsAlive())
        {
            enemies.at(i)->update(time);
        }
    }
}

void WaveManager::waveDraw()
{
    for(int i=0; i<enemyCount; i++)
    {
        if(enemies.at(i)->getIsAlive())
        {
            enemies.at(i)->onDraw();
        }
    }
}

sf::RectangleShape WaveManager::getHealthBarBorder(Enemy* e)
{
    const sf::Vector2f barOutterSize{50.f, 5.f};
    const sf::Vector2f barPosition{(e->_position.x)-23, (e->_position.y)-30};
    sf::RectangleShape outsideRect(barOutterSize);
    outsideRect.setPosition(barPosition);
    outsideRect.setFillColor(sf::Color(45, 45, 45, 255));
    outsideRect.setOutlineColor(sf::Color::Black);
    outsideRect.setOutlineThickness(2);
    return outsideRect;

}

sf::RectangleShape WaveManager::getHealthBar(Enemy* e)
{
    const sf::Vector2f barOutterSize{50.f, 5.f};
    const sf::Vector2f barInnerSize{barOutterSize.x * ((float)e->getHealth() / 100), barOutterSize.y};
    const sf::Vector2f barPosition{(e->_position.x)-23, (e->_position.y)-30};
    sf::RectangleShape insideRect(barInnerSize);
    insideRect.setPosition(barPosition);
    insideRect.setFillColor(sf::Color(255, 0, 0, 255));
    return insideRect;
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
