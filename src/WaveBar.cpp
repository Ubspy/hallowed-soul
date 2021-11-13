#include "WaveBar.h"

void WaveBar::setData(WaveManager* wave, sf::RenderWindow* gameWindow, sf::View* view)
{
    _wave = wave;
    _gameWindow = gameWindow;
    _view = view;
    _newWaveMatcher = wave->getWave();
}


void WaveBar::draw(sf::Time frameTime)
{
    
    float enemiesAlive = _wave->getEnemiesAlive();
    float totalEnemies = _wave->getEnemies();
    int currWave = _wave->getWave();

    // Handle if a new wave started or we are already drawing a wave notification, if so draw the notification again.
    if (currWave > _newWaveMatcher)
    {
        _timeElapsed = 0;
        _isDrawingNotif = true;
        _newWaveMatcher = currWave; // maybe remove this and update mem var when anim is done (doing so removes else block)
        drawWaveNotification(frameTime);
    }
    else if (_isDrawingNotif)
    {
        drawWaveNotification(frameTime);
    }

    const int lineSize = 2; // make this a constant?
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


}

void WaveBar::drawWaveNotification(sf::Time frameTime)
{
    // TODO: remove font vars to one place?
    _timeElapsed += frameTime.asSeconds();

    const sf::Vector2<float> viewCenter = _gameWindow->getView().getCenter();
    const sf::Vector2<float> &viewSize = _view->getSize();

    sf::Font font;
    sf::Text waveText;

    if (!font.loadFromFile("fonts/Helvetica.ttf"))
    {
        printf("ERROR: font can not be loaded!!");
    }

    // Current wave number text
    waveText.setFont(font);
    waveText.setString("Wave " + std::to_string(_wave->getWave()));
    waveText.setCharacterSize(64);
    waveText.setOutlineThickness(3);

    // Show wave notifaction for 1 second, then fade away for an additional second.
    if (_timeElapsed <= 1)
    {
        waveText.setCharacterSize((_timeElapsed * 54) + 10);
        waveText.setPosition(sf::Vector2f{viewCenter.x - (waveText.getGlobalBounds().left + waveText.getGlobalBounds().width) / 2,
                                          _timeElapsed * (viewCenter.y - (waveText.getGlobalBounds().top + waveText.getGlobalBounds().height) / 2)});
        waveText.setFillColor(sf::Color::White);
        waveText.setOutlineColor(sf::Color::Black);
    }
    else if (_timeElapsed < 2)
    {
        float dif = 2 - _timeElapsed;
        // Set position to the center of the screen by
        waveText.setPosition(sf::Vector2f{viewCenter.x - (waveText.getGlobalBounds().left + waveText.getGlobalBounds().width) / 2,
                                         viewCenter.y - (waveText.getGlobalBounds().top + waveText.getGlobalBounds().height) / 2});
        waveText.setFillColor(sf::Color(255, 255, 255, dif * 255)); // White with adjusted alpha
        waveText.setOutlineColor(sf::Color(0, 0, 0, dif * 255)); // Black with adjusted alpha
    }
    else
    {
        _isDrawingNotif = false;
        return;
    }

    _gameWindow->draw(waveText);
}