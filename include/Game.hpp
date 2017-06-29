#ifndef GAME_HPP
#define GAME_HPP

// Bibliotecas Roguelike
#include <TextureManager.hpp>
#include <Level.hpp>

 // Bibliotecas SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Bibliotecas std
#include <vector>

class Game {
  public:
    Game(sf::RenderWindow*);

    void run();

    void draw();

  protected:

  private:
    // Janela principal
    sf::RenderWindow& m_window;

    // Sprite teste
    sf::Sprite m_testSprite;

    // Level para o jogo
    Level m_level;

    // Estado do jogo
    GAME_STATE m_gameState;

    // Sprites UI
    // Barra de vida
    // Contorno
    // 
};

#endif
