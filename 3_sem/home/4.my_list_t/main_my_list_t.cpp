#include "my_list_t.hpp"
/*
int main() {
    List a;
    list_init(&a);

    for (int i = 0; i < 10; ++i)
        list_push_front(&a, i * i);

    list_print(&a);

    Node* pn = a.head->next->next;
    list_insert_after(&a, pn, 123);
    list_insert_after(&a, pn, 654);

    list_print(&a);

    pn = pn->next->next->next;
    list_erase_after(&a, pn);
    list_erase_after(&a, pn);

    list_print(&a);

    list_destroy(&a);
	return 0;
}*/