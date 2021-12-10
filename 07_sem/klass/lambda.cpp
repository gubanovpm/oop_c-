#include <iostream>
#include <algorithm>

// to compile use: g++ lambda.cpp -o lambda --std=c++17

int main() {

	std::vector v {18, 51, 2, 25, 14, 97, 73};
	std::sort(v.begin(), v.end(), [](int a, int b) {return abs(a) % 10 < abs(b) % 10;});
	std::for_each(v.begin(), v.end(), [](int a) {std::cout << a << " ";}); std::cout << std::endl;
	std::cout << "----------------------------------------------" << std::endl;

	std::vector<std::string> s_v {"Elephant", "Cat", "Zebra", "Dog", "Hippopotamus", "Mouse", "Tiger"};
	std::sort(s_v.begin(), s_v.end(), [](std::string a, std::string b) {return a < b ;});
	std::for_each(s_v.begin(), s_v.end(), [](std::string a) {std::cout << a << " ";}); std::cout << std::endl;

	std::sort(s_v.begin(), s_v.end(), [](std::string a, std::string b) {return a > b ;});
	std::for_each(s_v.begin(), s_v.end(), [](std::string a) {std::cout << a << " ";}); std::cout << std::endl;

	std::sort(s_v.begin(), s_v.end(), [](std::string a, std::string b) {return a.length() < b.length() ;});
	std::for_each(s_v.begin(), s_v.end(), [](std::string a) {std::cout << a << " ";}); std::cout << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
	
	

	return 0;
}