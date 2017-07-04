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
    Projectile(int, int);

    void update(float);

    bool collidesWall(Level&, sf::Vector2f, sf::Texture&);

    bool collidesEnemy(std::vector<Enemy*>);

  private:
    // distancia maxima
    int m_distMax;

    // distancia percorrida
    int m_distPerc;

    // dano do projétil
    double m_damage;

    // velocidade do projétil
    sf::Vector2f m_velocity;

    // tamanho do projétil
    sf::Vector2i m_size;
};

#endif
