#ifndef GAME_HPP
#define GAME_HPP

// Bibliotecas Roguelike
#include <ButtonList.hpp>
#include <Potion.hpp>
#include <Enemy.hpp>
#include <Hero.hpp>
#include <Level.hpp>
#include <Projectile.hpp>
#include <TextureManager.hpp>

 // Bibliotecas SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Bibliotecas std
#include <cmath>
#include <iostream>
#include <vector>

class Game {
  public:
    Game(sf::RenderWindow*);

    void run();

  protected:
    void draw(float);

    void update(float);

    void loadUI();

    void updateUI(sf::View,float);

    void drawUI();

    void setMusic(GAME_STATE);

    void menuButtonsEvent(sf::Event);

    void keyboardUpdate();

    void updateProjectiles(float);

    void updateEnemy(float);

    void populateLevel();

    void resetLevel();

    double calculateDistance(sf::Vector2f, sf::Vector2f);

  private:
    // Janela principal
    sf::RenderWindow& m_window;

    // Level para o jogo
    Level m_level;

    // Heroi
    Hero m_hero;

    // Estado do jogo
    GAME_STATE m_gameState;

    // Lista de inimigos
    std::vector<std::unique_ptr<Enemy>> m_enemyList;

    // Contador de inimigos no mapa
    int m_liveEnemies;

    // Contador de inimigos mortos
    int m_enemiesDead;

    // Lista de projéteis
    std::vector<std::unique_ptr<Projectile>> m_playerProjectiles;

    // ID da textura do projétil
    int m_projectileTextureID;

    // Relógio
    sf::Clock m_gameClock;

    // View
    sf::View m_view;

    // Fonte 8-bit
    sf::Font m_uiFont;

    // Sprites do menu
    sf::Sprite m_title;
    sf::Sprite m_controls;

    // Botões do menu inicial
    ButtonList m_menuButtons;

    // Sprite de inimigos mortos
    sf::Sprite m_enemiesKilled;

    // Texto de inimigos mortos
    sf::Text m_numberEnemies;

    // Textos da tela de game over
    sf::Text m_gameOver;
    sf::Text m_pressReset;
    sf::Text m_enemiesFinal;
    sf::Text m_roomFinal;

    // Sprites UI
    // Barra preta no fundo da tela
    sf::RectangleShape m_blackBar;


    // Barra de vida e mana
    // Vida
    sf::Sprite m_healthBarOutline;
    sf::Sprite m_healthBar;

    // Mana
  /*sf::Sprite m_manaBarOutline;
    sf::Sprite m_manaBar;*/

    // Poções
    Potion m_healthPotion;
    //Potion m_manaPotion;
    Potion m_damagePotion;
    Potion m_defensePotion;
    Potion m_speedPotion;
};

#endif
