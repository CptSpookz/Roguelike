#include <Hero.hpp>

Hero::Hero(){
  m_charMaxHp = 500;
  m_charHp = m_charMaxHp;
//  m_charMaxMp = 150;
//  m_charMp = m_charMaxMp;
  m_charBaseDmg = 25;
  m_charBuffDmg = 1;
  m_charBaseDef = 10;
  m_charBuffDef = 1;
  m_charSpeed = 200;
  m_charBuffSpeed = 1;
  m_position = {0.f,0.f};
  m_lastAttack = 0;
}

void Hero::initHero(HERO_CLASS classHero){
  if(classHero == HERO_CLASS::WARRIOR){
    m_className = "warrior";
    m_charBaseDmg *= 2;
    m_charMaxHp += 250;
    m_charHp = m_charMaxHp;
    m_attackSpd = 1.25;
  }
  else if (classHero == HERO_CLASS::MAGE){
    m_className = "mage";
    m_charBaseDmg *= 2.5;
    m_charBaseDef *= 1.5;
    m_attackSpd = .75;
  }
  else if (classHero == HERO_CLASS::ARCHER){
    m_className = "archer";
    m_charBaseDmg *= 3;
    m_charSpeed = 300;
    m_attackSpd = .5;
  }
  else if (classHero == HERO_CLASS::THIEF){
    m_className = "thief";
    m_charBaseDmg *= 2.5;
    m_charSpeed = 350;
    m_attackSpd = .75;
  }
  else if (classHero == HERO_CLASS::PALADIN){
    m_className = "paladin";
    m_charMaxHp += 500;
    m_charHp = m_charMaxHp;
    m_charBaseDef *= 3;
    m_attackSpd = 1.25;
  }
  else if (classHero == HERO_CLASS::VALKYRIE){
    m_className = "valkyrie";
    m_charMaxHp += 250;
    m_charHp = m_charMaxHp;
    m_charBaseDef *= 2;
    m_charSpeed = 250;
    m_attackSpd = 1;
  }

  m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::addTexture("../resources/sprites/players/" + m_className + "/spr_" + m_className + "_walk_up.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::addTexture("../resources/sprites/players/" + m_className + "/spr_" + m_className + "_walk_down.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::addTexture("../resources/sprites/players/" + m_className + "/spr_" + m_className + "_walk_left.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::addTexture("../resources/sprites/players/" + m_className + "/spr_" + m_className + "_walk_right.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::addTexture("../resources/sprites/players/" + m_className + "/spr_" + m_className + "_idle_up.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::addTexture("../resources/sprites/players/" + m_className + "/spr_" + m_className + "_idle_down.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::addTexture("../resources/sprites/players/" + m_className + "/spr_" + m_className + "_idle_left.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::addTexture("../resources/sprites/players/" + m_className + "/spr_" + m_className + "_idle_right.png");

  setSprite(TextureManager::getTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), 8, 12);
  m_currentTexID = static_cast<int>(ANIMATION_STATE::WALK_UP);

  m_sprite.setOrigin(sf::Vector2f(13.f, 18.f));

  m_position = m_sprite.getPosition();
}

void Hero::update(Level& level, float delta){
  sf::Vector2f newPosition = m_position;
  sf::Vector2f movement({0.f, 0.f});

  // next sprite after movement
  int animState = m_currentTexID;

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
    movement.y += -m_charSpeed * delta;
    animState = static_cast<int>(ANIMATION_STATE::WALK_UP);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
    movement.y += m_charSpeed * delta;
    animState = static_cast<int>(ANIMATION_STATE::WALK_DOWN);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
    movement.x += -m_charSpeed * delta;
    animState = static_cast<int>(ANIMATION_STATE::WALK_LEFT);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
    movement.x += m_charSpeed * delta;
    animState = static_cast<int>(ANIMATION_STATE::WALK_RIGHT);
  }

  if(collides(sf::Vector2f(movement.x ,0), level)){
    newPosition.x = m_position.x;
  }else{
    newPosition.x += movement.x;
  }

  if(collides(sf::Vector2f(0, movement.y), level)){
    newPosition.y = m_position.y;
  }else{
    newPosition.y += movement.y;
  }

  m_position = newPosition;
  m_sprite.setPosition(m_position);

  if (m_currentTexID != animState){
      m_currentTexID = animState;
      m_sprite.setTexture(TextureManager::getTexture(m_textureIDs[m_currentTexID]));
  }

  if (movement.x == 0 && movement.y == 0){
    if (isMoving()){
      switch (m_currentTexID) {
        case static_cast<int>(ANIMATION_STATE::WALK_UP):
          m_currentTexID = static_cast<int>(ANIMATION_STATE::IDLE_UP);
          break;
        case static_cast<int>(ANIMATION_STATE::WALK_DOWN):
          m_currentTexID = static_cast<int>(ANIMATION_STATE::IDLE_DOWN);;
          break;
        case static_cast<int>(ANIMATION_STATE::WALK_LEFT):
          m_currentTexID = static_cast<int>(ANIMATION_STATE::IDLE_LEFT);
          break;
        case static_cast<int>(ANIMATION_STATE::WALK_RIGHT):
          m_currentTexID = static_cast<int>(ANIMATION_STATE::IDLE_RIGHT);;
          break;
      }
      m_sprite.setTexture(TextureManager::getTexture(m_textureIDs[m_currentTexID]));
      setMovement(false);
    }
  }
  else {
    if (!isMoving()){
      switch (m_currentTexID) {
        case static_cast<int>(ANIMATION_STATE::IDLE_UP):
          m_currentTexID = static_cast<int>(ANIMATION_STATE::WALK_UP);
          break;
        case static_cast<int>(ANIMATION_STATE::IDLE_DOWN):
          m_currentTexID = static_cast<int>(ANIMATION_STATE::WALK_DOWN);
          break;
        case static_cast<int>(ANIMATION_STATE::IDLE_LEFT):
          m_currentTexID = static_cast<int>(ANIMATION_STATE::WALK_LEFT);
          break;
        case static_cast<int>(ANIMATION_STATE::IDLE_RIGHT):
          m_currentTexID = static_cast<int>(ANIMATION_STATE::WALK_RIGHT);
          break;
      }
      m_sprite.setTexture(TextureManager::getTexture(m_textureIDs[m_currentTexID]));
      setMovement(true);
    }
  }

  if(m_attackSpd > m_lastAttack){
    m_lastAttack += delta;
  }

  if(INV_TIME > m_lastDamage){
    m_lastDamage += delta;
  }
}

void Hero::attack(){
  m_lastAttack = 0;
}

bool Hero::canAttack(){
  return (m_attackSpd <= m_lastAttack);
}

bool Hero::canDamage(){
  return (INV_TIME <= m_lastDamage);
}

void Hero::takeDamage(double damage){
  auto afterHealth = m_charHp - damage;
  m_charHp = std::max(afterHealth, 0.0);
  m_lastDamage = 0;
}

/*void Hero::useMana(double cost){
  auto currentMana = m_charMp - cost;
  m_charMp = std::max(currentMana, 0.0);
}

void Hero::setMP(double mp){
  if (mp >= 0){
    m_charMp = mp;
  }
}*/

void Hero::setBuffDmg(double dmgBuff){
  if(dmgBuff >= 1){
    m_charBuffDmg = dmgBuff;
  }
}

void Hero::setBuffDef(double defBuff){
	if (defBuff >= 1){
		m_charBuffDef = defBuff;
  }
}

void Hero::setBuffSpd(int spdBuff){
	if (spdBuff >= 1){
		m_charBuffSpeed = spdBuff;
  }
}

bool Hero::collides(sf::Vector2f movement, Level& level){
  sf::Vector2f newPosition = {m_position.x + movement.x, m_position.y + movement.y};

  Tile* checkTiles[4];

  checkTiles[0] = level.getTile(sf::Vector2f(newPosition.x - 5, newPosition.y));

  checkTiles[1] = level.getTile(sf::Vector2f(newPosition.x + 15, newPosition.y));

  checkTiles[2] = level.getTile(sf::Vector2f(newPosition.x + 15, newPosition.y + 15));

  checkTiles[3] = level.getTile(sf::Vector2f(newPosition.x - 5, newPosition.y + 15));

  for(int i = 0; i < 4; i++){
    if(level.isSolid(checkTiles[i]->columnIndex, checkTiles[i]->rowIndex)){
      return true;
    }
  }
  return false;
}

sf::Vector2f Hero::getCenterPosition(){
  sf::Vector2f centerPosition = {m_position.x, m_position.y};
  return centerPosition;
}
