#ifndef OBJECT_HPP
#define OBJECT_HPP
//SFML
#include <SFML/Graphics.hpp>

//Roguelike
#include <Level.hpp>
#include <Util.hpp>
#include <TextureManager.hpp>


class Object {
private:
	// speed of sprite's animation
	int m_animSpeed;

	// number of texture's frames
	int m_frameNum;

	// current texture frame
	int m_currentFrame;

	// texture's frames' dimensions
	int m_frameWidth;
	int m_frameHeight;

	// is the texture animated?
	bool m_isMoving;

	// time between draw() calls
	float m_timeDelta;

	void nextFrame();

protected:
	// char sprite
	sf::Sprite m_sprite;
	// sprite position
	sf::Vector2f m_position;

public:
	Object();

	sf::Sprite& getSprite() {return m_sprite;};
	void setSprite(sf::Texture&, int, int);

	sf::Vector2f getPosition() const {return m_position;};
	void setPosition(double, double);

	int getFrameNum() const {return m_frameNum;};

	int getSpeed() const {return m_animSpeed;};
	void setSpeed(int);

	bool isMoving() const {return m_isMoving;};
	void setMovement(bool);

	virtual void update(float) = 0;

	virtual void draw(sf::RenderWindow&, float);

};

#endif
