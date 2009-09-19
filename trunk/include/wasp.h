#ifndef _WASP_H_
#define _WASP_H_

#include "entity.h"
#include <wiisprite.h>

using namespace wsp;

class Wasp : public Entity {
	public:
		Wasp(float x, float y, Image* img);
		~Wasp();
	
		void Render(float shiftx = 0);
		
	private:
		int _frameCount;
		bool _switchDirection;
		float _dx;
		float _dy;
		


};

#endif //_WASP_H_
