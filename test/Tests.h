/**
 * @file Tests.h
 * @author EECS 448 Group 13 2021
 * @brief Header file declaring tests
 * @version 0.1
 * @date 2021-11-10
 * 
 */

#ifndef TESTS_H
#define TESTS_H

class Tests
{
    public:
        void runTests();

    private:
        void testAndPrint(std::string name, bool (Tests::*test) ());
        bool testPlayerAnimations();
        bool testEnemyHealthBars();
        bool testEnemyHitIndicators();
        static int testNum;
};

#endif