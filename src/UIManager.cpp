#include "UIManager.h"
#include <cmath>
#include "GameManager.h"

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

void UIManager::drawMap()
{
    // Draw the map background.
    sf::IntRect mapRectSourceSprite(0, 0, 1500, 1125);
    sf::Texture texture;
    texture.loadFromFile("assets/textures/temp_floor_128.png");
    texture.setRepeated(true);
    sf::Sprite mapSprite(texture, mapRectSourceSprite);

    _gameWindow->draw(mapSprite);

    // Draw the tutorial sprite.
    sf::IntRect tutRectSourceSprite(0, 0, 327, 133);
    sf::Texture tutorialTex;
    tutorialTex.loadFromFile("assets/textures/tutorial.png");
    tutorialTex.setRepeated(false);
    sf::Sprite tutSprite(tutorialTex, tutRectSourceSprite);
    tutSprite.setPosition(1280.0 / 2.0 - tutRectSourceSprite.width / 2, 720.0 / 2.0 - tutRectSourceSprite.height);

    _gameWindow->draw(tutSprite);
}