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

    // base defense
    double m_charBaseDef;

    // character's base movement speed
    int m_charSpeed;

    // character's current velocity
    sf::Vector2f m_velocity;

 public:
  Char();

  double getMaxHP() const {return m_charMaxHp;};
	double getHP() const {return m_charHp;};
	void setHP(double);

	double getBaseDmg() const {return m_charBaseDmg;};
  void setBaseDmg(double);
  double getBaseDef() const {return m_charBaseDef;};
  void setBaseDef(double);
  int getBaseSpd() const {return m_charSpeed;};
  void setBaseSpd(int);

  sf::Vector2f getVel() const {return m_velocity;};

  virtual void update(float) override;
};

#endif
