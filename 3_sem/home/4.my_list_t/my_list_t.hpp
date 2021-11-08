#pragma once
#include <iostream>
#include <cstdlib>

template < typename Data >
struct my_list_t {
public:
	my_list_t() : size_(0), head_(nullptr) {}

private:
	struct node_t {
    	Data val_;
    	struct node_t* next_;
	};

	size_t  size_;
    node_t* head_;
};

/*
void list_push_front(List* pl, Data x)
{
    // Выделяем новый элемент и задаём его значения
    Node* p_new_node = malloc(sizeof(Node));
    p_new_node->val = x;
    p_new_node->next = pl->head;

    // Изменяем head
    pl->head = p_new_node;
    pl->size++;
}

Data list_pop_front(List* pl)
{
    if (pl->head == NULL)
    {
        printf("Error! Can't remove an element. List is empty!\n");
        exit(1);
    }
    // Запоминаем result, чтобы вернуть это значение и temp, чтобы освободить эту память в конце функции
    Node* temp = pl->head;
    Data result = temp->val;

    // head должен указывать на 2-й элемент
    pl->head = pl->head->next;
    free(temp);

    pl->size--;
    return result;
}


void list_insert_after(List* pl, Node* p_node, Data x)
{
    Node* p_new_node = malloc(sizeof(Node));
    p_new_node->val = x;
    p_new_node->next = p_node->next;

    p_node->next = p_new_node;
    pl->size++;
}

Data list_erase_after(List* pl, Node* p_node)
{
    if (p_node == NULL || p_node->next == NULL)
        printf("Error! Can't erase element from list\n");

    Node* temp = p_node->next;
    Data temp_value = p_node->next->val;

    p_node->next = p_node->next->next;
    free(temp);
    pl->size--;
    return temp_value;
}


void list_print(const List* pl)
{
    printf("List: size = %d, elements = { ", pl->size);
    Node* ptr = pl->head;
    while (ptr)
    {
        printf("%d, ", ptr->val);
        ptr = ptr->next;
    }
    printf("\b\b }\n");
}

size_t list_size(const List* pl)
{
    return pl->size;
}

void list_destroy(List* pl)
{
    Node* ptr = pl->head;
    Node* ptr_next;
    while (ptr != NULL)
    {
        ptr_next = ptr->next;
        free(ptr);
        ptr = ptr_next;
    }
    pl->head = NULL;
}
*/