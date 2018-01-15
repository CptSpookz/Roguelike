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
    // projectile speed ammount
    double m_speed;

    // projectile direction ammount
    sf::Vector2f m_velocity;

    // projectile's lifetime limit
    double m_lifeTime;

    // projectile's current lifetime
    double m_lifeTimePassed;
};

#endif
