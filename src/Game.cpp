#include <Game.hpp>

Game::Game(sf::RenderWindow* window):
m_window(*window),
m_isRunning(true),
m_screenSize({0,0}){
  this->m_screenSize = {this->m_window.getSize().x/2, this->m_window.getSize().y/2};
}

void Game::init(){
  this->loadUI();
}

void Game::run(){
  while(m_isRunning){
    sf::Event event;
    if(m_window.pollEvent(event)){
      if(event.type == sf::Event::Closed){
        m_window.close();
        return;
      }
    }

    m_window.clear();

    m_window.display();
  }

  m_window.close();
}

void Game::update(double delta){

}

void Game::draw(double delta){

}

void Game::loadUI(){
  // Sprite do contorno da barra de vida
  sf::Texture& barOutlineTexture = TextureManager::getTexture(TextureManager::addTexture("../resources/sprites/ui/bar_outline.png"));
}
