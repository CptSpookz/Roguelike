#ifndef BUTTON_HPP
#define BUTTON_HPP

// SFML
#include <SFML/Graphics.hpp>

#include <iostream>

class Button{
  public:
    Button();

    bool isPressed(sf::Vector2i);

    void setTexture(sf::Texture&);

    void centerHorizontal(int, int);

    void draw(sf::RenderWindow&);
  private:
    // sprite do botão
    sf::Sprite m_sprite;

    // posição do botão
    sf::Vector2f m_position;

    // origem do botão
    sf::Vector2f m_origin;

    // tamanho do botão
    sf::Vector2u m_size;
};

#endif
