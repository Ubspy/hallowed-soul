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
    testPlayer.update(0.01);

    return testPlayer.getPosition() != prevPos;
}

bool Tests::testEntityVelocity()
{
    Player testPlayer = Player(nullptr);

    sf::Vector2<float> prevPos = testPlayer.getPosition();

    testPlayer.moveInDirection(sf::Vector2<float>(0, 1));

    return testPlayer.getVelocity() != sf::Vector2<float>(0.0f, 0.0f);

}

bool Tests::testEntityDamage()
{
    Player testPlayer = Player(nullptr);

    int prevHealth;

    testPlayer.doDamage(80);

    return testPlayer.getHealth() < prevHealth;
}

bool Tests::testEntitySpawn()
{
    sf::Vector2<float> spawnLoc = sf::Vector2<float>(56.0f, 340.0f);

    Player testPlayer = Player(nullptr);
    testPlayer.spawn(spawnLoc);

    return testPlayer.getPosition() == spawnLoc;
}

bool Tests::testEntityDeath()
{
    Player testPlayer = Player(nullptr);
    testPlayer.kill();

    return !testPlayer.isAlive();
}

bool Tests::raycastInRange()
{
    std::vector<Entity*> entityVec;

    Player testPlayer1 = Player(&entityVec);
    Player testPlayer2 = Player(&entityVec);

    entityVec.push_back(&testPlayer1);
    entityVec.push_back(&testPlayer2);

    testPlayer1.spawn(sf::Vector2<float>(0, 0));
    testPlayer2.spawn(sf::Vector2<float>(100, 100));
    Entity* hit = testPlayer1.rayCast(sf::Vector2<float>(145, 145));

    return hit != nullptr;
}

bool Tests::raycastOutOfRange()
{
    std::vector<Entity*> entityVec;

    Player testPlayer1 = Player(&entityVec);
    Player testPlayer2 = Player(&entityVec);

    entityVec.push_back(&testPlayer1);
    entityVec.push_back(&testPlayer2);

    testPlayer1.spawn(sf::Vector2<float>(0, 0));
    testPlayer2.spawn(sf::Vector2<float>(200, 200));
    Entity* hit = testPlayer1.rayCast(sf::Vector2<float>(145, 145));

    return hit == nullptr;
}

bool Tests::testUnitVector()
{
    // TODO: May not work idk
    sf::Vector2<float> toTest = sf::Vector2<float>(2.0f, 2.0f);
    return VectorUtil::getVectorMagnitude(toTest) == std::sqrt(8);
}

bool Tests::testVectorMagnitude()
{
    sf::Vector2<float> toTest = sf::Vector2<float>(2.0f, 2.0f);
    return VectorUtil::getVectorMagnitude(VectorUtil::getUnitVector(toTest)) == 1.0f;
}
