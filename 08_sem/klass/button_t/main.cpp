#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include "button_t.hpp"

void nothing() {
	std::cout << "ya pridumal dlya vas obidnoe prozvishe\n" ;
}

// to compile use : g++ button_t.cpp main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test button");
	sf::CircleShape circle(20);

    circle.setPosition(sf::Vector2f{20, 20});

	button_t button({100, 100}, {200, 200}, {127, 0, 0}, nothing);

	while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)  {
				window.close();
            }
			button.pressed(event, &window);
        }

        //window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

	return 0;
}