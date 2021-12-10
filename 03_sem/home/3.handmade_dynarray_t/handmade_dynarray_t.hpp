#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <initializer_list>

template <typename T>
struct handmade_dynarray_t {
public:
	typedef T* iterator;

	iterator begin() {
		return &values[0];
	}

	iterator end() {
		return &values[size];
	}

	handmade_dynarray_t(size_t initial_capacity)  {
		if (initial_capacity < 0) { std::cout << "handmade_dynarray_t's capacity has to be non-negative integer\n"; exit(1); }
		
		size = 0;
		capacity = initial_capacity;
		values = new T[capacity];
	}

	handmade_dynarray_t() : handmade_dynarray_t(0) {}

	handmade_dynarray_t(std::initializer_list<T> il) {
		size = il.size();
		capacity = size;
		values = new T[capacity];
		std::copy(il.begin(), il.end(), values);
	}
 
	void push_back(T x)  {
		if (size >= capacity) {
			if  (capacity == 0) capacity = 1;
			else                capacity *= 2;

			T* temp = new T[capacity];
			std::copy_n(values, size, temp);
			delete[] values;
			values = temp;
		}
		values[size] = x;
		size += 1;
	}

	void erase(size_t id) {
		if (id < 0 || id >= size) { std::cout << "Error while erasing element from handmade_dynarray_t! Index is out of range\n"; exit(1); }

		for (size_t i = id; i < size - 1; i++)
			values[i] = values[i + 1];
	}

	int is_empty() const {
		return (size == 0);
	}

	size_t get_size() const {
		return size;
	}

	size_t get_capacity() const {
		return capacity;
	}

	T& operator[](size_t id) {
		return values[id];
	}

	T& at(size_t id)  {
		if (id < 0 || id >= size) { std::cout << "Error! handmade_dynarray_t id is out of bounds\n"; std::exit(1); }

		return values[id];
	}

	handmade_dynarray_t& operator=(const handmade_dynarray_t& other) {
		if (&other == this) return *this;

		size = other.size;
		capacity = other.capacity;
		
		delete[] values;
		values = new T[capacity];
		
		for (size_t i = 0; i < size; i++)
			values[i] = other.values[i];
		
		return *this;
	}

	~handmade_dynarray_t() { delete[] values; }

private:
	size_t size;
	size_t capacity;
	T* values;
};