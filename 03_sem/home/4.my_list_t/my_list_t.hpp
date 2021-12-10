#pragma once
#include <iostream>
#include <cstdlib>

template < typename Data >
struct my_list_t {
private:
	struct node_t {
        node_t() : val_(), next_(nullptr) {}
        node_t(Data value = 0, node_t *next = nullptr) : val_(value), next_(next) {}

    	Data val_;
    	struct node_t* next_;

        friend std::ostream &operator<< (std::ostream &stream, node_t *node_ptr) {
            if (node_ptr != nullptr) stream << "{ " << node_ptr->val_ << " }" ;

            return stream;
        }

	};


	size_t  size_;
    node_t* head_;
public:

    struct iterator_t {
    private:
        node_t *it_;
    public:
        iterator_t(node_t *node_ptr) : it_(node_ptr) {}
        node_t *operator->() {return it_;};

        iterator_t &operator+=(int offset) {
            for (int i = 0 ; i < offset ; ++i) {
                if (it_ == nullptr) return *this;
                it_ = it_->next_;
            }
            return *this;
        }

        friend std::ostream &operator<< (std::ostream &stream, const iterator_t &it) {
            if (it.it_ != nullptr) stream << "{ " << it.it_ << " }" ;
            return stream;
        }
    };

	my_list_t() : size_(0), head_(nullptr) {}
    ~my_list_t() {
        node_t *temp_ptr = head_->next_;
        while (head_ != nullptr) {
            temp_ptr = head_->next_;
            delete head_;

            head_    = temp_ptr;
        } 
    }

    iterator_t begin() {
        return head_;
    }
    iterator_t end() {
        node_t *temp_ptr = head_;
        while (temp_ptr->next_ != nullptr) temp_ptr = temp_ptr->next_;
        return temp_ptr;
    }

    void push_front(Data x) {
        node_t *new_node = new node_t(x, head_);
        head_ = new_node;
        ++size_;
    }

    Data pop_front() {
        if (head_ == nullptr) { std::cout << "Error! Can't remove an element. List is empty!" << std::endl ; exit(1); }

        Data result = head_->val_;
        node_t temp_ptr = head_->next;
        delete head_;
        head_ = temp_ptr;
        --size_;

        return result;
    }

    void insert_after(iterator_t it, Data x) {
        node_t *new_node = new node_t (x, it->next_);
        it->next_ = new_node;
        ++size_;
    }

    Data erase_after(iterator_t &it) {
        if (it->next_ == nullptr) { std::cout << "Error! Can't erase element from list" << std::endl; exit(1); } ;

        node_t *temp_ptr = it->next_;
        it->next_ = temp_ptr->next_;
        Data result = temp_ptr->val_;
        delete temp_ptr;
        --size_;

        return result;
    }

    friend std::ostream &operator<<(std::ostream &stream, const my_list_t &list) { 
        node_t *temp_ptr = list.head_; std::cout << "[ " ;
        while (temp_ptr != nullptr) {
            stream << temp_ptr << " ; " ;
            temp_ptr = temp_ptr->next_;
        }
        stream << "]" ;
        return stream;
    }
};