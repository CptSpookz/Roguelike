#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

// Roguelike
#include <Object.hpp>

class Projectile: public Object{
  public:
    Projectile(sf::Texture&, double, double, sf::Vector2f, sf::Vector2f);

    void update(float);

    void draw(sf::RenderWindow&);

    bool isAlive();
  private:
    // velocidade do projétil
    double m_speed;

    // direção do projétil
    sf::Vector2f m_velocity;

    // tempo de vida
    double m_lifeTime;

    // tempo passado
    double m_lifeTimePassed;
};

#endif
