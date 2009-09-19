#ifndef _Armor_H_
#define _Armor_H_

#include <wiisprite.h>

using namespace wsp;

namespace Armor {
	namespace Category {
		enum Type {
			HEAD    = 0,
			TORSO   = 1,
			BICEP   = 2,
			FOREARM = 3,
			HAND    = 4,
			THIGH   = 5,
			CALF    = 6,
			FOOT    = 7,
			SIZE    = 8
		};
	}
	
	namespace Side {
		enum Type {
			RIGHT,
			LEFT
		};
	}
	
	struct Type {
		Category::Type armor_type;
		Image* img;
		
		//display props
		//Offsets to get the image to look right on the body.
		float dx;
		float dy;
		
		float dang;
		
		//add other properties here... strength whatever
	};
}

#endif //_Armor_H_
