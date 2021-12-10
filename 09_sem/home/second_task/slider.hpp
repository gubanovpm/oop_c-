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
    sf::Vector2f       lastpos_;  // полследнее положение мышки
    float              state_;    // текущее состояние 
    bool               isScrolling_ = false;

    inline static const sf::Color _DefaultColor_ {sf::Color(190, 210, 190)};
    inline static const int _SlirderHeight_ = 25  ;
    inline static const int _SliderWidth_   = 10  ;
    inline static const int _BodyLength_    = 200 ;
    inline static const int _BodyHeight_    = 5   ;
    inline static const int _FontSize_      = 20  ;

    void isInBody();
public:
    // конструктор ползунка, принимающий все необходимые параметры
    Slider(sf::RenderWindow &window, sf::Font &font, sf::Vector2f position, sf::Vector2f size = sf::Vector2f({0, 100}), sf::Color color = sf::Color::White);
    // 
    void catchEvent(const sf::Event &event);
    // функция вывода в окно ползунка с текущим статусом
    void draw();
    // вернуть текущее значение ползунка
    float getCurrentValue() const;

    bool isInSlider(sf::Vector2f point);
};

