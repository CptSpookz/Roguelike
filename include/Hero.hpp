#ifndef HERO_HPP
#define HERO_HPP

// Roguelike
#include <Char.hpp>

#include <iostream>

class Hero: public Char {
  public:
    Hero();

    void initHero(HERO_CLASS);

    virtual void move(Level&);

    virtual void attack();

    virtual void draw(sf::RenderWindow&);

  private:
    bool collides(sf::Vector2f, Level&);
};

#endif
