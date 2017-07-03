#include <Button.hpp>

Button::Button(){}

bool Button::isPressed(sf::Vector2i mousePos){
  auto minX = m_position.x-m_size.x/2;
  auto maxX = m_position.x+m_size.x/2;
  auto minY = m_position.y-m_size.y/2;
  auto maxY = m_position.y+m_size.y/2;

  return ((mousePos.x >= minX && mousePos.x <= maxX) && (mousePos.y >= minY && mousePos.y <= maxY));
}

void Button::setTexture(sf::Texture& texture){
  m_sprite.setTexture(texture);
  m_position = m_sprite.getPosition();
  m_size = m_sprite.getTexture()->getSize();
  m_origin = sf::Vector2f(m_size.x/2, m_size.y/2);
  m_sprite.setOrigin(m_size.x/2, m_size.y/2);
}

void Button::centerHorizontal(int windowWidth, int vertPos){
  m_sprite.setPosition(windowWidth/2, vertPos);
  m_position = m_sprite.getPosition();
}

void Button::draw(sf::RenderWindow& window){
  window.draw(m_sprite);
}
