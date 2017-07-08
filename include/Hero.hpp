#ifndef _HERO_HPP_
#define _HERO_HPP_

// Roguelike
#include <Char.hpp>

// std
#include <iostream>

class Hero: public Char {
private:
  bool collides(sf::Vector2f, Level&);

  sf::String m_className;

  // base MP
  //double m_charMaxMp;

  // current MP
  //double m_charMp;

  // attack speed
  double m_attackSpd;

  // time since attack
  double m_lastAttack;

  // time since last damage taken
  double m_lastDamage;

  // damage buff
  double m_charBuffDmg;

  // defense buff
  double m_charBuffDef;

  // character's buff movement speed
  int m_charBuffSpeed;

public:
  Hero();

  void initHero(HERO_CLASS);

  virtual void update(Level&, float);

  virtual void attack();

  bool canAttack();
  bool canDamage();

  void takeDamage(double);
  /*void useMana(double);

  double getMaxMP() const {return m_charMaxMp;};
  double getMP() const {return m_charMp;};
  void setMP(double);*/

  double getBuffDmg() const {return m_charBuffDmg;};
	void setBuffDmg(double);
	double getDmg() const {return m_charBaseDmg * m_charBuffDmg;};

	double getBuffDef() const {return m_charBuffDef;};
	void setBuffDef(double);
	double getDef() const {return m_charBaseDef * m_charBuffDef;};

  int getBuffSpd() const {return m_charBuffSpeed;};
  void setBuffSpd(int);
  int getMovSpd() const {return m_charSpeed * m_charBuffSpeed;};

  sf::Vector2f getCenterPosition();
};

#endif
