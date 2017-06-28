#ifndef GAME_HPP
#define GAME_HPP

#include <TextureManager.hpp>
#include <SFML/Graphics.hpp>

class Game {
  public:
    Game(sf::RenderWindow*);

    void init();

    void run();

    void update(double);

    void draw(double);

  protected:
    void loadUI();

  private:
    // Janela principal do jogo
    sf::RenderWindow& m_window;

    // Checa se o jogo está rodando
    bool m_isRunning;

    // Vetor com o tamanho da tela
    sf::Vector2u m_screenSize;

    // Sprites da UI
    // Ponteiro do sprite do contorno da barra de vida
    sf::Sprite* m_healthBarOutlineSprite;
};

#endif
