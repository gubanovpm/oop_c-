#include <iostream>
#include <list>
#include <cmath>

#include "../include/common.hpp"
#include "../include/bonus.hpp"
#include "../include/ball.hpp"
#include "../include/brick_grid.hpp"
#include "../include/paddle.hpp"
#include "../include/arkanoid.hpp"

void arkanoid_game::Arkanoid::addRandomBonus(sf::Vector2f position) {
    if (m_bonuses.size() > kMaxNumBonuses) return;
    int max_rand = 10000;
    if      ((rand() % max_rand) * 1.0f / max_rand < m_bonusProbability / Bonus::bonus_count)
        m_bonuses.push_back(new Triple(position));
    else if ((rand() % max_rand) * 1.0f / max_rand < m_bonusProbability / Bonus::bonus_count)
        m_bonuses.push_back(new BigRocket(position));
    else if ((rand() % max_rand) * 1.0f / max_rand < m_bonusProbability / Bonus::bonus_count)
        m_bonuses.push_back(new LitRocket(position));
    else if ((rand() % max_rand) * 1.0f / max_rand < m_bonusProbability / Bonus::bonus_count)
        m_bonuses.push_back(new SlowBall (position));
    else if ((rand() % max_rand) * 1.0f / max_rand < m_bonusProbability * Bonus::bonus_count)
        m_bonuses.push_back(new UnderLine(position));
    else if ((rand() % max_rand) * 1.0f / max_rand < m_bonusProbability / Bonus::bonus_count)
        m_bonuses.push_back(new SpeedUp(position));
    else if ((rand() % max_rand) * 1.0f / max_rand < m_bonusProbability / Bonus::bonus_count)
        m_bonuses.push_back(new BurnIt(position));
    else if ((rand() % max_rand) * 1.0f / max_rand < m_bonusProbability * Bonus::bonus_count)
        m_bonuses.push_back(new StickyFingers(position));
}

void arkanoid_game::Arkanoid::handleBallCollisions(Ball& ball) {
    ball.handleWallsCollision(m_border);
    ball.handlePaddleCollision(m_paddle);

    auto [d, isColiding] = m_balls.front().findClosestPoint(m_paddle.getBorder());
    if (isColiding && m_paddle.isSticky) {
        // lastVelocity = m_balls.front().velocity;
        m_balls.front().velocity = {0., 0.};
    }

    for (auto it: m_bonuses) {
        ball.handlePaddleCollision(it->line_);
    }

    auto indexes = ball.handleBrickGridCollision(m_brickGrid);
    if (indexes.first == -1) return;
    m_brickGrid.deactivateBrick(indexes);
    addRandomBonus(ball.position);
}

arkanoid_game::Arkanoid::Arkanoid(sf::FloatRect border, sf::Font& font) :
    m_time{0.0},
    m_border{border},
    m_paddle{{m_border.left + m_border.width / 2, m_border.top + m_border.height - 100}, {120, 10}},
    m_gameState{GameState::stuck},
    m_numLives{7} {
        float gap = border.width / 10;
        m_brickGrid = BrickGrid({border.left + gap, border.top + gap, border.width - 2 * gap, border.height / 2}, 50, 30);
        m_bonusProbability = 0.1;
        m_endText.setFont(font);
    }

sf::FloatRect arkanoid_game::Arkanoid::getBorder() const {
    return m_border;
}

arkanoid_game::Paddle& arkanoid_game::Arkanoid::getPaddle() {
    return m_paddle;
}

const arkanoid_game::BrickGrid& arkanoid_game::Arkanoid::getBrickGrid() const {
    return m_brickGrid;
}

void arkanoid_game::Arkanoid::addBall(const Ball& ball) {
    if (m_balls.size() < kMaxNumBalls)
        m_balls.push_back(ball);
}

