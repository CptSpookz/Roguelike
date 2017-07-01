#ifndef _CHAR_HPP_
#define _CHAR_HPP_

// Roguelike
#include <DataStructures.hpp>
#include <Item.hpp>
#include <Level.hpp>
#include <TextureManager.hpp>
#include <Util.hpp>

// SFML
#include <SFML/Graphics.hpp>


class Char {
protected:
    // char sprite
    sf::Sprite m_sprite;

    // sprite position
    sf::Vector2f m_position;

    // base HP
    double m_charMaxHp;

	  // current HP
	  double m_charHp;

    // base damage
    double m_charBaseDmg;

    // damage buff
    double m_charBuffDmg;


 public:
  double getMaxHP(){return m_charMaxHp;};

	double getHP(){return m_charHp;};
	void setHP(double);

	double getBaseDmg(){return m_charBaseDmg;};

	double getBuffDmg(){return m_charBuffDmg;};
	void setBuffDmg(double);

	double getDmg(){return m_charBaseDmg * m_charBuffDmg;};

	virtual void move(Level&, float) = 0;

    virtual void attack() = 0;

    virtual void draw(sf::RenderWindow&) = 0;
};

/*class Enemy : public Char{
  public:
    virtual void move() override;
    virtual void attack() override;

  protected:
    // base IA tree
    BSTree<int> m_brain;
};*/

#endif
