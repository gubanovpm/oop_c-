#include "my_list_t.hpp"

// todo: very strange and poor iterator

int main() {
    my_list_t<int> a;

    for (int i = 0; i < 10; ++i) a.push_front(i * i);
    std::cout << a << std::endl;

    my_list_t<int>::iterator_t it = a.begin();  it += 2;
    std::cout << a.begin() << " " << it << std::endl;
    a.insert_after(it, 123);
    a.insert_after(it, 654);
    std::cout << a << std::endl;

    it += 3;
    a.erase_after(it);
    a.erase_after(it);
    std::cout << a << std::endl;

	return 0;
}