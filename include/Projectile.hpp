#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

// Roguelike
#include <Enemy.hpp>
#include <Level.hpp>
#include <Object.hpp>

// std
#include <vector>

class Projectile : public Object{
  public:
    Projectile();

    void update(float);

    bool collidesWall(Level&, sf::Vector2f);

    Enemy* collidesEnemy(std::vector<Enemy*>);

  private:
    // distancia maxima
    int m_distMax;

    // distancia percorrida
    int m_distPerc;
};

#endif
