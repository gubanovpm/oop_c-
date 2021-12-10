#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "./brick.hpp"

namespace arkanoid_game {

class BrickGrid {
private:
    // Константы:
    inline static const sf::Color color {100, 200, 250};
    // Поля:
    sf::FloatRect m_border;
    int m_numBrickColumns;
    int m_numBrickRows;
    std::vector<Brick> m_bricks;
    sf::RectangleShape m_brickShape;
    int m_numActiveBricks;

public:
    BrickGrid() {}
    BrickGrid(sf::FloatRect borders, int numBrickColumns, int numBrickRows);

    sf::FloatRect getBorder() const;
    sf::Vector2i getGridSizes() const;
    sf::Vector2f getBrickSizes() const;
    bool isBrickActive(std::pair<int, int> indexes) const;
    void deactivateBrick(std::pair<int, int> indexes);
    int getNumActiveBricks() const;
    void draw(sf::RenderWindow& window);
};

}