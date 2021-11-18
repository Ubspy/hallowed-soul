#include "GameManager.h"
#include "../test/Tests.h"
#include "../test/Tests.cpp"
#include <cstring>

/** Creates a GameManager and runs the main game loop. */
int main(int argc, char *argv[])
{
    bool isTesting = false;

    // Handle each command line arg.
    for(int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "--test") == 0)
        {
            isTesting = true;
        }
    }

    // Determine to run either game or tests.
    if (!isTesting)
    {
        GameManager gaming;
        gaming.displayStartScreen();
    }
    else {
        Tests testSuite;
        testSuite.runTests();
    }

    return 0;
}
