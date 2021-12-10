#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../include/arkanoid.hpp"
#include "../include/bonus.hpp"
#include "../include/paddle.hpp"

arkanoid_game::Bonus::Bonus(sf::Vector2f position): m_position(position) {
    m_time = 0;
}

// Двигаем бонус
void arkanoid_game::Bonus::update(float dt) {
    m_time += dt;
    m_position.y += speed * dt;
}

// Рисуем бонус
void arkanoid_game::Bonus::draw(sf::RenderWindow& window) const {
    // Рисуем белый круг
    static sf::CircleShape shape(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color{100, 200, 100});
    shape.setPosition(m_position);
    window.draw(shape);

    float angle = 0;
    // Рисуем 3 шарика на этом круге
    static Ball ball {5, {0, 0}, {0, 0}};
    float ballRotationRadius = 7;
    ball.position = m_position + ballRotationRadius * sf::Vector2f(std::cos(angle), std::sin(angle));
    ball.draw(window);
    angle += 2.0 * M_PI / 3.0;
    ball.position = m_position + ballRotationRadius * sf::Vector2f(std::cos(angle), std::sin(angle));
    ball.draw(window);
    angle += 2.0 * M_PI / 3.0;
    ball.position = m_position + ballRotationRadius * sf::Vector2f(std::cos(angle), std::sin(angle));
    ball.draw(window);
}

// Применяем эффект бонуса (в данном случае - утроение шариков)
void arkanoid_game::Bonus::activate(Arkanoid& game) {
    // Количество шариков до утроения
    int numBalls = game.m_balls.size();
    // Так как мы работаем со связным списком, то придётся использовать итератор
    std::list<Ball>::iterator ball_it = game.m_balls.begin();
    // Проходим итератором по изначальным элементам списка и добавляем новые шарики в список
    // В данном случае простой цикл через итераторы не сработает, так как
    // массив game.m_balls увеличивается в процессе выполнения цикла
    for (int i = 0; i < numBalls; i++) {
        // Выбираем случайный вектор скорости
        float angle = rand() % 1000 * (2 * M_PI / 1000);
        float vx = Ball::initialVelocity * sin(angle);
        float vy = Ball::initialVelocity * cos(angle);
        // Добавляем шарик в список game.m_balls
        game.addBall({game.m_initialBall.radius, (*ball_it).position, {vx, vy}});

        // Делаем то же самое для ещё одного шарика
        angle = rand() % 1000 * (2 * M_PI / 1000);
        vx = Ball::initialVelocity * sin(angle);
        vy = Ball::initialVelocity * cos(angle);
        game.addBall({game.m_initialBall.radius, (*ball_it).position, {vx, vy}});
        // Переходим ко следующему шарику в списке
        ball_it++;
    }
}

bool arkanoid_game::Bonus::isColiding(const Paddle& paddle) const {
    bool result = paddle.getBorder().intersects({m_position.x - radius, m_position.y - radius, 2 * radius, 2 * radius});
    return result;
}
