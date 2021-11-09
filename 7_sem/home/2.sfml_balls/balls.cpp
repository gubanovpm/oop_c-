#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Ball {
    float        radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
};

void boundary_conditions_tor (sf::Vector2f &position, std::pair < float, float > bound);

int main() {
    srand(time(0));
    
    const int width   = 800;
    const int height  = 600;
    const int n_balls = 10;
    const float delta_t = 0.1;

    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    window.setFramerateLimit(24);

    sf::CircleShape circle(50.0f);
    circle.setFillColor({200, 216, 200});

    std::vector<Ball> balls;
    balls.resize(n_balls);
    for (int i = 0; i < n_balls; i++) {
        balls[i].radius = 4 + rand() % 8;
        balls[i].position = {(float)(rand() % width), (float)(rand() % height)};
        balls[i].velocity = {(float)(rand() % 100 - 50), (float)(rand() % 100 - 50)};
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for (int i = 0; i < n_balls; i++) {
            balls[i].position += balls[i].velocity * delta_t;
			boundary_conditions_tor(balls[i].position, {width, height});
            circle.setRadius(balls[i].radius);
            circle.setOrigin(balls[i].radius, balls[i].radius);
            circle.setPosition(balls[i].position);
            
            window.draw(circle);
        }

        window.display();
    }

    return 0;
}

void boundary_conditions_tor (sf::Vector2f &position, std::pair < float, float > bound) {
	if (position.y > bound.second) position.y -= bound.second;
	else if (position.y < 0)       position.y += bound.second;

	if (position.x > bound.first) position.x -= bound.first ;
	else if (position.x < 0)      position.x += bound.first ;
}