#include <Char.hpp>

	void Char::setHP(double hpVal){
		if(hpVal <= m_charMaxHp)
			m_charHp = hpVal;
	}
		
	void Char::setBuffDmg(double buffVal){
		if(buffVal >= 1)
			m_charBuffDmg = buffVal;
	}