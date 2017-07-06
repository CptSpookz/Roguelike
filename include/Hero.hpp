#ifndef _HERO_HPP_
#define _HERO_HPP_

// Roguelike
#include <Char.hpp>

// std
#include <iostream>

class Hero: public Char {
  public:
    Hero();

    void initHero(HERO_CLASS);

    virtual void update(Level&, float);

    virtual void attack();

    bool canAttack();

    void takeDamage(double);
    void useMana(double);

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

    // attack speed
    double m_attackSpd;

    // time since attack
    double m_lastAttack;
};

#endif
