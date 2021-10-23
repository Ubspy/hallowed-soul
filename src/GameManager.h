#include <SFML/Graphics.hpp>

enum GameState
{
    playing, menu, gameOver, exiting
};

class GameManager
{
    public:
        GameManager();
        ~GameManager();

        void runGame();

    private:
        sf::RenderWindow* _gameWindow;
        // Camera _gameCamera;

        // Player _player;
        GameState _currentState;

        void runFrame();
        void handleInput();
        void checkCollisions();
        void drawFrame();
};
