#pragma once

#include <iostream>
#include <list>
#include <cmath>

namespace arkanoid_game {
    class Bonus;
}

#include "./common.hpp"
#include "./bonus.hpp"
#include "./ball.hpp"
#include "./brick_grid.hpp"
#include "./paddle.hpp"

namespace arkanoid_game {

class Arkanoid {
private:
    // Константы:
    const sf::Color kBackgroundColor {12, 31, 47};          // Цвет задника
    const unsigned kMaxNumBalls {250};                      // Максимально возможное количество шариков в один момент времени
    const unsigned kMaxNumBonuses {10};                     // Максимально возможное количество бонусов в один момент времени

    enum class GameState {stuck, running, endLose, endWin, sticked};
    // Поля:
    double m_time;                                          // Время, которое прошло с начала игры в секундах
    sf::FloatRect m_border;                                 // Границы игрового поля
    std::list<Ball> m_balls;                                // Связный список всех шариков
    BrickGrid m_brickGrid;                                  // Объект, задающий состояние сетки блоков
    Paddle m_paddle;                                        // Ракетка
    GameState m_gameState;                                  // Состояние игры
    int m_numLives;                                         // Текущее число жизней
    std::list< Bonus* > m_bonuses;                          // Связный список указателей на бонусы ( указатели - для реализации полиформизма ) 
    float m_bonusProbability;                               // Вероятность того, что при разрушении блока выпадет бонус
    Ball m_initialBall {6, {0, 0}, {0, 0}};                 // Макет шарика, используемый для рисова
    sf::Text m_endText;                                     // Текст, который рисуется в конце игры

    char reded   = 0;                                       // количество вызовов огеного бонуса
    char greened = 0;                                       // количество вызовов StickyFingers
    void addRandomBonus(sf::Vector2f position); 
    void handleBallCollisions(Ball &ball);                  // Функция, которая обрабатывает все столкновения шарика



public:
    Arkanoid(sf::FloatRect border, sf::Font &font);

    sf::FloatRect getBorder() const;
    Paddle &getPaddle();
    const BrickGrid &getBrickGrid() const;

    void addBall(const Ball &ball);
    void update(const sf::RenderWindow &window, float dt);  // Эта функция вызывается каждый кадр
    void draw(sf::RenderWindow &window);
    void onMousePressed(sf::Event &event);

    // Класс бонус должен быть дружественным, так как он может менять внутреннее состояние игры
    friend class Bonus        ;
    friend class Triple       ;
    friend class SlowBall     ;
    friend class UnderLine    ;
    friend class SpeedUp      ;
    friend class BurnIt       ;
    friend class StickyFingers;
};

}