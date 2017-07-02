#ifndef GAME_HPP
#define GAME_HPP

// Bibliotecas Roguelike
#include <Hero.hpp>
#include <Level.hpp>
#include <TextureManager.hpp>

 // Bibliotecas SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Bibliotecas std
#include <iostream>
#include <vector>

class Game {
  public:
    Game(sf::RenderWindow*);

    void run();

    void draw(float);

    void update(float);

    void loadUI();

    void updateUI(sf::View);

    void drawUI();

  protected:

  private:
    // Janela principal
    sf::RenderWindow& m_window;

    // Level para o jogo
    Level m_level;

    // Heroi
    Hero m_hero;

    // Estado do jogo
    GAME_STATE m_gameState;

    // Relógio
    sf::Clock m_gameClock;

    // View
    sf::View m_view;

    // Fonte 8-bit
    sf::Font m_uiFont;

    // Sprites UI
    // Barra preta no fundo da tela
    sf::RectangleShape m_blackBar;

    // Barra de vida e mana
    // Vida
    sf::Sprite m_healthBarOutline;
    sf::Sprite m_healthBar;

    // Mana
    sf::Sprite m_manaBarOutline;
    sf::Sprite m_manaBar;

    // Status do herói
    sf::Sprite m_attackStat;
    sf::Sprite m_defenseStat;
    sf::Sprite m_speedStat;
    sf::Sprite m_luckStat;

    // Texto UI
    // Status do herói
    sf::Text m_attackValue;
    sf::Text m_defenseValue;
    sf::Text m_speedValue;
    sf::Text m_luckValue;

};

#endif
