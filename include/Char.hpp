#ifndef _CHAR_HPP_
#define _CHAR_HPP_

// Roguelike
#include <DataStructures.hpp>
#include <Object.hpp>

class Char : public Object{
protected:
    // array of texture IDs
    int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

    // current texture
    int m_currentTexID;

    // base HP
    double m_charMaxHp;

	  // current HP
	  double m_charHp;

    // base damage
    double m_charBaseDmg;

    // damage buff
    double m_charBuffDmg;

    // character's movement speed
    int m_charSpeed;

    // character's current velocity
    sf::Vector2f m_charVel;

 public:
  Char();

  double getMaxHP() const {return m_charMaxHp;};
	double getHP() const {return m_charHp;};
	void setHP(double);

	double getBaseDmg() const {return m_charBaseDmg;};
  void setBaseDmg(double);
	double getBuffDmg() const {return m_charBuffDmg;};
	void setBuffDmg(double);
	double getDmg() const {return m_charBaseDmg * m_charBuffDmg;};

  void setMovSpd(int);
  int getMovSpd() const {return m_charSpeed;};
  sf::Vector2f getVel() const {return m_charVel;};

  virtual void update(float) override;

  virtual void attack() = 0;
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
