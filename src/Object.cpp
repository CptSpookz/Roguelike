#include "../include/Object.hpp"
#include "../include/TextureManager.hpp"

// Default constructor.
Object::Object() :
m_position{ 0.f, 0.f },
m_animationSpeed(0),
m_isAnimated(false),
m_frameCount(0),
m_currentFrame(0),
m_frameWidth(0),
m_frameHeight(0),
m_timeDelta(0){}

// Gives the object the given sprite.
bool Object::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed) {
	// Create a sprite from the loaded texture.
	m_sprite.setTexture(texture);

	// Set animation speed.
	m_animationSpeed = frameSpeed;

	// Store the number of frames.
	m_frameCount = frames;

	// Calculate frame dimensions.
	sf::Vector2u texSize = m_sprite.getTexture()->getSize();
	m_frameWidth = texSize.x / m_frameCount;
	m_frameHeight = texSize.y;

	// Check if animated or static.
	if (frames > 1){
		// Set sprite as animated.
		m_isAnimated = true;

		// Set the texture rect of the first frame.
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	}
	else{
		// Set sprite as non animated.
		m_isAnimated = false;
	}

	// Set the origin of the sprite.
	m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

	return true;
}

// Sets the position of the object.
void Object::SetPosition(sf::Vector2f position) {
	m_position.x = position.x;
	m_position.y = position.y;
	m_sprite.setPosition(m_position.x, m_position.y);
}

// Sets the animation state of the object.
void Object::SetAnimated(bool isAnimated) {
	m_isAnimated = isAnimated;

	if (m_isAnimated)
		m_currentFrame = 0;

	else
		// set the texture rect of the first frame
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

// Draws the object to the given render window.
void Object::Draw(sf::RenderWindow &window, float timeDelta)
{
	// check if the sprite is animated
	if (m_isAnimated) {
		// add the elapsed time since the last draw call to the aggregate
		m_timeDelta += timeDelta;

		// check if the frame should be updated
		if (m_timeDelta >= (1.f / m_animationSpeed))
		{
			NextFrame();
			m_timeDelta = 0;
		}
	}

	window.draw(m_sprite);
}

// Advances the sprite forward a frame.
void Object::NextFrame(){
	// check if we reached the last frame
	if (m_currentFrame == (m_frameCount - 1))
		m_currentFrame = 0;
	else
		m_currentFrame++;

	// update the texture rect
	m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}

// Default constructor.
Entity::Entity() :
m_currentTextureIndex(static_cast<int>(ANIMATION_STATE::WALK_DOWN)),
m_health(0),
m_maxHealth(0),
m_mana(0),
m_maxMana(0),
m_attack(0),
m_defense(0),
m_strength(0),
m_dexterity(0),
m_stamina(0),
m_speed(0),
m_velocity({0.f, 0.f}){}

// Override the default Object::Update function.
void Entity::Update(float timeDelta){
	// Choose animation state.
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);

	if ((m_velocity.x != 0) || (m_velocity.y != 0)){
		if (abs(m_velocity.x) > abs(m_velocity.y)){
			if (m_velocity.x <= 0)
				animState = ANIMATION_STATE::WALK_LEFT;
			else
				animState = ANIMATION_STATE::WALK_RIGHT;
		}
		else{
			if (m_velocity.y <= 0)
				animState = ANIMATION_STATE::WALK_UP;
			else
				animState = ANIMATION_STATE::WALK_DOWN;
		}
	}

	// Set animation speed.
	if ((m_velocity.x == 0) && (m_velocity.y == 0)){
		// The character is still.
		if (IsAnimated()){
			// Update sprite to idle version.
			m_currentTextureIndex += 4;

			// Stop movement animations.
			SetAnimated(false);
		}
	}
	else{
		// The character is moving.
		if (!IsAnimated()){
			// Update sprite to walking version.
			m_currentTextureIndex -= 4;

			// Start movement animations.
			SetAnimated(true);
		}
	}

	// Set the sprite.
	if (m_currentTextureIndex != static_cast<int>(animState)){
	 	m_currentTextureIndex = static_cast<int>(animState);
		m_sprite.setTexture(TextureManager::getTexture(m_textureIDs[m_currentTextureIndex]));
	}
}

// Sets the entities attack stat.
void Entity::SetAttack(int attackValue){
  m_attack = attackValue;
}

// Sets the entities defense stat.
void Entity::SetDefense(int defenseValue){
	m_defense = defenseValue;
}

// Sets the entities strength stat.
void Entity::SetStrength(int strengthValue){
	m_strength = strengthValue;
}

// Sets the entities dexterity stat.
void Entity::SetDexterity(int dexterityValue){
	m_dexterity = dexterityValue;
}

// Sets the entities stamina stat.
void Entity::SetStamina(int staminaValue){
	m_stamina = staminaValue;
}
