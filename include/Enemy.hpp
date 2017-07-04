#ifndef ENEMY_HPP
#define ENEMY_HPP

// Roguelike
#include <Char.hpp>

class Enemy: public Char{
  public:
    Enemy();

    virtual void update(Level&, float);

    virtual void attack() override;

    void takeDamage(double);

  private:

};

#endif
