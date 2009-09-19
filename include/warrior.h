#ifndef _Warrior_H_
#define _Warrior_H_

#include "player.h"

class Warrior : public Player {
	public:
		Warrior(float x, float y, b2World* w);
		~Warrior();
	
	private:
		void InitArmor();
		void InitWeapon();

};

#endif //_Warrior_H_
