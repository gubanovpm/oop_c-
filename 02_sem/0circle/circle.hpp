#pragma once

class circle_t {
private:
	point_t center;
	float radius;
public:
	circle_t(const point_t& acenter, float aradius);
	circle_t();

	point_t &get_center ();
	float get_radius() const;
	void set_center(const point_t &new_center);
	void set_radius(float new_radius);

	float get_area() const;
	float get_distance(const point_t &p) const;
	bool is_colliding(const circle_t &c) const;
	void move(const point_t &p);

};