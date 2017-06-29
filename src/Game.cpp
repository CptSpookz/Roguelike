#include <Game.hpp>

Game::Game(sf::RenderWindow* window):
m_window(*window){
  m_level = Level(*window);
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

  m_level.draw(m_window);

  m_window.display();
}
