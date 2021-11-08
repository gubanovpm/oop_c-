#include "handmade_dynarray_t.hpp"

int main()
{
	handmade_dynarray_t <int> a = {4, 8, 15, 16, 23, 42};
	handmade_dynarray_t <std::string> b = {"Cat", "Dog", "Nutria", "Echidna", "Turtle", "Coati"};

	for (int elem: a) std::cout << elem << " " ;
	std::cout << std::endl;

	for (std::string& s : b) s = "[" + s + "]";
	for (const std::string& s : b) std::cout << s << std::endl;
}