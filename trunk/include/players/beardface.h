#ifndef _Beardface_H_
#define _Beardface_H_

#include "player.h"

class Beardface : public Player {
	public:
		Beardface(float x, float y, b2World* w);
		~Beardface();
	
	private:
		void InitArmor();
		void InitWeapon();

};

#endif //_Beardface_H_
