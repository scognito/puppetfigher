#ifndef _Weapon_H_
#define _Weapon_H_

#include <wiisprite.h>

using namespace wsp;

namespace Weapon {
	namespace Category {
		enum Type {
			GUN    = 0
		};
	}
	
	struct Type {
		Category::Type weapon_type;
		Image* img;
		Image* bullet_image;
		
		//display props
		//Offsets to get the image to look right on the body.
		float dx;
		float dy;
		
		float dang;
		
		//add other properties here... strength whatever
		float velocity;
		float bullet_strength;
		float power_consumption;
		float firing_delay;
		
		float max_tof;
	};
}

#endif //_Weapon_H_
