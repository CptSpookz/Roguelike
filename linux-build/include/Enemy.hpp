#ifndef ENEMY_HPP
#define ENEMY_HPP

// Roguelike
#include <Char.hpp>
#include <Level.hpp>

// std
#include <climits>
#include <cstdlib>
#include <string>
#include <iostream>

class Enemy: public Char{
  public:
    Enemy();

    virtual void update(float) override;

    void calculateSteps(Level&, sf::Vector2f);

    void takeDamage(double);

    bool isAlive();
  private:
    // as posições para o inimigo
    std::vector<sf::Vector2f> m_targetPositions;

    // a posição objetivo atual
    sf::Vector2f m_currentTarget;

    // tile que o personagem estava no update anterior
    Tile* m_playerPrevious;

    // velocidade do inimigo
    double m_speed;
};

#endif
