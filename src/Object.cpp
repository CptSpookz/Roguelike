#include "../include/Object.hpp"
#include "../include/TextureManager.hpp"

// Default constructor.
Object::Object() :
position{ 0.f, 0.f },
animationSpeed(0),
isAnimated(false),
frameCount(0),
currentFrame(0),
frameWidth(0),
frameHeight(0),
timeDelta(0){}

// Gives the object the given sprite.
bool Object::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed) {
	// Create a sprite from the loaded texture.
	this->sprite.setTexture(texture);

	// Set animation speed.
	this->animationSpeed = frameSpeed;

	// Store the number of frames.
	this->frameCount = frames;

	// Calculate frame dimensions.
	sf::Vector2u texSize = sprite.getTexture()->getSize();
	frameWidth = texSize.x / frameCount;
	frameHeight = texSize.y;

	// Check if animated or static.
	if (frames > 1){
		// Set sprite as animated.
		this->isAnimated = true;

		// Set the texture rect of the first frame.
		sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	}
	else{
		// Set sprite as non animated.
		this->isAnimated = false;
	}

	// Set the origin of the sprite.
	sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);

	return true;
}

// Sets the position of the object.
void Object::SetPosition(sf::Vector2f position) {
	this->position.x = position.x;
	this->position.y = position.y;
	sprite.setPosition(this->position.x, this->position.y);
}

// Sets the animation state of the object.
void Object::SetAnimated(bool isAnimated) {
	this->isAnimated = isAnimated;

	if (this->isAnimated)
		currentFrame = 0;

	else
		// set the texture rect of the first frame
		sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

// Draws the object to the given render window.
void Object::Draw(sf::RenderWindow &window, float timeDelta)
{
	// check if the sprite is animated
	if (isAnimated) {
		// add the elapsed time since the last draw call to the aggregate
		this->timeDelta += timeDelta;

		// check if the frame should be updated
		if (this->timeDelta >= (1.f / animationSpeed))
		{
			NextFrame();
			this->timeDelta = 0;
		}
	}

	window.draw(this->sprite);
}

// Advances the sprite forward a frame.
void Object::NextFrame()
{
	// check if we reached the last frame
	if (currentFrame == (frameCount - 1))
		currentFrame = 0;
	else
		currentFrame++;

	// update the texture rect
	sprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight));
}

// Default constructor.
Entity::Entity() :
currentTextureIndex(static_cast<int>(ANIMATION_STATE::WALK_DOWN)),
health(0),
maxHealth(0),
mana(0),
maxMana(0),
attack(0),
defense(0),
strength(0),
dexterity(0),
stamina(0),
speed(0),
velocity({0.f, 0.f}){}

// Override the default Object::Update function.
void Entity::Update(float timeDelta){
	// Choose animation state.
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(currentTextureIndex);

	if ((velocity.x != 0) || (velocity.y != 0)){
		if (abs(velocity.x) > abs(velocity.y)){
			if (velocity.x <= 0)
				animState = ANIMATION_STATE::WALK_LEFT;
			else
				animState = ANIMATION_STATE::WALK_RIGHT;
		}
		else{
			if (velocity.y <= 0)
				animState = ANIMATION_STATE::WALK_UP;
			else
				animState = ANIMATION_STATE::WALK_DOWN;
		}
	}

	// Set animation speed.
	if ((velocity.x == 0) && (velocity.y == 0)){
		// The character is still.
		if (IsAnimated()){
			// Update sprite to idle version.
			currentTextureIndex += 4;

			// Stop movement animations.
			SetAnimated(false);
		}
	}
	else{
		// The character is moving.
		if (!IsAnimated()){
			// Update sprite to walking version.
			currentTextureIndex -= 4;

			// Start movement animations.
			SetAnimated(true);
		}
	}

	// Set the sprite.
	if (currentTextureIndex != static_cast<int>(animState)){
	 	currentTextureIndex = static_cast<int>(animState);
		sprite.setTexture(TextureManager::getTexture(textureIDs[currentTextureIndex]));
	}
}

// Sets the entities attack stat.
void Entity::SetAttack(int attackValue){
  attack = attackValue;
}

// Sets the entities defense stat.
void Entity::SetDefense(int defenseValue){
	defense = defenseValue;
}

// Sets the entities strength stat.
void Entity::SetStrength(int strengthValue){
	strength = strengthValue;
}

// Sets the entities dexterity stat.
void Entity::SetDexterity(int dexterityValue){
	dexterity = dexterityValue;
}

// Sets the entities stamina stat.
void Entity::SetStamina(int staminaValue){
	stamina = staminaValue;
}
