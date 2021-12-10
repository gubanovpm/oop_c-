#include <iostream>
#include <algorithm>
#include <vector>

struct Date {
    int day, month, year;
};

struct Movie {
    std::string title;
    int running_time;
    float rating;
    Date release_date;
};


// Перегруженный оператор для печати структуры Date
std::ostream& operator<<(std::ostream& stream, const Date& right) {
    stream << right.day << "." << right.month << "." << right.year;
    return stream;
}

// Перегруженный оператор для печати структуры Movie
std::ostream& operator<<(std::ostream& stream, const Movie& right) {
    stream << right.title << ". Running time:" << right.running_time 
        <<". Rating: " << right.rating << ". Release date: " << right.release_date;
    return stream;
}

// Перегруженный оператор для печати вектора структур Movie
std::ostream& operator<<(std::ostream& stream, const std::vector<Movie>& array) {
    for (const auto& m : array) {
        if (m.title.length() != 0)
            std::cout << m << std::endl;
    }
    return stream;
}

bool operator<(Date a, Date b) {
    return (a.day + a.month * 30 + a.year * 12 * 30) < 
           (b.day + b.month * 30 + b.year * 12 * 30) ;
}

// to compile use : g++ movies.cpp -o movies --std=c++17
int main() {
    std::vector<Movie> movies {{"The Godfather", 175, 8.735, {14, 3, 1972}},
                          {"The Shawshank Redemption", 142, 9.112, {10, 9, 1994}},
                          {"Fight Club", 175, 8.651, {10, 9, 1999}},
                          {"The Matrix", 131, 8.491, {24, 3, 1999}},
                          {"Pulp Fiction", 154, 8.620, {19, 5, 1994}},
                          {"Citizen Kane", 119, 7.826, {1, 5, 1941}},
                          {"A Clockwork Orange", 137, 7.959, {19, 12, 1971}},
                          {"2001: A Space Odyssey", 149, 7.988, {2, 4, 1968}},
                          {"Finding Nemo", 175, 7.862, {30, 05, 2003}},
                          {"Vzlomat blogerov", 90, 1.029, {10, 11, 2016}} };

    std::sort(movies.begin(), movies.end(), [](Movie a, Movie b) {return a.rating < b.rating ;});
    std::cout << movies << std::endl;

    std::sort(movies.begin(), movies.end(), [](Movie a, Movie b) {return a.title < b.title ;});
    std::cout << movies << std::endl;

    std::sort(movies.begin(), movies.end(), [](Movie a, Movie b) {return a.release_date < b.release_date ;});
    std::cout << movies << std::endl;

    std::vector<int> v {61, 20, 39, 84, 77};
    std::transform(v.begin(), v.end(), v.begin(), [](int a){return a%10;} );
    for (auto i: v) std::cout << i << " "; std::cout << std::endl;

    std::transform(movies.begin(), movies.end(), movies.begin(), [](Movie a) { Movie b = a; --b.rating; return b; } );
    std::cout << movies << std::endl;

    std::transform(movies.begin(), movies.end(), movies.begin(), [](Movie a) { for (int i = 0; i < a.title.length(); i++) a.title[i] = toupper(a.title[i]); return a; } );
    std::cout << movies << std::endl;

    std::vector<Movie> result = {};
    std::copy_if(movies.begin(), movies.end(), std::back_inserter(result), [](Movie a) { return a.rating > 8; });
    std::cout << result << std::endl;

    std::remove_if(movies.begin(), movies.end(), [](Movie a) { return (a.release_date.year >= 1990 && a.release_date.year < 2000); });
    std::cout << movies << std::endl;

    return 0;
}