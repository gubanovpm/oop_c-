#include "my_unique_ptr_t.hpp"

int main() {

	// use my_unique_ptr<__TYPENAME__> __VARIABLENAME__ = new __TYPENAME__ [?] <- is unavalible, because copyconstructor is deleted, to use it we must have more experience
	// you can set it " = default;" if you think that it is needed
	my_unique_ptr_t<int> variable { new int (10) } ;
	my_unique_ptr_t<int> array    { new int [10] , array_deleter<int>} ;

	for (int i = 0; i < 10; ++i) array[i] = i;
	*variable = 123321; 

	for (int i = 0; i < 10; ++i) std::cout << array[i] << " ";
	std::cout << std::endl << *variable << std::endl;

	return 0;
}