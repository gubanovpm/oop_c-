#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace arkanoid_game {
class Arkanoid;
}

#include "./paddle.hpp"
#include "./arkanoid.hpp"

namespace arkanoid_game {

class Bonus {
protected:
    inline static const float speed       = 120;
    inline static const float radius      = 15 ;
    inline static const int   time        = 10 ;
    inline static const int   bonus_count = 7  ;

    sf::Vector2f m_position;
    float m_time;

public:
    Paddle line_ = {{0., 0.}, {0., 0.}};
    Bonus(sf::Vector2f position);
    virtual ~Bonus() {}
    void update(float dt);                                  // Двигаем бонус
    virtual void draw(sf::RenderWindow &window) const = 0 ; // Рисуем бонус
    virtual void activate(Arkanoid &game) = 0;              // Активация бонуса
    virtual bool deactivate(Arkanoid &game) { return true; };

    bool isColiding(const Paddle &paddle) const;

    friend class Arkanoid;                                  // Класс Arkanoid должен быть дружественным, так как он может менять внутреннее объекта-бонуса
};

class Triple final: public Bonus {
public:
    Triple(sf::Vector2f position) : Bonus(position) {}
    void draw(sf::RenderWindow &window) const override;
    void activate(Arkanoid &game) override;

    friend class Arkanoid;                                  // Класс Arkanoid должен быть дружественным, так как он может менять внутреннее объекта-бонуса
};

class BigRocket final: public Bonus {
public:
    BigRocket(sf::Vector2f position) : Bonus(position) {}
    void draw(sf::RenderWindow &window) const override;
    void activate(Arkanoid &game) override;

    friend class Arkanoid;                                  // Класс Arkanoid должен быть дружественным, так как он может менять внутреннее объекта-бонуса
};

class LitRocket final: public Bonus {
public:
    LitRocket(sf::Vector2f position) : Bonus(position) {}
    void draw(sf::RenderWindow &window) const override;
    void activate(Arkanoid &game) override;
    
    friend class Arkanoid;                                  // Класс Arkanoid должен быть дружественным, так как он может менять внутреннее объекта-бонуса
};

class SlowBall final: public Bonus {
public:
    SlowBall(sf::Vector2f position) : Bonus(position) {}
    void draw(sf::RenderWindow &window) const override;
    void activate(Arkanoid &game) override;
    bool deactivate(Arkanoid &game) override;
    
    friend class Arkanoid;                                  // Класс Arkanoid должен быть дружественным, так как он может менять внутреннее объекта-бонуса
};

class UnderLine final: public Bonus {
public:
    UnderLine(sf::Vector2f position) : Bonus(position) {}
    void draw(sf::RenderWindow &window) const override;
    void activate(Arkanoid &game) override;
    bool deactivate(Arkanoid &game) override;

    friend class Arkanoid;
};

class SpeedUp final: public Bonus {
public:
    SpeedUp(sf::Vector2f position) : Bonus(position) {}
    void draw(sf::RenderWindow &window) const override;
    void activate(Arkanoid &game) override;
    bool deactivate(Arkanoid &game) override;

    friend class Arkanoid;
};

class BurnIt final: public Bonus {
public:
    BurnIt(sf::Vector2f position) : Bonus(position) {}
    void draw(sf::RenderWindow &window) const override;
    void activate(Arkanoid &game) override;
    bool deactivate(Arkanoid &game) override;

    friend class Arkanoid;
};

class StickyFingers final : public Bonus {
public:
    StickyFingers(sf::Vector2f position) : Bonus(position) {}
    void draw(sf::RenderWindow &window) const override;
    void activate(Arkanoid &game) override;
    bool deactivate(Arkanoid &game) override;

    friend class Arkanoid;
};

}