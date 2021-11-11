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
#include <SFML/Graphics.hpp>
#include <iostream>

int Tests::testNum {0};

void Tests::runTests()
{
    testAndPrint("Player animations", testPlayerAnimations);
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