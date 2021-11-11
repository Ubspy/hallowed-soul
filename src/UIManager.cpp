#include "UIManager.h"
#include <cmath>
#include "GameManager.h"

UIManager::UIManager() 
{

    printf("hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n\n\n");
}

void UIManager::setData(Player &player, sf::RenderWindow &gameWindow, sf::View &view)
{
    _player = &player;
    _gameWindow = &gameWindow;
    _view = &view;
}

void UIManager::onDraw()
{
    _healthBar.draw();
}