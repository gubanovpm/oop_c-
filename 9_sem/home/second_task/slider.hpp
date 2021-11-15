#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct Slider {
private:
    sf::Text           number_;   // число, которое показывает ползунок
    sf::RectangleShape body_;     // тело ползунка
    sf::RectangleShape slider_;   // ползунок
    sf::Color          color_;    // цвет ползунка
    sf::RenderWindow   *window_;  // в каком окне
    sf::Vector2i       size_;     // какие значения принимает ползунок
    sf::Vector2i       position_; // где располагается относительно экрана
    sf::Vector2i       current_;  // текущее состояние 
public:
    // конструктор ползунка, принимающий все необходимые параметры
    Slider(sf::RenderWindow &window, sf::Font &font, sf::Vector2i position, sf::Vector2i size = sf::Vector2i({0, 100}), sf::Color color = sf::Color::White);
    // 
    void catchEvent(const sf::Event &event);
    // функция вывода в окно ползунка с текущим статусом
    void draw();
};