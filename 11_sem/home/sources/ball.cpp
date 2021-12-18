#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <utility>
#include <iostream>

#include "../include/ball.hpp"
#include "../include/common.hpp"
#include "../include/paddle.hpp"
#include "../include/brick_grid.hpp"

arkanoid_game::Ball::Ball(float radius, sf::Vector2f position, sf::Vector2f velocity) : 
    radius(radius), 
    position(position), 
    velocity(velocity) {
    }

void arkanoid_game::Ball::update(float dt) {
    position += velocity * dt;
}

void arkanoid_game::Ball::draw(sf::RenderWindow& window) {
    static sf::CircleShape shape {};
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(color);
    shape.setPosition(position);
    window.draw(shape);
}

std::pair< sf::Vector2f, bool > arkanoid_game::Ball::findClosestPoint(const sf::FloatRect& rect) const {
    float left   = rect.left;
    float right  = rect.left + rect.width ;
    float bottom = rect.top  + rect.height;
    float top    = rect.top;

    sf::Vector2f d;
    if (position.x < left) d.x = left;
    else if (position.x > right) d.x = right;
    else d.x = position.x;

    if (position.y > bottom) d.y = bottom;
    else if (position.y < top) d.y = top;
    else
        d.y = position.y;

    d -= position;
    bool isColiding = sqnorm(d) < radius * radius;
    return {d, isColiding};
}

bool arkanoid_game::Ball::handleRectCollision(const sf::FloatRect& rect) {
    auto [d, isColiding] = findClosestPoint(rect);
    if (!isColiding)
        return false;

    sf::Vector2f safe_velocity = velocity;
    float closestPointNorm = norm(d);
    // Если расстояние == 0, то это значит, что шарик за 1 фрейм зашёл центром внутрь блока
    // Отражаем шарик от блока
    if (closestPointNorm < 1e-4) {
        if (std::fabs(velocity.x) > std::fabs(velocity.y)) velocity.x *= -1;
        else velocity.y *= -1;
    }
    // Если расстояние != 0, но шарик касается блока, то мы можем просчитать отражение более точно
    // Отражение от углов и по касательной.
    else if (closestPointNorm < radius) {
        position -= d * ((radius - closestPointNorm) / closestPointNorm);
        velocity -= 2.0f * d * (d * velocity) / (closestPointNorm * closestPointNorm);       
    }
    if (isRed) velocity = safe_velocity;
    return true;
}

void arkanoid_game::Ball::handleWallsCollision(sf::FloatRect boundary) {
    if (position.x < boundary.left + radius) {
        position.x = boundary.left + radius;
        velocity.x *= -1;
    }
    if (position.x > boundary.left + boundary.width - radius) {
        position.x = boundary.left + boundary.width - radius;
        velocity.x *= -1;
    }
    if (position.y < boundary.top + radius) {
        position.y = boundary.top + radius;
        velocity.y *= -1;
    }
}

std::pair<int, int> arkanoid_game::Ball::handleBrickGridCollision(const BrickGrid& brickGrid) {
    auto [gridColumns, gridRows]    = brickGrid.getGridSizes();
    auto [brickWidth, brickHeight]  = brickGrid.getBrickSizes();
    auto [left, top, width, height] = brickGrid.getBorder();
    
    // Определяем координаты блоков с которыми шарик может пересечься
    int brickColumnStart  = std::clamp(static_cast<int>((position.x - left - radius) / brickWidth)    ,  0, gridColumns);
    int brickColumnFinish = std::clamp(static_cast<int>((position.x - left + radius) / brickWidth) + 1,  0, gridColumns);
    int brickRowStart     = std::clamp(static_cast<int>((position.y - top  - radius) / brickHeight)   ,  0, gridRows   );
    int brickRowFinish    = std::clamp(static_cast<int>((position.y - top  + radius) / brickHeight) + 1, 0, gridRows   );

    // Если шарик находится вне сетки блоков, то выходим
    if (brickColumnStart == brickColumnFinish || brickRowStart == brickRowFinish) return {-1, -1};

    // Находим ближайший к центру шарика активный пересекаемый шариком блок
    float closestSqNorm = width * width + height * height ;
    std::pair<int, int> closestBrickIndexes = {-1, -1} ;
    for (int i = brickColumnStart; i < brickColumnFinish; ++i) {
        for (int j = brickRowStart; j < brickRowFinish; ++j) {
            if (!brickGrid.isBrickActive({i, j})) continue;

            sf::FloatRect rect {left + i * brickWidth, top + j * brickHeight, brickWidth, brickHeight};
            auto [d, isColiding] = findClosestPoint(rect);
            if (!isColiding) continue;

            if (sqnorm(d) < closestSqNorm) {
                closestSqNorm = sqnorm(d);
                closestBrickIndexes = {i, j};
            }
        }
    }

    // Если такого не нашли, то возвращаем {-1, -1}
    if (closestBrickIndexes.first == -1) return closestBrickIndexes;

    // Упруго сталкиваем шарик с найденым блоком
    sf::FloatRect rect {left + closestBrickIndexes.first  * brickWidth, 
                        top  + closestBrickIndexes.second * brickHeight, brickWidth, brickHeight};
    handleRectCollision(rect);

    // Возвращаем координаты блока в сетки блоков
    return closestBrickIndexes;
}

void arkanoid_game::Ball::handlePaddleCollision(const arkanoid_game::Paddle& paddle) {
    auto [d, isColiding] = findClosestPoint(paddle.getBorder());
    if (!isColiding) return;

    if (paddle.isSticky) {
        if (lostPosition.x == 0. && lostPosition.y == 0) lostPosition = position - paddle.position;
        if (!(velocity.x == 0. && velocity.y == 0)) lostVelocity = velocity ;
        velocity     = {0., 0.}    ;
        position     = paddle.position + lostPosition;
        touched      = true;
        return;
    }
    lostPosition = {0., 0.};
    // Столкновение не упругое
    // Угол отражения зависит от места на ракетке, куда стукнулся шарик
    // Если шарик стукнулся в левую часть ракетки, то он должен полететь влево.
    // Если в правую часть ракетки, то вправо.
    if (!(lostVelocity.x == 0. && lostVelocity.y == 0.)) velocity = lostVelocity;

    const float pi = 3.14159265;
    float velocityAngle = (position.x - paddle.position.x) / (paddle.size.x + 2 * radius) * (0.8 * pi) + pi / 2;
    float velocityNorm = norm(velocity);
    velocity.x = - velocityNorm * std::cos(velocityAngle);
    velocity.y = - velocityNorm * std::sin(velocityAngle);
}