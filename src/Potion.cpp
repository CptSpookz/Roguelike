#include <Potion.hpp>
#include <iostream>

Potion::Potion(POTION_TYPE type):
m_type(type),
m_isUsed(false){
  m_textureIDs[static_cast<int>(POTION_STATE::EMPTY)] = TextureManager::addTexture("../resources/sprites/ui/spr_empty_potion.png");
  sf::String potname;
  switch (m_type) {
    case POTION_TYPE::HP_POT:
      potname = "health";
    break;
    case POTION_TYPE::ATK_POT:
      potname = "damage";
    break;
    case POTION_TYPE::DEF_POT:
      potname = "defense";
    break;
    case POTION_TYPE::SPD_POT:
      potname = "speed";
    break;
  }
  m_textureIDs[static_cast<int>(POTION_STATE::FULL)] = TextureManager::addTexture("../resources/sprites/ui/spr_" + potname + "_potion.png");
  setSprite(TextureManager::getTexture(m_textureIDs[static_cast<int>(POTION_STATE::FULL)]), 1, 12);
  sf::Vector2u textureSize = TextureManager::getTexture(m_textureIDs[static_cast<int>(POTION_STATE::FULL)]).getSize();
  m_currentTexID = static_cast<int>(POTION_STATE::FULL);
  m_sprite.setOrigin(textureSize.x/2, textureSize.y/2);
}

void Potion::use(Hero& hero){
  if(!m_isUsed){
    switch (m_type) {
      case POTION_TYPE::HP_POT:
        hero.setHP(hero.getMaxHP());
      break;
      case POTION_TYPE::ATK_POT:
        hero.setBuffDmg(2 * hero.getBuffDmg());
      break;
      case POTION_TYPE::DEF_POT:
        hero.setBuffDef(2 * hero.getBuffDef());
      break;
      case POTION_TYPE::SPD_POT:
        hero.setBuffSpd(100);
      break;
    }
    m_isUsed = true;
  }
}

void Potion::refill(){
  if(m_isUsed)
    m_isUsed = false;
}

void Potion::update(float timeDelta){
  int animState;

  if (m_isUsed)
    animState = static_cast<int>(POTION_STATE::EMPTY);
  else
    animState = static_cast<int>(POTION_STATE::FULL);

  if(animState != m_currentTexID){
    m_currentTexID = animState;
    m_sprite.setTexture(TextureManager::getTexture(m_textureIDs[m_currentTexID]));
  }
}

void Potion::draw(sf::RenderWindow& window){
  window.draw(m_sprite);
}

void Potion::setPosition(double posX, double posY){
  m_sprite.setPosition(posX,posY);
}
