#include <Game.hpp>

Game::Game(sf::RenderWindow* window):
m_window(*window),
m_gameState(GAME_STATE::GAME_RUN){
  m_level = Level(*window);
  m_level.generate();

  m_testSprite.setTexture(TextureManager::getTexture(2));
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
      m_level.draw(m_window);
      break;
    case GAME_STATE::GAME_END:
      // código do fim de jogo
      break;
  }

  m_window.display();
}
