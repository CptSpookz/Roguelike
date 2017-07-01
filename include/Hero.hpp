#ifndef _HERO_HPP_
#define _HERO_HPP_

// Roguelike
#include <Char.hpp>

#include <iostream>

class Hero: public Char {
  public:
    Hero();

    void initHero(HERO_CLASS);

    virtual void move(Level&, float);

    virtual void attack();

    virtual void draw(sf::RenderWindow&);

    sf::Vector2f getCenterPosition();

  private:
    bool collides(sf::Vector2f, Level&);
};

#endif
