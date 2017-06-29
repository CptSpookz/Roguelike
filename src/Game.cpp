#include <Game.hpp>

Game::Game(sf::RenderWindow* window):
m_window(*window),
m_gameState(GAME_STATE::GAME_RUN),
m_level(Level(*window)){
  loadUI();

  m_level.generate();
}

void Game::run(){
  while(m_window.isOpen()){
    sf::Event event;
    while(m_window.pollEvent(event)){
      if(event.type == sf::Event::Closed)
        m_window.close();
    }

    draw();
  }
}

void Game::draw(){
  m_window.clear(sf::Color::Black);

  switch(m_gameState){
    case GAME_STATE::MAIN_MENU:
      // código do menu
      break;
    case GAME_STATE::GAME_RUN:
      // renderiza o mapa
      m_level.draw(m_window);

      // renderiza a ui
      drawUI();

      break;
    case GAME_STATE::GAME_END:
      // código do fim de jogo
      break;
  }

  m_window.display();
}

void Game::loadUI(){
  // carrega as texturas das barras e altera os sprites
  // texturas
  auto barOutlineId = TextureManager::addTexture("../resources/sprites/ui/outline_bar.png");
  auto healthBarId = TextureManager::addTexture("../resources/sprites/ui/health_bar.png");
  auto manaBarId = TextureManager::addTexture("../resources/sprites/ui/mana_bar.png");

  // sprites
  // barra de vida
  m_healthBarOutline.setTexture(TextureManager::getTexture(barOutlineId));
  m_healthBarOutline.setPosition(10, 10);
  m_healthBar.setTexture(TextureManager::getTexture(healthBarId));
  m_healthBar.setPosition(10, 10);
  // barra de mana
  m_manaBarOutline.setTexture(TextureManager::getTexture(barOutlineId));
  m_manaBarOutline.setPosition(10, 36);
  m_manaBar.setTexture(TextureManager::getTexture(manaBarId));
  m_manaBar.setPosition(10, 36);
}

void Game::drawUI(){
  // barras
  // vida
  m_window.draw(m_healthBarOutline);
  m_window.draw(m_healthBar);
  // mana
  m_window.draw(m_manaBarOutline);
  m_window.draw(m_manaBar);
}