void arkanoid_game::Arkanoid::update(const sf::RenderWindow& window, float dt) {
    m_time += dt;
    // Устанавливаем положение ракетки
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    m_paddle.position.x = mousePosition.x;
    // Обрабатываем шарики
    for (std::list<Ball>::iterator it = m_balls.begin(); it != m_balls.end();) {
        (*it).update(dt);
        handleBallCollisions(*it);
        if ((*it).position.y > m_border.top + m_border.height) it = m_balls.erase(it);
        else ++it;
    }
    // Если шариков нет, то переходи в режим начала игры и уменьшаем кол-во жизней
    if ((m_gameState == GameState::running || m_gameState == GameState::sticked) && m_balls.size() == 0) {
        m_gameState = GameState::stuck;

        m_numLives--;
    }
    // Если жизни кончились, то переходим в состояние конца игры (проигрыш)
    if (m_numLives < 0) {
        m_gameState = GameState::endLose;
    }
    // Если блоки кончились, то переходим в состояние конца игры (победа)
    if (m_brickGrid.getNumActiveBricks() == 0) {
        m_gameState = GameState::endWin;
    }
    // Обрабатываем бонусы
    for (auto it = m_bonuses.begin(); it != m_bonuses.end();) {
        (*it)->update(dt);
        if ((*it)->isColiding(m_paddle)) {
            (*it)->activate(*this);
            if ((*it)->deactivate(*this)) {
                delete (*it);
                it = m_bonuses.erase(it);
            }
            else ++it;
        }
        else if ((*it)->m_position.y > m_border.top + m_border.height) { 
            delete (*it);
            it = m_bonuses.erase(it);
        }
        else ++it;
    }
    for (auto it = m_bonuses.begin(); it != m_bonuses.end();) {
        if ((*it)->m_position.x == -100 && (*it)->deactivate(*this)) {
            delete (*it);
            it = m_bonuses.erase(it);
        }
        else ++it;
    }
}

void arkanoid_game::Arkanoid::draw(sf::RenderWindow& window) {
    // Рисуем задний прямоугольник
    static sf::RectangleShape background {{m_border.width, m_border.height}};
    background.setPosition({m_border.left, m_border.top});
    background.setFillColor(kBackgroundColor);
    window.draw(background);
    // Рисуем блоки
    m_brickGrid.draw(window);
    // Рисуем шарики
    for (Ball& ball : m_balls) {
        ball.draw(window);
    }
    // Рисуем ракетку
    m_paddle.draw(window);
    // Если мы в режиме начала игры, то рисуем шарик на ракетке
    if (m_gameState == GameState::stuck) {
        m_initialBall.position = {m_paddle.position.x, m_paddle.position.y - m_paddle.size.y / 2 - m_initialBall.radius};
        m_initialBall.position = {m_paddle.position.x, m_paddle.position.y - m_paddle.size.y / 2 - m_initialBall.radius};
        m_initialBall.draw(window);
    }

    // Рисуем кол-во жизней вверху слева
    for (int i = 0; i < m_numLives; i++) {
        m_initialBall.position = {m_initialBall.radius * (3 * i + 2), 2 * m_initialBall.radius};
        m_initialBall.draw(window);
    }
    // Рисуем бонусы
    for (Bonus* pbonus : m_bonuses) {
        pbonus->draw(window);
    }
    // При завершении игры рисуем надпись
    if (m_gameState == GameState::endLose || m_gameState == GameState::endWin) {
        if (m_gameState == GameState::endWin) {
            m_endText.setString("You Win!");
            
        }
        // При завершении игры рисуем надпись
        if (m_gameState == GameState::endLose) {
            m_endText.setString("You Lose!");
        }

        m_endText.setCharacterSize(50);
        m_endText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = m_endText.getLocalBounds();
        m_endText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
        m_endText.setPosition({m_border.left + m_border.width / 2, m_border.top + m_border.height / 2});

        window.draw(m_endText);
    }
}

void arkanoid_game::Arkanoid::onMousePressed(sf::Event& event) {
    switch (m_gameState) {
        case GameState::stuck:
            if (event.mouseButton.button == sf::Mouse::Left) {
                m_gameState = GameState::running;
                float velocityAngle = (rand() % 100 + 40) * M_PI / 180;
                float velocityNorm = Ball::initialVelocity;
                sf::Vector2f newPosition = {m_paddle.position.x, m_paddle.position.y - m_paddle.size.y / 2.0f - m_initialBall.radius};
                sf::Vector2f newVelocity = {-velocityNorm * cosf(velocityAngle), -velocityNorm * sinf(velocityAngle)};
                addBall({m_initialBall.radius, newPosition, newVelocity});
            }
            break;
        case GameState::sticked:
            if (event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "why are you gay?" << std::endl; 
                m_gameState = GameState::running;
                std::cout << lastVelocity.x << " and " << lastVelocity.y << std::endl; 
                m_balls.front().velocity = lastVelocity;
            }
            break;
        case GameState::running: break;
        case GameState::endLose: break;
        case GameState::endWin : break;
    }
}