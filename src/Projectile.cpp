#include <Projectile.hpp>

Projectile::Projectile(sf::Texture& texture, double speed, double lifeTime, sf::Vector2f direction, sf::Vector2f initialPos):
m_speed(speed),
m_lifeTime(lifeTime),
m_lifeTimePassed(0),
m_velocity(direction){
  m_position = initialPos;

  m_sprite.setTexture(texture);
  m_sprite.setOrigin(0, texture.getSize().y);
  m_sprite.setPosition(m_position);

  if(direction.x == 1)
    m_sprite.setRotation(0);
  else if(direction.x == -1)
    m_sprite.setRotation(180);
  else if(direction.y == 1)
    m_sprite.setRotation(90);
  else if(direction.y == -1)
    m_sprite.setRotation(270);
}

void Projectile::update(float delta){
  m_position.x += m_velocity.x * (m_speed * delta);
  m_position.y += m_velocity.y * (m_speed * delta);

  m_sprite.setPosition(m_position);

  m_lifeTimePassed += delta;
}

void Projectile::draw(sf::RenderWindow& window){
  window.draw(m_sprite);
}

bool Projectile::isAlive(){
  return (m_lifeTime > m_lifeTimePassed);
}
