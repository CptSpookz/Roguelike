#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_
#include <SFML/Graphics.hpp>
#include "./Util.hpp"

class Object {
private:
	int m_animationSpeed;
  bool m_isAnimated;
  int m_frameCount;
  int m_currentFrame;
	int m_frameWidth;
	int m_frameHeight;
	float m_timeDelta;

  void NextFrame();

protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;

public:

  Object();

  virtual void Draw(sf::RenderWindow &window, float timeDelta);
	virtual void Update(float timeDelta) {};

	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() const {return m_position;};

	bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);
	sf::Sprite& GetSprite() {return m_sprite;};

	int GetFrameCount() const {return m_frameCount;};

	void SetAnimated(bool isAnimated);
  bool IsAnimated() {return m_isAnimated;};

};

class Entity : public Object {
protected:
	int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];
	int m_currentTextureIndex;
	int m_health;
	int m_maxHealth;
	int m_mana;
	int m_maxMana;
	int m_attack;
	int m_defense;
	int m_strength;
	int m_dexterity;
	int m_stamina;
	int m_speed;

  sf::Vector2f m_velocity;

public:

	Entity();

	virtual void Update(float timeDelta) override;

	int GetHealth() const {return m_health;};

	int GetMaxHealth() const {return m_maxHealth;};

	int GetAttack() const {return m_attack;};

	int GetDefense() const {return m_defense;};

	int GetStrength() const {return m_strength;};

	int GetDexterity() const {return m_dexterity;};

	int GetStamina() const {return m_stamina;};

	void SetAttack(int attackValue);

  void SetDefense(int defenseValue);

  void SetStrength(int strengthValue);

	void SetDexterity(int dexterityValue);

	void SetStamina(int staminaValue);

};

#endif
