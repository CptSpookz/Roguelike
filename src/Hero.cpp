#include <Hero.hpp>

Hero::Hero(){
  m_charHp = 0;
  m_charBaseDmg = 0;
  m_charBuffDmg = 0;
  m_position = {0, 0};
}

void Hero::initHero(HERO_CLASS classHero){
  if(classHero == HERO_CLASS::WARRIOR){
    auto heroTextureId = TextureManager::addTexture("../resources/sprites/char/warrior/warrior_idle.png");
    m_sprite.setTexture(TextureManager::getTexture(heroTextureId));
    m_sprite.setPosition(1.3*TILE_SIZE, 1.3*TILE_SIZE);
    m_position = m_sprite.getPosition();
  }
}

void Hero::move(Level& level){
  sf::Vector2f newPosition = m_position;
  sf::Vector2f movement = {0, 0};

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    movement.y += -.5;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    movement.y += .5;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    movement.x += -.5;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    movement.x += .5;

  if(collides(sf::Vector2f(movement.x ,0), level))
    newPosition.x = m_position.x;
  else
    newPosition.x += movement.x;

  if(collides(sf::Vector2f(0, movement.y), level))
    newPosition.y = m_position.y;
  else
    newPosition.y += movement.y;

  m_position = newPosition;
  m_sprite.setPosition(m_position);
}

void Hero::attack(){}

void Hero::draw(sf::RenderWindow& window){
  window.draw(m_sprite);
}

bool Hero::collides(sf::Vector2f movement, Level& level){
  sf::Vector2f newPosition = {m_position.x + movement.x, m_position.y + movement.y};

  Tile* checkTiles[4];

  checkTiles[0] = level.getTile(sf::Vector2f(newPosition.x, newPosition.y));

  checkTiles[1] = level.getTile(sf::Vector2f(newPosition.x + 30, newPosition.y));

  checkTiles[2] = level.getTile(sf::Vector2f(newPosition.x + 30, newPosition.y + 30));

  checkTiles[3] = level.getTile(sf::Vector2f(newPosition.x, newPosition.y + 30));

  for(int i = 0; i < 4; i++){
    if(level.isSolid(checkTiles[i]->columnIndex, checkTiles[i]->rowIndex))
      return true;
  }
  return false;
}
