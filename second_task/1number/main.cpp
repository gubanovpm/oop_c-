#include <iostream>
#include "number.hpp"

int main() {

	number_t *Fib = new number_t [1000];
	Fib[0] = 1;
	Fib[1] = 1;
	for (int i = 2; i < 1000; i++)
		Fib[i] = Fib[i - 1] + Fib[i - 2];
	std::cout << Fib[999] << "\n";

	number_t x = 1;
	for (int i = 2; i <= 10; ++i) {
		x *= i;
	}
	std::cout << x << std::endl;

	return 0;
}