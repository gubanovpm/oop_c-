#pragma once
#include <iostream>

template < typename firstType, typename secondType >
struct my_pair_t {

	my_pair_t() : first(), second() {}
	my_pair_t(firstType f, secondType s) : first(f), second(s) {}

	my_pair_t(const my_pair_t& other) { first = other.first; second = other.second; }
	

	firstType  first ;
	secondType second;
};