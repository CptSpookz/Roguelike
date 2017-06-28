#ifndef _CHAR_HPP_
#define _CHAR_HPP_

#include <SFML/Graphics.hpp>
#include "./Item.hpp"
#include "./data_structures.hpp"

enum class HERO_CLASS{
  WARRIOR,
  MAGE,
  ARCHER,
  ASSASSIN,
  PALADIN,
  BARBARIAN,
  COUNT
};

class Char{
protected:
  double hp, baseDmg, buff;
  sf::Sprite *model;
public:
  virtual bool move() = 0;
  virtual bool attack() = 0;
};

class Hero : public Char{
protected:
  HERO_CLASS char_class;
  Item *bag;
public:
  Hero();
  virtual bool move() override;
  virtual bool attack() override;
};

Hero::Hero(){
  char_class = static_cast<HERO_CLASS>(std::rand() % static_cast<int>(HERO_CLASS::COUNT));
}

class Enemy : public Char{
protected:
  BSTree<int> brain;

public:
  virtual bool move() override;
  virtual bool attack() override;
};

#endif
