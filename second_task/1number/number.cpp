#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstring>

#include "number.hpp"

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
number_t::number_t() {
	capacity = 1;
	size = 0;
	data = new char [capacity] {};
}

number_t::number_t(long long int a) {
	long long int temp = a;
	capacity = 0;
	
	while ((temp /= base) != 0)
		++capacity;
	++capacity;
	
	data = new char [capacity] {};
	
	for (int i = 0; i < capacity; ++i) {
		data[i] = a % base;
		a /= base;
	}
	
	size = capacity;
}

number_t::number_t(const char *a){
	size_t offset = 0;
	while (a[offset] != '\0' && a[offset] == '0') 
		++offset;
	const char *str = a + offset;

	size_t t_sz = strlen(str);
	capacity    = t_sz / 2 + t_sz % 2;
	size        = capacity;
	
	data = new char [capacity] {};

	size_t t;
	for (int i = 0; i < capacity - 1; ++i){
		t = 2 * (capacity - i - (t_sz % 2));
		data[i] = (str[t - (2 - t_sz % 2)] - '0') * 10 + (str[t - (1 - t_sz % 2)] - '0') ;
	}

	if (t_sz % 2) {
		data[capacity - 1] = str[0] - '0' ;
	}
	else if (t_sz != 0) {
		data[capacity - 1] = (str[0] - '0') * 10 + (str[ 1] - '0') ;
	}
}

number_t::~number_t() {
	delete [] data;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
number_t &number_t::operator= (const number_t &other) {
	if (this == &other) return *this;

	size     = other.size;
	capacity = other.capacity;

	delete [] data;

	data = new char [capacity] {};

	for (int i = 0; i < size; ++i)
		data[i] = other.data[i];

	return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
number_t::number_t(const number_t &other) {
	size     = other.size;
	capacity = other.capacity;

	data = new char [capacity] {};

	for (int i  = 0; i < other.size; ++i)
		data[i] = other.data[i];
}

number_t::number_t(number_t &&other) {
	size     = other.size;
	capacity = other.capacity;
	std::swap(data, other.data);
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
number_t number_t::operator+= (const number_t &other) {
	size_t remainder = 0, cur = 0, count = 0;

	count = std::max(other.size, size);
	if (capacity <= count) 
		resize(count + 2);
	size = count;

	for (int i = 0; i < count; ++i) {
		cur = 0;
		if (i < other.size)
			cur = other.data[i];
		
		cur += remainder + data[i];

		data[i] = cur % base;
		remainder = cur / base; 
	}
	if (remainder != 0) {
		data[size] += remainder;
		++size;
	}
	return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
number_t operator+ (const number_t &left, const number_t &right) {
	number_t result = left;
	result += right;
	return result;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
number_t number_t::operator*= (const number_t &other) {
	long long int remainder = 0, cur = 0, sz = 2 * std::max(capacity, other.capacity) ;
	number_t sum;
	sum.resize(sz);
	if (capacity < sz)
		resize(sz);
	for (int state = 0; state < other.size; ++state) {
		number_t temp;
		temp.resize(sz);
		temp.size = size + state;
		remainder = 0;
		for (int i = 0; i < size; ++i) {
			cur = data[i] * other.data[state] + remainder;
			temp.data[i + state] = cur % base;
			remainder = cur / base;
		}
		if (remainder != 0) {
			temp.data[size + state] += remainder;
			++temp.size;
		}

		sum += temp;
	}	
	capacity = sum.capacity;
	size     = sum.size;
	std::swap(data, sum.data);

	return *this;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
number_t operator* (const number_t &left, const number_t &right) {
	number_t result = left;
	result *= right;
	return result;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream& stream, const number_t& right) {
	stream << (int)right.data[right.size - 1];

	for (size_t i = 0; i < right.size - 1 ; ++i) {
		stream << std::setfill('0') << std::setw(2) << (int)right.data[right.size - 2 - i];
	}
	return stream;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void number_t::resize(size_t new_size) {
	char *new_data = new char [new_size] {};

	int copy_size = std::min(new_size, size);
	size = copy_size;

	for (int i = 0 ; i < copy_size; ++i)
		new_data[i] = data[i];

	delete [] data;
	
	data = new_data;
	capacity = new_size;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
bool number_t::isEven() const {
	return (!(data[0] % 2));
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void number_t::div2() {
	int remainder = 0, cur = 0;
	for (int i = size - 1; i >= 0; --i) {
		cur = data[i] + remainder * base;
		data[i] = cur / 2 ;
		remainder = cur % 2;
	}
	if (size != 0 && data[size - 1] == 0)
		size--;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
bool number_t::operator== (const number_t &other) const{
	if (other.size != size) return false;
	for (int i = 0; i < size; ++i)
		if (data[i] != other.data[i]) return false;
	return true;
}

bool number_t::operator!= (const number_t &other) const{
	return !(*this == other);
}

bool number_t::operator> (const number_t &other) const {
	if (size > other.size) return true;
	
	for (int i = size - 1; i >= 0; --i)
		if (data[i] > other.data[i]) return true;
			else if (data[i] != other.data[i]) return false;
				else continue;
	return false;
}