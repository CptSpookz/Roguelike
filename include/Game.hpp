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

    void loadUI();

    void drawUI();

  protected:

  private:
    // Janela principal
    sf::RenderWindow& m_window;

    // Level para o jogo
    Level m_level;

    // Estado do jogo
    GAME_STATE m_gameState;

    // Sprites UI
    // Barra de vida e mana
    // Vida
    sf::Sprite m_healthBarOutline;
    sf::Sprite m_healthBar;

    // Mana
    sf::Sprite m_manaBarOutline;
    sf::Sprite m_manaBar;
};

#endif
