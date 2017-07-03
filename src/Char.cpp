#include <Char.hpp>
	Char::Char() :
	m_currentTexID(static_cast<int>(ANIMATION_STATE::WALK_DOWN)),
	m_charMaxHp(0),
	m_charHp(0),
	m_charBuffDmg(0),
	m_charBaseDmg(0),
	m_charSpeed(0),
	m_charVel({0.f,0.f}){}

void Char::setHP(double hpVal){
	if(hpVal >= 0)
		m_charHp = hpVal;
}

void Char::setBaseDmg(double dmgVal){
	if (dmgVal > 0)
		m_charBaseDmg = dmgVal;
}

void Char::setBuffDmg(double dmgBuff){
	if(dmgBuff >= 1)
		m_charBuffDmg = dmgBuff;
}

void Char::setBaseDef(double defVal){
	if (defVal > 0)
		m_charBaseDef = defVal;
}

void Char::setBuffDef(double defBuff){
	if (defBuff >= 1)
		m_charBuffDef = defBuff;
}

void Char::setBaseSpd(int spdVal){
	if (spdVal > 50)
		m_charSpeed = spdVal;
}

void Char::setBuffSpd(int spdBuff){
	if (spdBuff >= 1)
		m_charBuffSpeed = spdBuff;
}

void Char::update(float timeDelta){
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(m_currentTexID);

	//Set animation state
	if(m_charVel.x != 0 && m_charVel.y != 0){
		if (abs(m_charVel.x) > abs(m_charVel.y)){
			if (m_charVel.x <= 0)
				animState = ANIMATION_STATE::WALK_LEFT;
			else
				animState = ANIMATION_STATE::WALK_RIGHT;
		}
		else{
			if (m_charVel.y <= 0)
				animState = ANIMATION_STATE::WALK_UP;
			else
				animState = ANIMATION_STATE::WALK_DOWN;
		}
	}

	//Update sprite
	if(m_charVel.x == 0 && m_charVel.y == 0){
		  if (isMoving()){
	      m_currentTexID += 4;
	      setMovement(false);
	    }
	}
	else {
	   	if (!isMoving()){
	     	m_currentTexID -= 4;
	     	setMovement(true);
	    }
	}

	if(m_currentTexID != static_cast<int>(animState)){
		m_currentTexID = static_cast<int>(animState);
		m_sprite.setTexture(TextureManager::getTexture(m_textureIDs[m_currentTexID]));
	}

}
