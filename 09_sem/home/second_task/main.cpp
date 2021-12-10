#include <iostream>
#include "slider.hpp"

// to compile use: g++ main.cpp slider.cpp -o slider.exe -lsfml-system -lsfml-window -lsfml-graphics
// or just do it used cmake (check in readme.md)

struct Ball {
    sf::Vector2f position;
    float radius;
    bool isChoosen;
    sf::Color color_ = sf::Color::White;

    Ball(sf::Vector2f position, float radius) : position(position), radius(radius) {
    }

    void draw(sf::RenderWindow& window) const {
        sf::CircleShape circle(radius);
        circle.setFillColor(color_);
        circle.setOrigin({radius, radius});
        circle.setPosition(position);
        window.draw(circle);
    }
};

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Selector? Yes!", sf::Style::Default, settings);
    window.setFramerateLimit(144);

    sf::Font font;
    if (!font.loadFromFile("../consolas.ttf")) {
        std::cout << "Can't load button font" << std::endl;
    }

    Slider radius_slider {window, font, sf::Vector2f({100., 100.}), {5, 100}} ;
    Slider red_slider {window, font, sf::Vector2f({100., 200.}), {0, 255}, {255, 0, 0}} ;
    Slider green_slider {window, font, sf::Vector2f({100., 300.}), {0, 255}, {0, 255, 0}} ;
    Slider blue_slider {window, font, sf::Vector2f({100., 400.}), {0, 255}, {0, 0, 255}} ;

    Ball ball = {{600, 300}, 5};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }

            radius_slider.catchEvent(event);
            red_slider.catchEvent(event);
            green_slider.catchEvent(event);
            blue_slider.catchEvent(event);
            ball.radius = radius_slider.getCurrentValue();
            ball.color_ = { (sf::Uint8)red_slider.getCurrentValue(), (sf::Uint8)green_slider.getCurrentValue(), (sf::Uint8)blue_slider.getCurrentValue() } ;

            window.clear(sf::Color::Black);
            radius_slider.draw();
            red_slider.draw();
            green_slider.draw();
            blue_slider.draw();
            ball.draw(window);
            window.display();
        }
    }

    return 0;
}