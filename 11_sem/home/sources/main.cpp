#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

#include "../include/arkanoid.hpp"

// to compile on Windows with SFML libs installed in MinGW use it (!!! in build directory!!!):
// g++ ../sources/main.cpp ../sources/bonus.cpp ../sources/brick_grid.cpp ../sources/brick.cpp ../sources/arkanoid.cpp ../sources/paddle.cpp ../sources/common.cpp ../sources/ball.cpp -o ARKANOID.exe -lsfml-system -lsfml-window -lsfml-graphics

int main () {
    srand(time(0));
    sf::ContextSettings settings; settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1000, 800, 32), "Arkanoid", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::Clock clock;
        
    sf::Font font;
    if (!font.loadFromFile("../include/consola.ttf")) { std::cout << "Can't load font consola.ttf" << std::endl; std::exit(1); }
    
    arkanoid_game::Arkanoid game({0, 0, 1000, 800}, font);
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        // Обработка событий
        sf::Event event;
        // game.bonusCheck();
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                game.onMousePressed(event);
            }
        }
        window.clear(sf::Color(0, 0, 0));
        // Расчитываем новые координаты и новую скорость шарика
        game.update(window, dt);
        game.draw(window);
        // Отображам всё нарисованное на временном "холсте" на экран
        window.display();
    }
    return EXIT_SUCCESS;
}