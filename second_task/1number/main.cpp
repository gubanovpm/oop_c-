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
	
	std::string begin = "" ;
	std::cin >> begin ;

	number_t current(begin.data()), mx(0ll);
	int steps = 0;

	while (current != number_t(1)) {
		++steps;
		if (current > mx)
			mx = current;
		if (current.isEven()) 
			current.div2();
		else
			current = 3 * current + 1;
	}
	std::cout << "steps = " << steps << " ; max = " << mx << std::endl;

	return 0;
}