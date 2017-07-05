#ifndef ENEMY_HPP
#define ENEMY_HPP

// Roguelike
#include <Char.hpp>
#include <Enemy.hpp>

// std
#include <climits>
#include <cstdlib>
#include <string>
#include <iostream>

class Enemy: public Char{
  public:
    Enemy(double);

    void update(float) override;

    void draw(sf::RenderWindow&);

    void calculateSteps(Level&, sf::Vector2f);
  private:
    // as posições para o inimigo
    std::vector<sf::Vector2f> m_targetPositions;

    // a posição objetivo atual
    sf::Vector2f m_currentTarget;

    // velocidade de movimento
    sf::Vector2f m_velocity;

    // tile que o personagem estava no update anterior
    Tile* m_playerPrevious;

    // velocidade do inimigo
    double m_speed;
};

#endif
