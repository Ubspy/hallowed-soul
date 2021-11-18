/**
 * @file Tests.cpp
 * @author EECS 448 Group 13 2021
 * @brief Implementation of Tests.h
 * @version 0.1
 * @date 2021-11-10
 * 
 */

#include "Tests.h"
#include "../src/Player.h"
#include "../src/GameManager.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int Tests::testNum {0};

void Tests::runTests()
{
    testAndPrint("Player animations", testPlayerAnimations);
    testAndPrint("Enemy health bar", testEnemyHealthBars);
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

bool Tests::testPlayerAnimations()
{
    // Create a player
    Player p;
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
    p.onDraw();
    // Assert that the walking up sprite is selected
    if (p.getSprite().getTextureRect().top != upWalkRow * p.getHeight())
        return false;
    
    // Move left
    p.moveInDirection({-1, 0});
    p.update(0.1);
    p.onDraw();
    if (p.getSprite().getTextureRect().top != leftWalkRow * p.getHeight())
        return false;

    // Move down
    p.moveInDirection({1, 0});
    p.update(0.1);
    p.onDraw();
    if (p.getSprite().getTextureRect().top != downWalkRow * p.getHeight())
        return false;

    // Move right
    p.moveInDirection({0, 1});
    p.update(0.1);
    p.onDraw();
    if (p.getSprite().getTextureRect().top != rightWalkRow * p.getHeight())
        return false;

    // The animation frame should have changed by now since we moved; assert this
    int secondLeft = p.getSprite().getTextureRect().left;
    if (firstLeft == secondLeft)
        return false;

    return true;
}

bool Tests::testEnemyHealthBars()
{
    WaveManager wave;
    Enemy* e = new Enemy;
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
