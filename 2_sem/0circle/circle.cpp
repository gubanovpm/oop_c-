#include <iostream>
#include <cmath>

#include "point.hpp"
#include "circle.hpp"

circle_t::circle_t(const point_t& acenter, float aradius) : 
	center(acenter), 
	radius(aradius) {
}

circle_t::circle_t() : center({}), radius(1.) {}

point_t &circle_t::get_center () { 
	return center; 
}
float circle_t::get_radius() const { 
	return radius; 
}

void circle_t::set_center(const point_t &new_center) { 
	center = new_center; 
}

void circle_t::set_radius(float new_radius) { 
	radius = (new_radius > 0) ? new_radius : 0; 
}

float circle_t::get_area() const {
	return M_PI * radius * radius;
}

float circle_t::get_distance(const point_t &p) const {
	return center.distance(p) - radius;
}

bool circle_t::is_colliding(const circle_t &c) const {
	return (center.distance(c.center) <= c.get_radius() + radius) ? true : false;
}

void circle_t::move(const point_t &p) {
	center = center + p;
}