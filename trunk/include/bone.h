#ifndef _BONE_H_
#define _BONE_H_

#include <wiisprite.h>

#include "armor.h"

using namespace wsp;

#include <vector>

//Generic Bone Definition

class Bone {
	public:

		Bone(Bone * parent, float angle, float m, GXColor color, char* bone_name);
		~Bone();

		void Attach(Bone * child);

		void Kinematics(float x, float y, float rotation, bool flip);
		
		void SetBoneImage(Image* img);
		void SetImageOffsets(float dx, float dy, float dang);
		
		Sprite *GetSprite(){return &_boneSprite;}
		
		void SetBoneNameType(char* name);
		
		void Draw(float x_offset, float y_offset);
		
		float GetX(){return _x;}
		float GetY(){return _y;}
		
		float GetJointX(){return _jointx;}
		float GetJointY(){return _jointy;}
		
		float GetAngle(){return _angle;}
		void SetAngle(float angle){_angle = angle;}
		void SetAbsAngle(float angle){_absAngle = angle;}

		float GetMagnitude(){return _m;}
		
		GXColor GetColor(){return _color;}
		
		bool IsRoot();
		
		
		Armor::Category::Type GetType(){return type;}
		Armor::Side::Type GetSide(){return side;}
		
	private:
		// The main (animatable) bone info
		float _angle; // degrees
		float _m; // magnitude
		// Position information, don't touch, Kinematics calculates this
		float _x, _y;
		float _jointx, _jointy;
		float _absAngle;

		GXColor _color;
		
		// list of 'child' bones
		std::vector<Bone*> _boneList;
		// the parent bone
		Bone *_parent;
		
		//Wiisprite stuff (for bone drawing)
		Image* _boneImage;
		Sprite _boneSprite;
		
		float _skinDx;
		float _skinDy;
		float _skinDangle;
		
		Rectangle _rect;
		Quad _quad;

		Armor::Category::Type type;
		Armor::Side::Type side;
		
		bool _flip;
		
		bool _imageSet;
		
		bool debug_enabled;

};

#endif //_BONE_H_
