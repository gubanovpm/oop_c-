#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "./brick_grid.hpp"
#include "./paddle.hpp"

namespace arkanoid_game {

struct Ball {
    // Константы:
    inline static const float initialVelocity = 700;
    sf::Color color = {246, 213, 92};
    // Поля:
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool isRed   = false;
    bool touched = false;

    sf::Vector2f lostVelocity = {0., 0.};
    sf::Vector2f lostPosition = {0., 0.};
    Ball(float radius, sf::Vector2f position, sf::Vector2f velocity);

    void update(float dt);
    void draw(sf::RenderWindow &window);
    std::pair< sf::Vector2f, bool > findClosestPoint(const sf::FloatRect &rect) const;
    bool handleRectCollision(const sf::FloatRect &rect);
    void handleWallsCollision(sf::FloatRect boundary);
    std::pair<int, int> handleBrickGridCollision(const BrickGrid &brickGrid);
    void handlePaddleCollision(const Paddle &paddle);                                   // Обрабатываем столкновения шарика с ракеткой
};

}