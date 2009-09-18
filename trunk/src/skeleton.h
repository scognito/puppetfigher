#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "bone.h"
#include "animation.h"
#include <math.h>
#include <vector>
#include <fat.h>
#include <string.h>

//#include "Box2D.h"
	
class Skeleton {
	public:
		Skeleton(float x, float y, const char* skelFilePath);
		
		~Skeleton();
		
		//Skeleton Absolute Position
		void SetPosition(float x, float y);
		
		//Skeleton Absolute Rotation
		void SetRotation(float ang);
		void SetBoneRotation(int boneId, float ang);
		
		void SetCurrentAnimation(int anim_id);
		int GetCurrentAnimation(){return _CurrentAnimation;}
		
		void StepAnimation(float step_size, float current_step);
		
		void SetBoneImage(int boneId, Image* img);
		void SetBoneImageOffsets(int boneId, float dx, float dy, float dang);
		
		int GetBoneId(Armor::Category::Type type, Armor::Side::Type side = Armor::Side::RIGHT);
		
		void Draw(float x_offset, float y_offset);
		
		char* GetAnimationNameById(int anim_id);
		int GetAnimationIdByName(const char* name);

		float GetX(){return _position_x;}
		float GetY(){return _position_y;}
		float GetRotation(){return _rotation;}

		//Text debug
		void Print();
		
		void SetFlip(bool f){_flip = f;}
		
		int GetFrameCount(const char* name);
		
	private:
		
		void ParseAnimation(std::string file);
		void ParseSkeleton(std::string file);
		
		float CircleDistance(float rot1, float rot2);
		
		//variable to store current animation frame
		int _animationFrame;

		std::vector<Bone*> _BoneVector;
		std::vector<Animation::Type> _Animations;
		
		int _CurrentAnimation;

		float _position_x;
		float _position_y;
		float _rotation;
	
		float _x_offset;
		float _y_offset;
		
		bool _flip;
		
		//Skelton Physics
		//b2World *_worldPtr;
		//b2Body *_body;
		//LEGS
};

#endif //_SKELETON_H_
