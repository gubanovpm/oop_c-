#include "slider.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cfloat>

Slider::Slider(sf::RenderWindow &window, sf::Font &font, sf::Vector2f position, sf::Vector2f size, sf::Color color) {
    state_   = size.x;
    size_    = (sf::Vector2i)size;
    window_  = &window;
    color_   = color;
    lastpos_ = {-1, -1};

    number_.setFont(font);
    number_.setFillColor(_DefaultColor_);
    number_.setCharacterSize(_FontSize_);
    number_.setPosition({(float)(position.x + _BodyLength_ + 2 * _SliderWidth_), (float)(position.y)});
    number_.setString(std::to_string(state_));

    body_.setFillColor(color);
    body_.setPosition(position + sf::Vector2f({0, (float)_SlirderHeight_ / 2 - (float)_BodyHeight_ / 2})); 
    body_.setSize({(float)_BodyLength_, (float)_BodyHeight_});

    slider_.setFillColor(color);
    slider_.setPosition(position);
    slider_.setSize({(float)(_SliderWidth_), (float)(_SlirderHeight_)});
}

bool Slider::isInSlider(sf::Vector2f point) {
    sf::Vector2f sp = slider_.getPosition();
    sf::Vector2f botp {(float)__INT32_MAX__, (float)__INT32_MAX__};
    sf::Vector2f topp { 0, 0};

    sf::Vector2f points[4];
    for (int i = 0; i < 4; ++i) points[i] = sp + slider_.getPoint(i);

    for (int i = 0; i < 4; ++i) {
        if (points[i].x < botp.x || points[i].y < botp.y) botp = points[i];
        if (points[i].x > topp.x || points[i].y > topp.y) topp = points[i];
    }

    // std::cout << botp.x << " " << botp.y << " ;;; " << topp.x << " " << topp.y << " <->  point = " << point.x << " " << point.y << std::endl ;
    return ((point.x > botp.x && point.x < topp.x) && (point.y > botp.y && point.y < topp.y));
}

void Slider::isInBody() {
    sf::Vector2f left  = body_.getPoint(0) + body_.getPosition();
    sf::Vector2f right = body_.getPoint(1) + body_.getPosition();

    sf::Vector2f cur = slider_.getPosition();
    if (cur.x < left.x) slider_.setPosition({left.x, slider_.getPosition().y});
    if (cur.x > right.x) slider_.setPosition({right.x, slider_.getPosition().y});

    // float del = (std::abs(size_.y - size_.x) < 1e-7) ? 1 : size_.y - size_.x ;
    state_ = int((float)(slider_.getPosition().x - body_.getPosition().x ) / _BodyLength_ * (size_.y - size_.x) + size_.x);

}

void Slider::catchEvent(const sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePosition = window_->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        
        if (isInSlider(mousePosition)) {
            isScrolling_ = true;
        }
    }
    if (event.type == sf::Event::MouseMoved && isScrolling_) {
        sf::Vector2f mousePosition = window_->mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
        
            if (lastpos_.x == -1 && lastpos_.y == -1) lastpos_ = mousePosition;
            sf::Vector2f shiftv = {mousePosition.x - lastpos_.x, 0};
            slider_.setPosition(slider_.getPosition() + shiftv);
            isInBody();
            lastpos_ = mousePosition;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        isScrolling_ = false;
    }

}

void Slider::draw() {
    window_->draw(body_  );
    window_->draw(slider_);
    number_.setString(std::to_string((int)state_));
    window_->draw(number_);
}

float Slider::getCurrentValue() const{
    return state_;
}