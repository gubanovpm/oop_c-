#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "../include/brick_grid.hpp"

arkanoid_game::BrickGrid::BrickGrid(sf::FloatRect borders, int numBrickColumns, int numBrickRows) : 
    m_border(borders), 
    m_numBrickColumns(numBrickColumns), 
    m_numBrickRows(numBrickRows),
    m_numActiveBricks(numBrickColumns * numBrickRows) {
        m_bricks.resize(m_numBrickColumns * m_numBrickRows, Brick{true});
        m_brickShape.setSize(getBrickSizes());
        m_brickShape.setOutlineColor(sf::Color::Black);
        m_brickShape.setOutlineThickness(0.5);
        m_brickShape.setFillColor(color);
    }

sf::FloatRect arkanoid_game::BrickGrid::getBorder() const {
    return m_border;
}

sf::Vector2i arkanoid_game::BrickGrid::getGridSizes() const {
    return {m_numBrickColumns, m_numBrickRows};
}

sf::Vector2f arkanoid_game::BrickGrid::getBrickSizes() const {
    return {m_border.width / m_numBrickColumns, m_border.height / m_numBrickRows};
}

bool arkanoid_game::BrickGrid::isBrickActive(std::pair<int, int> indexes) const {
    return m_bricks[indexes.first + indexes.second * m_numBrickColumns].isActive;
}

void arkanoid_game::BrickGrid::deactivateBrick(std::pair<int, int> indexes) {
    m_bricks[indexes.first + indexes.second * m_numBrickColumns].isActive = false;
    m_numActiveBricks--;
}

int arkanoid_game::BrickGrid::getNumActiveBricks() const {
    return m_numActiveBricks;
}

void arkanoid_game::BrickGrid::draw(sf::RenderWindow& window) {
    auto [brickWidth, brickHeight] = getBrickSizes();
    
    for (int j = 0; j < m_numBrickRows; ++j) {
        for (int i = 0; i < m_numBrickColumns; ++i) {
            if (!isBrickActive({i, j}))
                continue;
            m_brickShape.setPosition({m_border.left + i * brickWidth, m_border.top + j * brickHeight});
            window.draw(m_brickShape);
        }
    }
}