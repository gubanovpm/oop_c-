#include <iostream>
#include "number.hpp"

int main() {
	number_t x ("123456\0");
	number_t y = 0ll; 
	number_t z = 9999999999ll;
	z += x;
	std::cout << x << " " << y << " " << z << std::endl;
}