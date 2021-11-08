#include "my_pair_t.hpp"

int main() {
	my_pair_t< int, std::string >   a = {777, "Axolotl"}; 
	my_pair_t< std::string, float > b = {"Hippo", 6.45 };

	std::cout << a.first << " " << a.second << std::endl;
	b.first += "potamus";
	b.second = 3.14;
	std::cout << b.first << " " << b.second << std::endl;

	return 0;
}