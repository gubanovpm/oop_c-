#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../include/paddle.hpp"

arkanoid_game::Paddle::Paddle(sf::Vector2f position, sf::Vector2f size) : 
    position(position), 
    size(size) {
    }

sf::FloatRect arkanoid_game::Paddle::getBorder() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

void arkanoid_game::Paddle::draw(sf::RenderWindow& window) {
    static sf::RectangleShape shape{};
    shape.setPosition(position - size / 2.0f);
    shape.setSize(size);
    shape.setFillColor(color);
    window.draw(shape);
}