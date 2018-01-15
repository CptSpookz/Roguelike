#ifndef GAME_HPP
#define GAME_HPP

// Roguelike Libs
#include <ButtonList.hpp>
#include <Potion.hpp>
#include <Enemy.hpp>
#include <Hero.hpp>
#include <Level.hpp>
#include <Projectile.hpp>
#include <TextureManager.hpp>

 // SFML Libs
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Standard C++ Libs
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
    // Main Window
    sf::RenderWindow& m_window;

    // Main Game level
    Level m_level;

    // Main Character
    Hero m_hero;

    // Game State
    GAME_STATE m_gameState;

    // Enemies list
    std::vector<std::unique_ptr<Enemy>> m_enemyList;

    // Currently alive enemies counter
    int m_liveEnemies;

    // Currently dead enemies counter
    int m_enemiesDead;

    // Projectiles list
    std::vector<std::unique_ptr<Projectile>> m_playerProjectiles;

    // Projectile Texture's ID
    int m_projectileTextureID;

    // Game Clock
    sf::Clock m_gameClock;

    // View
    sf::View m_view;

    // UI 8-bit font
    sf::Font m_uiFont;

    // Main menu sprites
    sf::Sprite m_title;
    sf::Sprite m_controls;

    // Main menu buttons
    ButtonList m_menuButtons;

    // Dead enemies sprites
    sf::Sprite m_enemiesKilled;

    // Dead enemies text
    sf::Text m_numberEnemies;

    // Textos da tela de game over
    sf::Text m_gameOver;
    sf::Text m_pressReset;
    sf::Text m_enemiesFinal;
    sf::Text m_roomFinal;

    // UI Sprites
    // Lower Screen black bar
    sf::RectangleShape m_blackBar;


    // Health and Mana Bars
    // Health
    sf::Sprite m_healthBarOutline;
    sf::Sprite m_healthBar;

    // Mana
  /*sf::Sprite m_manaBarOutline;
    sf::Sprite m_manaBar;*/

    // Potions
    Potion m_healthPotion;
    //Potion m_manaPotion;
    Potion m_damagePotion;
    Potion m_defensePotion;
    Potion m_speedPotion;
};

#endif
