#pragma once

struct number_t {
private:
	
	static const int base = 100;
	size_t size;
	size_t capacity;
	char* data;

public:
	
	number_t();
	number_t(long long int a);
	number_t(const char *a);
	~number_t();

	number_t(const number_t &other);
	number_t(number_t &&other);
	
	number_t &operator= (const number_t &other);
	number_t operator+= (const number_t &other);
	number_t operator*= (const number_t &other);

	void resize(size_t new_size);
	bool isEven() const ;
	void div2();

	friend number_t operator+ (const number_t &left, const number_t &right);
	friend number_t operator* (const number_t &left, const number_t &right);
	friend std::ostream &operator<<(std::ostream& stream, const number_t& right);
};
