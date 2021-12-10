#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

namespace arkanoid_game {
// Вспомагательные функции для работы с векторами типа sf::Vector2f
float operator*(const sf::Vector2f& first, const sf::Vector2f& second);
float norm(sf::Vector2f a);
float sqnorm(sf::Vector2f a);

}