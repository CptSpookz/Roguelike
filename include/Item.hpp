#ifndef _ITEM_HPP_
#define _ITEM_HPP_
#include "Object.hpp"
#ifndef ITEM_HPP
#define ITEM_HPP

// SFML
#include <SFML/Graphics.hpp>

class Item {
  public:
    virtual void itemAction() = 0;

  protected:
    // item base Sprite
    sf::Sprite m_sprite;

    // item charges left
    int m_charges;
};

#endif
