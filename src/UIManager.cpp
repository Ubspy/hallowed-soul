#include "UIManager.h"
#include <cmath>
#include "GameManager.h"

UIManager::UIManager() 
{

    printf("hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n\n\n");
}

void UIManager::setData(Player &player, WaveManager &wave, sf::RenderWindow &gameWindow, sf::View &view)
{
    _player = &player;
    _wave = &wave;
    _gameWindow = &gameWindow;
    _view = &view;

    _healthBar.setData(_player, _gameWindow, _view);
    _waveBar.setData(_wave, _gameWindow, _view);
}

void UIManager::onDraw(sf::Time frameTime)
{
    _healthBar.draw();
    _waveBar.draw(frameTime);
}