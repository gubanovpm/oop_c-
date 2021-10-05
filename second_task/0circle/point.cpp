#include <iostream>
#include <cmath>

#include "point.hpp"

point_t::point_t(float ax, float ay) : x(ax), y(ay) {}
point_t::point_t() : x(0), y(0) {}

float point_t::get_x() const {
	return x;
}

float point_t::get_y() const {
	return y;
}
void point_t::set_x(float x) {
	this->x = x;
}
void point_t::set_y(float y) {
	this->y = y;
}

float point_t::abs() const {
	return sqrtf(x*x + y*y);
}

void point_t::normalize() {
	float pnorm = abs();
	x /= pnorm;
	y /= pnorm;
}

float point_t::distance(const point_t &p) const {
	return sqrtf((p.x - x)*(p.x - x) + (p.y - y)*(p.y - y));
}

point_t point_t::operator+(const point_t &right) const {
	point_t result = {x + right.x, y + right.y};
	return result;
}

point_t point_t::operator*(float a) const {
	point_t result = {a * x, a * y};
	return result;
}

// Дружественные функции класса Point
point_t operator*(float a, const point_t& p) {
	point_t result = {a * p.x, a * p.y};
	return result;
}

std::ostream &operator<<(std::ostream &left, const point_t &right) {
	left << "(" << right.x << ", " << right.y << ")";
	return left;
}