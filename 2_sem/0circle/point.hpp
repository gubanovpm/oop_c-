#pragma once

class point_t {
private:
	float x, y;
	
public:
	point_t (float x, float y);
	point_t ();

	float get_x () const;
	float get_y () const;
	void set_x (float x);
	void set_y (float y);

	void normalize ();
	float distance (const point_t &p) const;
	float abs () const;
	point_t operator+ (const point_t &right) const;
	point_t operator* (float a) const;

	friend point_t operator* (float a, const point_t &p);
	friend std::ostream &operator<< (std::ostream &left, const point_t &right);
};