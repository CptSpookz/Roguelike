#include <Projectile.hpp>

Projectile::Projectile(int x, int y, sf::Texture& texture){
  m_velocity.x = x;
  m_velocity.y = y;
}

void Projectile::update(float delta){
  sf::Vector2f newPos = {m_position.x + m_velocity.x*delta, m_position.y + m_velocity.y*delta};
  //m_position = sf::Vector2f();
}

bool Projectile::collidesWall(Level& level, sf::Vector2f movement){
  sf::Vector2f newPosition = {m_position.x + movement.x, m_position.y + movement.y};

  Tile* checkTiles[4];

  checkTiles[0] = level.getTile(sf::Vector2f(newPosition.x - (m_size.x/2), newPosition.y - (m_size.y/2)));

  checkTiles[1] = level.getTile(sf::Vector2f(newPosition.x + (m_size.x/2), newPosition.y - (m_size.y/2)));

  checkTiles[2] = level.getTile(sf::Vector2f(newPosition.x + (m_size.x/2), newPosition.y + (m_size.y/2)));

  checkTiles[3] = level.getTile(sf::Vector2f(newPosition.x - (m_size.x/2), newPosition.y + (m_size.y/2)));

  for(int i = 0; i < 4; i++){
    if(level.isSolid(checkTiles[i]->columnIndex, checkTiles[i]->rowIndex))
      return true;
  }
  return false;
}

bool Projectile::collidesEnemy(std::vector<Enemy*> enemyList){

}
