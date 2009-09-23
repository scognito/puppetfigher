#include "bone.h"
#include <math.h>

Bone::Bone(Bone * parent, float angle, float m, GXColor color, char* bone_name) {
	_x = 0;
	_y = 0;
	_angle = angle;
	_m = m;
	
	_color = color;
	
	if(parent != NULL)
	parent->Attach(this);
	_parent = parent;

	_quad.SetFillColor(color);
		
	_imageSet = false;
	
	_flip = false;
	
	SetBoneNameType(bone_name);
	
	#ifdef DEBUG
	debug_enabled = true;
	#else
	debug_enabled = false;
	#endif
}


Bone::~Bone(){

}

void Bone::SetBoneNameType(char* name)
{
	if(strcmp(name,"head") == 0)
	{
		type = Armor::Category::HEAD;
		side = Armor::Side::RIGHT;
	}
	else if(strcmp(name,"torso") == 0)
	{
		type = Armor::Category::TORSO;
		side = Armor::Side::RIGHT;
	}
	else if(strcmp(name,"lbicep") == 0)
	{
		type = Armor::Category::BICEP;
		side = Armor::Side::LEFT;
	}
	else if(strcmp(name,"rbicep") == 0)
	{
		type = Armor::Category::BICEP;
		side = Armor::Side::RIGHT;
	}
	else if(strcmp(name,"lforearm") == 0)
	{
		type = Armor::Category::FOREARM;
		side = Armor::Side::LEFT;
	}
	else if(strcmp(name,"rforearm") == 0)
	{
		type = Armor::Category::FOREARM;
		side = Armor::Side::RIGHT;
	}
	else if(strcmp(name,"lhand") == 0)
	{
		type = Armor::Category::HAND;
		side = Armor::Side::LEFT;
	}
	else if(strcmp(name,"rhand") == 0)
	{
		type = Armor::Category::HAND;
		side = Armor::Side::RIGHT;
	}
	else if(strcmp(name,"lthigh") == 0)
	{
		type = Armor::Category::THIGH;
		side = Armor::Side::LEFT;
	}
	else if(strcmp(name,"rthigh") == 0)
	{
		type = Armor::Category::THIGH;
		side = Armor::Side::RIGHT;
	}
	else if(strcmp(name,"lcalf") == 0)
	{
		type = Armor::Category::CALF;
		side = Armor::Side::LEFT;
	}
	else if(strcmp(name,"rcalf") == 0)
	{
		type = Armor::Category::CALF;
		side = Armor::Side::RIGHT;
	}
	else if(strcmp(name,"lfoot") == 0)
	{
		type = Armor::Category::FOOT;
		side = Armor::Side::LEFT;
	}
	else if(strcmp(name,"rfoot") == 0)
	{
		type = Armor::Category::FOOT;
		side = Armor::Side::RIGHT;
	}
}

void Bone::SetBoneImage(Image* img){
	//Image Set
	
	_boneSprite.SetImage(img);
	_imageSet = true;
	
}

void Bone::SetImageOffsets(float dx, float dy, float dang)
{
	_skinDx = dx;
	_skinDy = dy;
	_skinDangle = dang;
}

bool Bone::IsRoot()
{
	if(_parent == NULL)
	{
		return true;
	}
	
	return false;
}

void Bone::Attach(Bone * child) {
   _boneList.push_back(child);
}

void Bone::Kinematics(float x, float y, float rotation, bool flip) {
	_x = x;
	_y = y;
	_absAngle = rotation + _angle;
//   if(_parent) {
//     _x += _parent->GetJointX();
//     _y += _parent->GetJointY();
//     _angle += _parent->GetAngle();
//   }

	_flip = flip;

	float m_flip = 1;
	
	if(flip) m_flip = -1;

	_jointx = _x + m_flip*_m * cos(_absAngle * (M_PI / 180));
	_jointy = _y + _m * sin(_absAngle * (M_PI / 180));
	
	//             ^ might need to multiply by -1 here?
	//               (for the y calculation only)
	for (int i = 0; i < (int)_boneList.size(); i++) {
		_boneList[i]->Kinematics(_jointx, _jointy, _absAngle, flip);
	}
}

void Bone::Draw(float x_offset, float y_offset){

	bool t_flip = _flip;
	
	if(Armor::Category::HAND == type &&
		side == Armor::Side::RIGHT)
			t_flip = !_flip;
		

	if(_imageSet)
	{
		if(t_flip)
		{
			_boneSprite.SetTransform(TRANS_MIRROR);
		}
		else
		{
			_boneSprite.SetTransform(TRANS_NONE);
		}
		
		_boneSprite.SetPosition((_x + _jointx)/2.0 - _boneSprite.GetWidth()/2 + _skinDx, (_y + _jointy)/2.0 - _boneSprite.GetHeight()/2 + _skinDy);
		
		float angle_bump = 0;
		if(type != Armor::Category::TORSO && type != Armor::Category::HEAD)
			angle_bump = 90;
		
		if(!_flip)
		{
			_boneSprite.SetRotation((_absAngle)/2.0 + _skinDangle/2.0 + angle_bump);
		}
		else
		{
			_boneSprite.SetRotation(-1*((_absAngle)/2.0) + -1*_skinDangle/2.0 + angle_bump);
		}


		_boneSprite.Draw(x_offset, y_offset);
	}
	
	if(!_imageSet || debug_enabled)
	{
		Mtx model;
		guMtxIdentity(model);
		GX_LoadPosMtxImm(model, GX_PNMTX0);

		GX_SetLineWidth(30,GX_TO_ONE);
		
		GXColor t_color = _color; //_boneList[i]->GetColor();
				// Turn off texturing
		GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
		GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);

		// Draw a Quad
		GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 2);
		GX_Position2f32(_jointx, _jointy);
		GX_Color4u8(t_color.r, t_color.g, t_color.b, t_color.a);//_boneList[i]->GetColor().r, _boneList[i]->GetColor().g, _boneList[i]->GetColor().b, _boneList[i]->GetColor().a);
		
		GX_Position2f32(_x, _y);
		GX_Color4u8(t_color.r, t_color.g, t_color.b, t_color.a);//_boneList[i]->GetColor().r, _boneList[i]->GetColor().g, _boneList[i]->GetColor().b, _boneList[i]->GetColor().a);
		GX_End();
			
		// Turn texturing back on
		GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	}
	
	
}
