#ifndef _HERO_HPP_
#define _HERO_HPP_

// Roguelike
#include <Char.hpp>
#include <iostream>

class Hero: public Char {
  public:
    Hero();

    void initHero(HERO_CLASS);

    virtual void update(Level&, float);

    virtual void attack() override;

    void takeDamage(double);

    double getMaxMP() const {return m_charMaxMp;};
  	double getMP() const {return m_charMp;};
  	void setMP(double);

    sf::Vector2f getCenterPosition();

  private:
    bool collides(sf::Vector2f, Level&);

    sf::String m_className;

    // base MP
    double m_charMaxMp;

    // current MP
    double m_charMp;
};

#endif
