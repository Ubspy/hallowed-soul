/**
 * @file Tests.h
 * @author EECS 448 Group 13 2021
 * @brief Header file declaring tests
 * @version 0.1
 * @date 2021-11-10
 * 
 */

#pragma once

class Tests
{
    public:
        void runTests();

    private:
        void testAndPrint(std::string name, bool (Tests::*test) ());
        bool testPlayerAnimations();
        bool testEnemyHealthBars();
        bool testEnemyHitIndicators();

        bool testEntityMovement();
        bool testEntityDamage();
        bool testEntityDeath();

        static int testNum;
};
