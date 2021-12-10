#pragma once
#include <iostream>

template < typename T >
void default_deleter(T* ptr) {
	delete ptr;
}

template < typename T >
void array_deleter(T* ptr) {
	delete [] ptr;
}

template < typename T >
struct my_unique_ptr_t {

	using D = void (*)(T *);

	my_unique_ptr_t(T *ptr = nullptr, D deleter = default_deleter<T>) : 
	 	ptr_(ptr), 
		deleter_(deleter){
	}
	~my_unique_ptr_t() { deleter_(ptr_); }

	T& operator*() const { return *ptr_; }
	T* operator->() const { return ptr_; }
	T& operator[](int offset) { return *(ptr_ + offset); }

	my_unique_ptr_t(const my_unique_ptr_t &x) = delete ; // use allocator
	my_unique_ptr_t &operator=(const my_unique_ptr_t &other) = delete; // use allocator

	T* ptr_;
	D deleter_;
};