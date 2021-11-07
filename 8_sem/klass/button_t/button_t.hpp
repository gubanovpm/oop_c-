#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

bool check_point_rect_collision(const sf::Vector2i& p, const sf::RectangleShape& rect);

struct point_t {
public:
	int x = 0; int y = 0;
private:
};

struct color_t {
public:
	char r;	char g; char b;
private:
};

struct button_t {
public:
	button_t(point_t ldp, point_t rup, color_t color, void (*executor)());
	void pressed(sf::Event event, sf::RenderWindow *window);
	color_t color_;
	sf::RectangleShape form;
	void (*executor_)();
private:
};