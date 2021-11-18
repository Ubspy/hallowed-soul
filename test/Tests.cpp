/**
 * @file Tests.cpp
 * @author EECS 448 Group 13 2021
 * @brief Implementation of Tests.h
 * @version 0.1
 * @date 2021-11-10
 * 
 */

#include <string>
#include "Tests.h"
#include "../src/Player.h"
#include "../src/Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int Tests::testNum {0};

void Tests::runTests()
{
    srand(time(0));
    // testAndPrint("Player walk animations", testPlayerWalkAnimations);
    // testAndPrint("Enemy health bar", testEnemyHealthBars);
    // testAndPrint("Enemies are alive", testEnemyAlive);
    // testAndPrint("Enemies die", testEnemyDead);
    // testAndPrint("Enemies spawn in correct position", testEnemySpawn);
    printf("test");
}

void Tests::testAndPrint(std::string name, bool (Tests::*test) ())
{
    std::cout << "Test " << testNum++ << ": " << name << ": ";
    if ((this->*test)())
    {
        std::cout << "PASSED";
    }
    else
    {
        std::cout << "FAILED";
    }
    std::cout << '\n';
}

bool Tests::testPlayerWalkAnimations()
{
    // Create a player
    Player p(nullptr);
    // Constants about which direction player is in
    const int upWalkRow {8};
    const int leftWalkRow {9};
    const int downWalkRow {10};
    const int rightWalkRow {11};

    // Get current animation frame
    int firstLeft = p.getSprite().getTextureRect().left;

    // Move it up
    p.moveInDirection({0, -1});
    p.update(0.1);
    p.onDrawBase();
    // Assert that the walking up sprite is selected
    if (p.getSprite().getTextureRect().top != upWalkRow * p.getHeight())
        return false;
    
    // Move left
    p.moveInDirection({-1, 0});
    p.update(0.1);
    p.onDrawBase();
    if (p.getSprite().getTextureRect().top != leftWalkRow * p.getHeight())
        return false;

    // Move down
    p.moveInDirection({1, 0});
    p.update(0.1);
    p.onDrawBase();
    if (p.getSprite().getTextureRect().top != downWalkRow * p.getHeight())
        return false;

    // Move right
    p.moveInDirection({0, 1});
    p.update(0.1);
    p.onDrawBase();
    if (p.getSprite().getTextureRect().top != rightWalkRow * p.getHeight())
        return false;

    // The animation frame should have changed by now since we moved; assert this
    int secondLeft = p.getSprite().getTextureRect().left;
    if (firstLeft == secondLeft)
        return false;

    return true;
}

bool Tests::testPlayerAttackAnimations()
{
    Player p(nullptr);
        // Constants about which direction player is in
    const int upAttackRow {12};
    const int leftAttackRow {13};
    const int downAttackRow {14};
    const int rightAttackRow {15};

    // Get current animation frame
    int firstLeft = p.getSprite().getTextureRect().left;

    // Move it up
    p.moveInDirection({0, -1});
    p.attack();
    p.update(0.1);
    p.onDrawBase();
    // Assert that the attacking up sprite is selected
    if (p.getSprite().getTextureRect().top != upAttackRow * p.getHeight())
        return false;
    
    // Move left
    p.moveInDirection({-1, 0});
    p.attack();
    p.update(0.1);
    p.onDrawBase();
    if (p.getSprite().getTextureRect().top != leftAttackRow * p.getHeight())
        return false;

    // Move down
    p.moveInDirection({1, 0});
    p.attack();
    p.update(0.1);
    p.onDrawBase();
    if (p.getSprite().getTextureRect().top != downAttackRow * p.getHeight())
        return false;

    // Move right
    p.moveInDirection({0, 1});
    p.attack();
    p.update(0.1);
    p.onDrawBase();
    if (p.getSprite().getTextureRect().top != rightAttackRow * p.getHeight())
        return false;


    return true;
}

bool Tests::testEnemyHealthBars()
{
    WaveManager wave(nullptr);
    Enemy* e = new Enemy(nullptr);
    int x = wave.getHealthBar(e).getSize().x;
    e->doDamage(20);
    if(wave.getHealthBar(e).getSize().x < x)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool Tests::testEnemyHitIndicators()
{
    return true;
}

bool Tests::testEntityMovement()
{
    Player testPlayer = Player(nullptr);

    sf::Vector2<float> prevPos = testPlayer.getPosition();

    testPlayer.moveInDirection(sf::Vector2<float>(0, 1));

    return testPlayer.getPosition() != prevPos;
}

bool Tests::testEntityDamage()
{
    Player testPlayer = Player(nullptr);

    int prevHealth;

    testPlayer.doDamage(80);

    return testPlayer.getHealth() < prevHealth;
}

bool Tests::testEntityDeath()
{
    Player testPlayer = Player(nullptr);
    testPlayer.kill();

    return !testPlayer.isAlive();
}

bool Tests::testEnemyAlive()
{
    Enemy test = Enemy(nullptr);
    return test.isAlive();
}

bool Tests::testEnemyDead()
{
    Enemy test = Enemy(nullptr);
    test.kill();
    return !test.isAlive();
}

bool Tests::testEnemySpawn()
{
    Enemy test = Enemy(nullptr);
    sf::Vector2<float> pos = sf::Vector2<float>(rand()%2000,rand()%2000);
    test.spawn(pos);
    return test.getPosition()==pos;
}

bool Tests::testEnemyDamage()
{
    Enemy test = Enemy(nullptr);
    int startHP = test.getHealth();
    int damage = rand()%100;
    test.doDamage(damage);
    return test.getHealth()==startHP-damage;
}
