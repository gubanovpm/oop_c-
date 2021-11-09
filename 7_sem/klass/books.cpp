#include <iostream>
#include <vector>
using std::cout;
using std::endl;

struct Book {
    std::string title;
    std::string author;
    int pages;
    float price;
};

std::ostream &operator<< (std::ostream &stream, Book book) {
    stream << "(" << book.author << " , " << book.title << " , " << book.pages << " , " << book.price << ")" ;
    return stream;
}

// to compile use : g++ books.cpp -o books -std=c++17

int main() {
    std::vector<Book> books {{"In Search of Lost Time", "Marcel Proust", 500, 1200},
                             {"The Odyssey", "Homer", 300, 700},
                             {"The Catcher in the Rye", "Jerome David Salinger", 400, 500},
                             {"Anna Karenina", "Leo Tolstoy", 800, 1000},
                             {"Catch-22", "Joseph Heller", 600, 900},
                             {"Faust", "Johann Goethe", 700, 1100},
                             {"The Castle", "Franz Kafka", 543, 100} };

    for (auto it : books)
        std::cout << it << " " ;
    std::cout << std::endl;

    for (auto it = books.begin(); it != books.end(); ++it)
        std::cout << *it << " " ;
    std::cout << std::endl;

    for (auto &it: books)
        it.price += 134;
    {for (auto it : books) std::cout << it << " " ; std::cout << std::endl; }

    for (auto it = books.begin(); it != books.end(); ++it)
        (*it).price -= 134;
    {for (auto it : books) std::cout << it << " " ; std::cout << std::endl; }

    return 0;
}