#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct ball_t {
    float        radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
};

void conditions_tor     (ball_t &ball, std::pair < float, float > bound);
void conditions_reflect (ball_t &ball, std::pair < float, float > bound);

int main() {
    srand(time(nullptr));
    
    const int width     = 800;
    const int height    = 600;
    const int n_balls   = 10;
    const float delta_t = 0.1;

    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    window.setFramerateLimit(60);

    sf::CircleShape circle(50.0f);
    circle.setFillColor({200, 216, 200});

    std::vector<ball_t> balls;
    balls.resize(n_balls);
    for (int i = 0; i < n_balls; i++) {
        balls[i].radius = 4 + rand() % 8;
        balls[i].position = {(float)(rand() % width), (float)(rand() % height)};
        balls[i].velocity = {(float)(rand() % 100 - 50), (float)(rand() % 100 - 50)};
    }

    balls[9].radius = 50;
    balls[9].position = {float(width / 2), float(height / 2)};
    balls[9].velocity = {20, 20} ;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for (int i = 0; i < n_balls; i++) {
            balls[i].position += balls[i].velocity * delta_t;
            circle.setRadius(balls[i].radius);
            circle.setOrigin(balls[i].radius, balls[i].radius);
            circle.setPosition(balls[i].position);
            conditions_reflect(balls[i], {width, height});
            
            window.draw(circle);
        }

        window.display();
    }

    return 0;
}

void conditions_tor     (ball_t &ball, std::pair < float, float > bound) {
	if (ball.position.y > bound.second) ball.position.y -= bound.second;
	else if (ball.position.y < 0)       ball.position.y += bound.second;

	if (ball.position.x > bound.first) ball.position.x -= bound.first ;
	else if (ball.position.x < 0)      ball.position.x += bound.first ;
}

void conditions_reflect (ball_t &ball, std::pair < float, float > bound) {
    if (ball.position.y + ball.radius > bound.second) { 
        ball.position.y = bound.second - ball.radius;
        ball.velocity.y = -ball.velocity.y;
    }
    else if (ball.position.y - ball.radius < 0) {
        ball.position.y = ball.radius;
        ball.velocity.y = -ball.velocity.y;
    }

    if (ball.position.x + ball.radius > bound.first) { 
        ball.position.x = bound.first - ball.radius;
        ball.velocity.x = -ball.velocity.x;
    }
    else if (ball.position.x - ball.radius < 0) {
        ball.position.x = ball.radius;
        ball.velocity.x = -ball.velocity.x;
    }
}