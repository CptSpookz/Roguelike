#ifndef _ITEM_HPP_
#define _ITEM_HPP_
#include <SFML/Graphics.hpp>

class Item{
protected:
  int charges;
  sf::Sprite *model;
public:
  virtual void item_action() = 0;
};

#endif
