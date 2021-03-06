#pragma once

namespace arkanoid_game {

struct Paddle {
    // Константы:
    sf::Color color = sf::Color::White;
    
    // Поля:
    sf::Vector2f position;
    sf::Vector2f size = {10, 1000};
    bool isSticky = false;

    // Методы:
    Paddle() {}
    Paddle(sf::Vector2f position, sf::Vector2f size);

    sf::FloatRect getBorder() const;

    void draw(sf::RenderWindow& window) const;
};

}