#ifndef _Animation_H_
#define _Animation_H_

#include <vector>
#include "armor.h"
namespace Animation {

	namespace BonePosition {
		struct Type {
			int   bone_id;
			float angle;
			
		};
	}
	
	namespace KeyFrame {
		struct Type {
			float x;
			float y;
			float   frame_delay;
			
			std::vector<BonePosition::Type> bone;
		};
	}
	
	struct Type {
		char  name[100];
		int   anim_id;
		int   frame_count;
		
		std::vector<KeyFrame::Type> frame;
	};
}

#endif //_Animation_H_
