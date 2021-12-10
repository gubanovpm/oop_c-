#pragma once

namespace arkanoid_game {

struct Paddle {
    // Константы:
    inline static const sf::Color color {sf::Color::White};
    
    // Поля:
    sf::Vector2f position;
    sf::Vector2f size;

    // Методы:
    Paddle() {}
    Paddle(sf::Vector2f position, sf::Vector2f size);

    sf::FloatRect getBorder() const;

    void draw(sf::RenderWindow& window);
};

}