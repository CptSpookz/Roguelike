#ifndef _CHAR_HPP_
#define _CHAR_HPP_

#include <SFML/Graphics.hpp>
#include "./Item.hpp"
#include "./data_structures.hpp"

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
  Item *bag;
public:
  virtual bool move() override;
  virtual bool attack() override;
};


struct Action{};

class Enemy : public Char{
protected:
  BSTree<Action> brain;
  
public:
  virtual bool move() override;
  virtual bool attack() override;
};

#endif
