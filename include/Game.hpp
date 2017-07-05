#ifndef GAME_HPP
#define GAME_HPP

// Bibliotecas Roguelike
#include <ButtonList.hpp>
#include <Enemy.hpp>
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
    void menuButtonsEvent(sf::Event);

  private:
    // Janela principal
    sf::RenderWindow& m_window;

    // Level para o jogo
    Level m_level;

    // Heroi
    Hero m_hero;

    // Estado do jogo
    GAME_STATE m_gameState;

    // Lista de inimigos TODO: fazer os inimigos
    std::vector<Enemy*> m_enemyList;

    // Relógio
    sf::Clock m_gameClock;

    // View
    sf::View m_view;

    // Fonte 8-bit
    sf::Font m_uiFont;

    // Botões do menu inicial
    ButtonList m_menuButtons;

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

    // Poções
    sf::Sprite m_healthPotion;
    sf::Sprite m_manaPotion;
    sf::Sprite m_defensePotion;
    sf::Sprite m_speedPotion;
};

#endif
