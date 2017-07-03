#include <ButtonList.hpp>

ButtonList::ButtonList():
m_actualIndex(0){}

void ButtonList::setOutline(sf::Texture& texture){
  sf::Vector2u textureSize = texture.getSize();
  m_outlineSprite.setTexture(texture);
  m_outlineSprite.setOrigin(textureSize.x/2, textureSize.y/2);
}

void ButtonList::addButton(sf::RenderWindow& window, sf::Texture& texture){
  sf::Vector2u textureSize = texture.getSize();
  auto newSprite = new sf::Sprite();
  newSprite->setTexture(texture);
  newSprite->setOrigin(textureSize.x/2, textureSize.y/2);
  m_buttonSprites.insertItem(newSprite);
  centerHorizontal(window);
}

void ButtonList::setTextureIndex(int index, sf::Texture& texture){
  sf::Vector2u textureSize = texture.getSize();
  m_buttonSprites[index]->setTexture(texture);
  m_buttonSprites[index]->setOrigin(textureSize.x/2, textureSize.y/2);
}

void ButtonList::draw(sf::RenderWindow& window){
  for(int i = 0; i < m_buttonSprites.getSize(); i++){
    window.draw(*m_buttonSprites[i]);
  }
  window.draw(m_outlineSprite);
}

void ButtonList::toNext(){
  m_actualIndex++;
  if(m_actualIndex >= m_buttonSprites.getSize())
    m_actualIndex = 0;
  m_outlineSprite.setPosition(m_buttonSprites[m_actualIndex]->getPosition());
}

void ButtonList::toPrevious(){
  m_actualIndex--;
  if(m_actualIndex < 0)
    m_actualIndex = m_buttonSprites.getSize()-1;
  m_outlineSprite.setPosition(m_buttonSprites[m_actualIndex]->getPosition());
}

int ButtonList::getIndex(){
  return m_actualIndex;
}

void ButtonList::centerHorizontal(sf::RenderWindow& window){
  // variáveis principais para a centralização dos botões
  auto numberOfButtons = m_buttonSprites.getSize();
  sf::Vector2u textureSize = m_buttonSprites[0]->getTexture()->getSize();
  sf::Vector2u windowSize = window.getSize();
  auto vertPos = windowSize.y/2;
  auto margin = (windowSize.x-(numberOfButtons*textureSize.x))/(numberOfButtons+1);

  // centralização do primeiro botão
  m_buttonSprites[0]->setPosition(margin+textureSize.x/2, vertPos);

  // aplicação na borda
  m_outlineSprite.setPosition(m_buttonSprites[0]->getPosition());

  for(int i = 1; i < m_buttonSprites.getSize(); i++){
    sf::Vector2f prevPos = m_buttonSprites[i-1]->getPosition();
    m_buttonSprites[i]->setPosition(margin+prevPos.x+textureSize.x, vertPos);
  }
}
