#include <stdexcept>
#include <time.h>
#include <cstdlib>

#include "WaveManager.h"
#include "Enemy.h"

WaveManager::WaveManager(std::vector<Entity*> *entityVec)
{
    _currentWave = 0;
    _enemyCount = 0;
    _aliveEnemyCount =0;
    _entityVec = entityVec;
}

void WaveManager::setPlayer(Player &play)
{
    _player = &play;
}

bool WaveManager::waveOver()
{
    for(int i=0; i<_enemyCount; i++)
    {
        if(_enemies.at(i)->isAlive())
        {
            return(false);
        }
    }
    return(true);
}

void WaveManager::beginWave()
{
    _currentWave++;
    // For now, waves will progress linearly for simple demonstration sake
    _enemyCount = _currentWave;
    _aliveEnemyCount = _currentWave;
    // Spawn enemies
    Enemy* temp = nullptr;

    for(int i=0; i<_enemyCount; i++)
    {
        temp = new Enemy(this->_entityVec);
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
                    if(spawn.x-_enemies.at(j)->getPosition().x<30&&spawn.x-_enemies.at(j)->getPosition().x>-30
                            &&spawn.y-_enemies.at(j)->getPosition().y<30&&spawn.y-_enemies.at(j)->getPosition().y>-30)
                    {
                        loop = true;
                        break;
                    }
                }
            }
        }while(loop);
        temp->spawn(spawn); 
        temp->setPlayer(_player);
        temp->setFriends(_enemies);
        _enemies.push_back(temp);

        printf("%i \n", (int) _entityVec->size());

        _entityVec->push_back(temp);
    }
}

void WaveManager::endWave()
{
    // Clear gamestate
    while(_enemies.size() > 0)
    {
        delete _enemies.at(_enemies.size()-1);
        _enemies.pop_back();
    }

    for(int i = 0; i < _entityVec->size(); i++)
    {
        int erased = 0;

        if(_entityVec->at(i) == nullptr)
        {
            this->_entityVec->erase(this->_entityVec->begin() + i + erased);
            erased++;
        }
    }
}

int WaveManager::getWave()
{
    return(_currentWave);
}

int WaveManager::getEnemies()
{
    return(_enemyCount);
}

int WaveManager::getEnemiesAlive()
{
    return(_aliveEnemyCount);
}

int WaveManager::getEnemiesRemaining()
{
    int alive = 0;
    for(int i=0; i<_enemyCount; i++)
    {
        if(_enemies.at(i)->isAlive())
        {
            alive++;
        }
    }
    return(alive);
}

void WaveManager::update(float deltaTime)
{
    // Update wave if the current wave is over
    if(waveOver())
    {
        endWave();
        beginWave();
    }

    // Update all our enemy objects
    for(int i=0; i<_enemyCount; i++)
    {
        if(_enemies.at(i)->isAlive())
        {
            _enemies.at(i)->update(deltaTime);
        }
    }

    // Update the alive enemy count
    _aliveEnemyCount = getEnemiesRemaining();
}

void WaveManager::waveDraw()
{
    for(int i=0; i<_enemyCount; i++)
    {
        if(_enemies.at(i)->isAlive())
        {
            _enemies.at(i)->onDrawBase();
        }
    }
}

sf::RectangleShape WaveManager::getHealthBarBorder(Enemy* e)
{
    const sf::Vector2<float> barOutterSize{50.f, 5.f};
    const sf::Vector2<float> barPosition{(e->_position.x + (e->getWidth() / 2.0f)) - 23,
        (e->_position.y + (e->getHeight() / 2.0f)) - 30};
    sf::RectangleShape outsideRect(barOutterSize);
    outsideRect.setPosition(barPosition);
    outsideRect.setFillColor(sf::Color(45, 45, 45, 255));
    outsideRect.setOutlineColor(sf::Color::Black);
    outsideRect.setOutlineThickness(2);
    return outsideRect;

}

sf::RectangleShape WaveManager::getHealthBar(Enemy* e)
{
    const sf::Vector2<float> barOutterSize{50.f, 5.f};
    const sf::Vector2<float> barInnerSize{barOutterSize.x * ((float)e->getHealth() / 100.0f), barOutterSize.y};
    const sf::Vector2<float> barPosition{(e->_position.x + (e->getWidth() / 2.0f)) - 23, 
        (e->_position.y + (e->getHeight() / 2.0f)) - 30};
    sf::RectangleShape insideRect(barInnerSize);
    insideRect.setPosition(barPosition);
    insideRect.setFillColor(sf::Color(255, 0, 0, 255));
    return insideRect;
}

sf::Text WaveManager::getHitIndicator(Enemy* e)
{
    
    sf::Text text;
    //std::cout<<time.asSeconds()<<std::endl;
    // Current wave number text
    const sf::Vector2<float> indicatorPosition{(e->getPosition().x)-30, (e->getPosition().y)-30};
    
    text.setString("40");
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Red);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setPosition(indicatorPosition);
    return text;
}


Enemy* WaveManager::getEnemy(int n)
{
    // Blah blah not how blah blah no enemies blah blah
    if(n<(int)_enemies.size())
    {
        return(_enemies.at(n));
    }
    // no clue how this is gonna work with enemies, god I wish we used rust
    //return(-1);
    throw std::runtime_error("literally how");
}

const std::vector<Enemy*>& WaveManager::getEnemiesVec() const
{
    return this->_enemies;
}

WaveManager::~WaveManager()
{
    endWave();
}
