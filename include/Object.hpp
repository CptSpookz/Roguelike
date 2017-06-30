#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_
#include <SFML/Graphics.hpp>
#include "./Util.hpp"

class Object {
private:
	int animationSpeed;
  bool isAnimated;
  int frameCount;
  int currentFrame;
	int frameWidth;
	int frameHeight;
	float timeDelta;

  void NextFrame();

protected:
	sf::Sprite sprite;
	sf::Vector2f position;

public:

  Object();

  virtual void Draw(sf::RenderWindow &window, float timeDelta);
	virtual void Update(float timeDelta) {};

	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() const {return this->position;};

	bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);
	sf::Sprite& GetSprite() {return this->sprite;};

	int GetFrameCount() const {return this->frameCount;};

	void SetAnimated(bool isAnimated);
  bool IsAnimated() {return this->isAnimated;};

};

class Entity : public Object {
protected:
	int textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

	int currentTextureIndex;

	int health;

	int maxHealth;

	int mana;

	int maxMana;

	int attack;

	int defense;

	int strength;

	int dexterity;

	int stamina;

	int speed;

  sf::Vector2f velocity;

public:

	Entity();

	virtual void Update(float timeDelta) override;

	int GetHealth() const {return this->health;};

	int GetMaxHealth() const {return this->maxHealth;};

	int GetAttack() const {return this->attack;};

	int GetDefense() const {return this->defense;};

	int GetStrength() const {return this->strength;};

	int GetDexterity() const {return this->dexterity;};

	int GetStamina() const {return this->stamina;};

	void SetAttack(int attackValue);

  void SetDefense(int defenseValue);

  void SetStrength(int strengthValue);

	void SetDexterity(int dexterityValue);

	void SetStamina(int staminaValue);

};

#endif
