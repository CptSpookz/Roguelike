#include <Object.hpp>

// Default constructor.
Object::Object() :
m_position{0.f, 0.f},
m_animSpeed(0),
m_isMoving(false),
m_frameNum(0),
m_currentFrame(0),
m_frameWidth(0),
m_frameHeight(0),
m_timeDelta(0){}

// Sets a texture into the object's sprite
void Object::setSprite(sf::Texture& texture, int frames, int framespeed){
	m_sprite.setTexture(texture);
	m_animSpeed = framespeed;
	m_frameNum = frames;

	sf::Vector2u textureSize = m_sprite.getTexture()->getSize();
	m_frameWidth = textureSize.x / m_frameNum;
	m_frameHeight = textureSize.y;

	if (frames > 1){
		m_isMoving = true;
		m_sprite.setTextureRect(sf::IntRect(0,0, m_frameWidth, m_frameHeight));
	}
	else
		m_isMoving = false;

	m_sprite.setOrigin(m_frameWidth/2.f, m_frameHeight/2.f);
}

// Sets the position of the object.
void Object::setPosition(double posX, double posY) {
	m_position.x = posX;
	m_position.y = posY;
	m_sprite.setPosition(m_position.x, m_position.y);
}

void Object::setSpeed(int speed){
	if(speed > 0){
		m_animSpeed = speed;
	}
}

// set the animation state of the object
void Object::setMovement(bool isAnimated) {
	m_isMoving = isAnimated;

	if(m_isMoving){
		m_currentFrame = 0;
	}

	else
		// set the texture rect of the first frame
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

// draw the object to the given render window.
void Object::draw(sf::RenderWindow &window, float timeDelta)
{
	// check if the sprite is animated
	if (m_isMoving) {
		// add the elapsed time since the last draw() call
		m_timeDelta += timeDelta;

		// check if the frame should be updated
		if (m_timeDelta >= (1.f / m_animSpeed))
		{
			nextFrame();
			m_timeDelta = 0;
		}
	}

	window.draw(m_sprite);
}

// Advances the sprite forward a frame.
void Object::nextFrame(){
	// check if we reached the last frame
	if (m_currentFrame == (m_frameNum - 1)){
		m_currentFrame = 0;
	}else{
		m_currentFrame++;
	}

	// update the texture rect
	m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}
