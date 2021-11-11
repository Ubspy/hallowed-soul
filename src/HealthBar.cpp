#include "HealthBar.h"


// HealthBar::HealthBar()
// {
//     fl_health;
// }

// void HealthBar::setData(Player& player, sf::RenderWindow& gameWindow)
// {
//     _player = &player;
//     _gameWindow = &gameWindow;
// }


void HealthBar::draw()
{
    const int lineSize = 2;
    const sf::Vector2<float> viewCenter = _gameWindow->getView().getCenter();
    const sf::Vector2<float> &viewSize = _view->getSize();
    const sf::Vector2<float> barOutterSize{100.f, 10.f};
    const sf::Vector2<float> barInnerSize{barOutterSize.x * ((float)_player->getHealth() / 100), barOutterSize.y};
    const sf::Vector2<int> padding{5 + lineSize, 5 + lineSize};
    const sf::Vector2<float> barPosition{viewCenter.x + padding.x - (viewSize.x / 2), viewCenter.y - padding.y - barOutterSize.y + viewSize.y / 2};

    // This is the outside grey/black rectangle.
    sf::RectangleShape outsideRect(barOutterSize);
    outsideRect.setPosition(barPosition);
    outsideRect.setFillColor(sf::Color(45, 45, 45, 255));
    outsideRect.setOutlineColor(sf::Color::Black);
    outsideRect.setOutlineThickness(lineSize);
    _gameWindow->draw(outsideRect);

    // This is the inside red rectangle.
    sf::RectangleShape insideRect(barInnerSize);
    insideRect.setPosition(barPosition);
    insideRect.setFillColor(sf::Color(255, 0, 0, 255));
    _gameWindow->draw(insideRect);
}