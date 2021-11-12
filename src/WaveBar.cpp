#include "WaveBar.h"

void WaveBar::setData(WaveManager* wave, sf::RenderWindow* gameWindow, sf::View* view)
{
    _wave = wave;
    _gameWindow = gameWindow;
    _view = view;
}


void WaveBar::draw()
{
    float enemiesAlive = _wave->getEnemiesAlive();
    float totalEnemies = _wave->getEnemies();
    int currWave = _wave->getWave();
    
    const int lineSize = 2;
    const sf::Vector2<float> viewCenter = _gameWindow->getView().getCenter();
    const sf::Vector2<float> &viewSize = _view->getSize();
    const sf::Vector2<float> barOutterSize{100.f, 5.f};
    const sf::Vector2<float> barInnerSize{barOutterSize.x * (enemiesAlive / totalEnemies), barOutterSize.y};
    const sf::Vector2<int> padding{2 + lineSize, 2 + lineSize};
    const sf::Vector2<float> barPosition{viewCenter.x - padding.x - barOutterSize.x / 2, viewCenter.y + padding.y + barOutterSize.y - viewSize.y / 2};

    // This is the outside grey/black rectangle.
    sf::RectangleShape outsideRect(barOutterSize);
    outsideRect.setPosition(barPosition);
    outsideRect.setFillColor(sf::Color(45, 45, 45, 255));
    outsideRect.setOutlineColor(sf::Color::Black);
    outsideRect.setOutlineThickness(lineSize);
    _gameWindow->draw(outsideRect);

    // This is the inside purple rectangle.
    sf::RectangleShape insideRect(barInnerSize);
    insideRect.setPosition(barPosition);
    insideRect.setFillColor(sf::Color(128, 0, 187, 255));
    _gameWindow->draw(insideRect);

    sf::Text fractionText;
    sf::Font font;

    if (!font.loadFromFile("fonts/Helvetica.ttf"))
    {
        printf("ERROR: font can not be loaded!!");
    }

    // Enemies left text
    fractionText.setFont(font);
    fractionText.setString(std::to_string((int)enemiesAlive)+"/"+std::to_string((int)totalEnemies));
    fractionText.setCharacterSize(lineSize * 2 + barOutterSize.y);
    // fractionText.setCharacterSize(800);
    fractionText.setFillColor(sf::Color::White);
    fractionText.setOutlineColor(sf::Color::Black);
    fractionText.setOutlineThickness(1);

    fractionText.setPosition(sf::Vector2f{barPosition.x - padding.x - (fractionText.getGlobalBounds().left + fractionText.getGlobalBounds().width), barPosition.y + lineSize - (fractionText.getGlobalBounds().top + fractionText.getGlobalBounds().height) / 2});
    _gameWindow->draw(fractionText);

    sf::Text waveText;

    // Current wave number text
    waveText.setFont(font);
    waveText.setString("Wave " + std::to_string(currWave));
    waveText.setCharacterSize(lineSize * 2 + barOutterSize.y);
    waveText.setFillColor(sf::Color::White);
    waveText.setOutlineColor(sf::Color::Black);
    waveText.setOutlineThickness(1);

    waveText.setPosition(sf::Vector2f{barPosition.x + barOutterSize.x / 2 - (waveText.getGlobalBounds().left + waveText.getGlobalBounds().width) / 2, barPosition.y + (lineSize * 2) + (waveText.getGlobalBounds().top + waveText.getGlobalBounds().height) / 2});
    _gameWindow->draw(waveText);


    sf::Text waveText1;
    // Current wave number text
    waveText1.setFont(font);
    
    waveText1.setStyle(sf::Text::Regular);
    waveText1.setString("Wave " + std::to_string(currWave));
    waveText1.setCharacterSize(64);
    waveText1.setFillColor(sf::Color::White);
    waveText1.setOutlineColor(sf::Color::Black);
    waveText1.setOutlineThickness(3);

    waveText1.setPosition(sf::Vector2f{viewCenter.x - (waveText1.getGlobalBounds().left + waveText1.getGlobalBounds().width) / 2, viewCenter.y - (waveText1.getGlobalBounds().top + waveText1.getGlobalBounds().height) / 2});
    _gameWindow->draw(waveText1);
}