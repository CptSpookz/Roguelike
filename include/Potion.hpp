#ifndef _POTION_HPP_
#define _POTION_HPP_

// Roguelike
#include <Object.hpp>
#include <DataStructures.hpp>

// SFML
#include <SFML/Graphics.hpp>

class Potion : public Object {
public:
    Potion();
    virtual void usePot() = 0;
    void update(float);
};

class PotionBag : public LinkedList<Potion>{
private:
	bool potHP;
  bool potMP;
  bool potATK;
  bool potDEF;

public:
	PotionBag();

  void addPotHP(PotHP);
  void addPotMP(PotMP);
  void addPotATK(PotATK);
  void addPotDEF(PotDEF);

	bool isFull();

};

class PotHP : public Potion{
  void usePot() override;
public:
  PotHP();
};

class PotMP : public Potion{
  void usePot() override;
public:
  PotMP();
};

class PotATK : public Potion{
  void usePot() override;
public:
  PotATK();
};

class PotDEF : public Potion{
  void usePot() override;
public:
  PotDEF();
};

#endif