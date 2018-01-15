#ifndef HERO_HPP
#define HERO_HPP

// Roguelike
#include <Char.hpp>

// std
#include <iostream>

class Hero: public Char {
private:
  bool collides(sf::Vector2f, Level&);

  sf::String m_className;

  /*// base MP
  double m_charMaxMp;

  // current MP
  double m_charMp;*/

  // attack speed
  double m_attackSpd;

  // time since attack
  double m_lastAttack;

  // time since last damage taken
  double m_lastDamage;

  // damage buff
  double m_charBuffDmg;
  // max damage buff duration
  float m_atkBuffLimit;
  // current damage buff time
  sf::Time m_atkBuffCurrent;

  // defense buff
  double m_charBuffDef;
  // max defense buff duration
  float m_defBuffLimit;
  // current defense buff time
  sf::Time m_defBuffCurrent;

  // movement speed buff
  int m_charBuffSpeed;
  // max speed buff duration
  float m_spdBuffLimit;
  // current speed buff time
  sf::Time m_spdBuffCurrent;

public:
  Hero();

  void initHero(HERO_CLASS);

  virtual void update(Level&, float);

  virtual void attack();

  bool canAttack();
  bool canDamage();

  void takeDamage(double);

  void reset();

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
  int getMovSpd() const {return m_charSpeed + m_charBuffSpeed;};

  sf::Vector2f getCenterPosition();
};

#endif
