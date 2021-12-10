#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "../include/common.hpp"

float arkanoid_game::operator*(const sf::Vector2f& first, const sf::Vector2f& second) {
    return first.x * second.x + first.y * second.y;
}

float arkanoid_game::norm(sf::Vector2f a) {
    return std::sqrt(a.x * a.x + a.y * a.y);
}

float arkanoid_game::sqnorm(sf::Vector2f a) {
    return a.x * a.x + a.y * a.y;
}