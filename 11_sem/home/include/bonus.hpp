#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace arkanoid_game {
class Arkanoid;
}

#include "./paddle.hpp"
#include "./arkanoid.hpp"

namespace arkanoid_game {

class Bonus {
private:
    inline static const float speed = 120;
    inline static const float radius = 15;

    sf::Vector2f m_position;
    float m_time;

public:
    Bonus(sf::Vector2f position);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    void activate(Arkanoid& game);

    bool isColiding(const Paddle& paddle) const;
    // Класс Arkanoid должен быть дружественным, так как он может менять внутреннее объекта-бонуса
    friend class Arkanoid;
};

}