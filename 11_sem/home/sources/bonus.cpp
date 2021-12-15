#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../include/arkanoid.hpp"
#include "../include/bonus.hpp"
#include "../include/paddle.hpp"

arkanoid_game::Bonus::Bonus(sf::Vector2f position): m_position(position) {
    m_time = 0;
}

void arkanoid_game::Bonus::update(float dt) {
    m_time += dt;
    m_position.y += speed * dt;
}

bool arkanoid_game::Bonus::isColiding(const Paddle &paddle) const {
    bool result = paddle.getBorder().intersects({m_position.x - radius, m_position.y - radius, 2 * radius, 2 * radius});
    return result;
}

void arkanoid_game::Triple::draw(sf::RenderWindow &window) const {
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
void arkanoid_game::Triple::activate(Arkanoid &game) {
    // Количество шариков до утроения
    int numBalls = game.m_balls.size();
    // Так как мы работаем со связным списком, то придётся использовать итератор
    std::list<Ball>::iterator ball_it = game.m_balls.begin();
    // Проходим итератором по изначальным элементам списка и добавляем новые шарики в список
    // В данном случае простой цикл через итераторы не сработает, так как
    // массив game.m_balls увеличивается в процессе выполнения цикла
    sf::Vector2f initVelocity = {ball_it->velocity.x, ball_it->velocity.y};
    for (int i = 0; i < numBalls; i++) {
        // Выбираем случайный вектор скорости
        float angle = rand() % 1000 * (2 * M_PI / 1000);
        float vx = initVelocity.x * sin(angle);
        float vy = initVelocity.y * cos(angle);
        // Добавляем шарик в список game.m_balls
        game.addBall({game.m_initialBall.radius, (*ball_it).position, {vx, vy}});

        // Делаем то же самое для ещё одного шарика
        angle = rand() % 1000 * (2 * M_PI / 1000);
        vx = initVelocity.x * sin(angle);
        vy = initVelocity.y * cos(angle);
        game.addBall({game.m_initialBall.radius, (*ball_it).position, {vx, vy}});
        // Переходим ко следующему шарику в списке
        ball_it++;
    }
}

void arkanoid_game::BigRocket::activate(Arkanoid &game) {
    if (m_time >= 0) game.getPaddle().size = {1.05f * game.getPaddle().size.x, game.getPaddle().size.y};
}

void arkanoid_game::BigRocket::draw(sf::RenderWindow &window) const {
    static sf::CircleShape shape(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color{100, 200, 100});
    shape.setPosition(m_position);
    window.draw(shape);

    static sf::RectangleShape paddle;
    paddle.setOrigin(10., 2.);
    paddle.setFillColor(sf::Color{0, 255, 255});
    paddle.setPosition(m_position);
    paddle.setSize({20., 4.});
    window.draw(paddle);
}

void arkanoid_game::LitRocket::activate(Arkanoid &game) {
    game.getPaddle().size = { 
        (game.getPaddle().size.x > 50) ? - 15 + game.getPaddle().size.x : game.getPaddle().size.x, game.getPaddle().size.y 
    };
}

void arkanoid_game::LitRocket::draw(sf::RenderWindow &window) const {
    static sf::CircleShape shape(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color{100, 200, 100});
    shape.setPosition(m_position);
    window.draw(shape);

    static sf::RectangleShape paddle;
    paddle.setOrigin(10., 2.);
    paddle.setFillColor(sf::Color{255, 100, 0});
    paddle.setPosition(m_position);
    paddle.setSize({20., 4.});
    window.draw(paddle);
}

void arkanoid_game::SlowBall::activate(Arkanoid &game) {
    m_time = 0;
    for (auto &ball: game.m_balls) {
        ball.velocity = { ball.velocity.x * 0.66f  , ball.velocity.y * 0.66f };
    }
}

bool arkanoid_game::SlowBall::deactivate(Arkanoid &game) {
    std::cout << m_time << std::endl;
    if (m_time > 10) {
        for (auto &ball: game.m_balls) {
            ball.velocity = { ball.velocity.x * 1.5f , ball.velocity.y * 1.5f};
        }
        return true;
    }
    m_position = {-100, 0};
    return false;
}

void arkanoid_game::SlowBall::draw(sf::RenderWindow &window) const {
    static sf::CircleShape shape(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color{100, 200, 100});
    shape.setPosition(m_position);
    window.draw(shape);

    static sf::RectangleShape paddle;
    paddle.setOrigin(2., 10.);
    paddle.setFillColor(sf::Color{255, 100, 0});
    paddle.setPosition(m_position);
    paddle.setSize({4., 20.});
    window.draw(paddle);

    static sf::CircleShape target(radius / std::sqrt(3) , 3);
    target.setOrigin(radius / std::sqrt(3), radius);
    target.setFillColor(sf::Color(255, 100, 0));
    target.setPosition(m_position);
    target.setRotation(180);
    window.draw(target);
}