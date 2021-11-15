#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../context_menu/context_menu.hpp"

// Вспомогательные функции, вычисляет расстояние между двумя точками
float distance(sf::Vector2f start, sf::Vector2f finish) {
    return sqrtf((start.x - finish.x)*(start.x - finish.x) + (start.y - finish.y)*(start.y - finish.y));
}

// Вспомогательные функции, рисует линию на холсте окна window
void drawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f finish, sf::Color color = sf::Color::White) {
    sf::Vertex line_vertices[2] = {sf::Vertex(start, color), sf::Vertex(finish, color)};
    window.draw(line_vertices, 2, sf::Lines);
}


// Вспомагательный класс, описывет шарик
// position - положение шарика; radius - радиус
// is_chosen - говорит о том, выбран ли шарик или нет
struct Ball {
    sf::Vector2f position;
    float radius;
    bool isChoosen;
    sf::Color color_ = sf::Color::White;

    Ball(sf::Vector2f position, float radius) : position(position), radius(radius) {
        isChoosen = false;
    }

    // Метод, который рисует шарик на холстек окна window
    void draw(sf::RenderWindow& window) const {
        // Тут рисуем белый кружочек
        sf::CircleShape circle(radius);
        circle.setFillColor(color_);
        circle.setOrigin({radius, radius});
        circle.setPosition(position);
        window.draw(circle);

        // Если шарик выбран
        if (isChoosen) {
            // То рисуем "уголки"
            const float fraction = 0.7;
            drawLine(window, {position.x - radius, position.y + radius}, {position.x - radius, position.y + radius * fraction});
            drawLine(window, {position.x - radius, position.y + radius}, {position.x - fraction * radius, position.y + radius});

            drawLine(window, {position.x + radius, position.y + radius}, {position.x + radius, position.y + radius * fraction});
            drawLine(window, {position.x + radius, position.y + radius}, {position.x + radius * fraction, position.y + radius});

            drawLine(window, {position.x + radius, position.y - radius}, {position.x + radius * fraction, position.y - radius});
            drawLine(window, {position.x + radius, position.y - radius}, {position.x + radius, position.y - radius * fraction});

            drawLine(window, {position.x - radius, position.y - radius}, {position.x - radius * fraction, position.y - radius});
            drawLine(window, {position.x - radius, position.y - radius}, {position.x - radius, position.y - radius * fraction});
        }
    }
    // Метод, который определяет принадлежит ли шарик выбранной области, и если да, то считает его выбранным
    void inRectangle(sf::RectangleShape &selectionRect) {
        sf::Vector2f sp = selectionRect.getPosition();

        sf::Vector2f botp {(float)__INT32_MAX__, (float)__INT32_MAX__};
        sf::Vector2f topp { 0, 0};

        sf::Vector2f points[4];
        for (int i = 0; i < 4; ++i) points[i] = sp + selectionRect.getPoint(i);

        for (int i = 0; i < 4; ++i) {
            if (points[i].x < botp.x || points[i].y < botp.y) botp = points[i];
            if (points[i].x > topp.x || points[i].y > topp.y) topp = points[i];
        }

        if ((position.x > botp.x && position.x < topp.x) && (position.y > botp.y && position.y < topp.y)) isChoosen = true;
        else isChoosen = false;
    }
};


int main() {
    srand(time(nullptr));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Select, Move, Delete!", sf::Style::Default, settings);
    window.setFramerateLimit(60);


    // Создаём связный список из шариков
    std::list<Ball> balls;

    // Создаём прямоугольник выделения
    sf::RectangleShape selectionRect;
    selectionRect.setFillColor(sf::Color(150, 150, 240, 50));
    selectionRect.setOutlineColor(sf::Color(200, 200, 255));
    // selectionRect.setOutlineThickness(1);

    // Специальная переменная, которая будет показывать, что мы находимся в режиме выделения
    bool isSelecting = false;
    bool isMoving    = false;
    sf::Vector2f lastMousePosition = {-1, -1};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                
                // Если мы находимся в режиме выделения, то меняем прямоугольник выделения
                if (isSelecting) {
                    selectionRect.setSize(mousePosition - selectionRect.getPosition());
                    // При изменении прямоугольника выделения пересчитываем, какие кружки находятся внутри выделенной области
                    for (Ball &b: balls) {
                        b.inRectangle(selectionRect);
                    }
                } 
                // Если мы находимся в режиме перемещения, передвигаем объекты
                if (isMoving) {
                    sf::Vector2f shiftv = mousePosition - lastMousePosition;
                    lastMousePosition = mousePosition;

                    for (Ball &b : balls) 
                        if(b.isChoosen) 
                            b.position += shiftv;
                }
                continue;
            }

            // lastMousePosition = {-1, -1};
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                if (event.mouseButton.button == sf::Mouse::Left) {
                    lastMousePosition = mousePosition;
                    
                    // Если не зажат левый Ctrl, то все выделения снимаются
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        for (Ball &b : balls) 
                            if (b.isChoosen && distance(mousePosition, b.position) < b.radius) { 
                                isMoving = true; 
                                break; 
                            }

                        if (!isMoving)
                            for (Ball &b : balls)
                                b.isChoosen = false;
                    }
                    // Проверяем попал ли курсор в какой-нибудь шарик, если попал - выделяем
                    for (Ball &b : balls) {
                        if (distance(mousePosition, b.position) < b.radius) {
                            b.isChoosen = true;
                            isMoving = true;
                            break;
                        }
                    }
                    // ЛКМ + левый Alt - добавляем новый случайный шарик
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
                        balls.push_back(Ball(mousePosition, 5 + rand() % 40));
                    }
                    // Задаём новое положения прямоугольника выделения
                    if (!isMoving) isSelecting = true;
                    selectionRect.setPosition(mousePosition);
                    selectionRect.setSize({0, 0});
                }
                lastMousePosition = mousePosition;
                continue;
            }

            // SPACE - меняем цвет всех выделенных шариков на случайный
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                sf::Color new_color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
                for (Ball &b : balls) {
                    if (b.isChoosen) b.color_ = new_color;
                }
                continue;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                auto it = balls.begin(), temp = it;
                while (it != balls.end()) {
                    if (it->isChoosen) {
                        temp = std::next(it);
                        balls.erase(it);
                        it = temp;
                    } else ++it;
                }
            }

            // При отпускании кнопки мыши выходим из режима выделения и передвижения
            if (event.type == sf::Event::MouseButtonReleased) {
                isSelecting = false;
                isMoving    = false;
            }
        }

        window.clear(sf::Color::Black);
        // Рисуем все шарики
        for (Ball& b : balls) {
            b.draw(window);
        }
        // Рисуем прямоугольник выделения
        if (isSelecting) {
            window.draw(selectionRect);
        }
        window.display();
    }

    return 0;
}