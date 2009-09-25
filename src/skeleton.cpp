#include "skeleton.h"
#include <fat.h>
#include <string>

using namespace Animation;

Skeleton::Skeleton(float x, float y, const char* skelFilePath)
{
 	char next_type[100];

	std::string skelFile;
	skelFile.assign(skelFilePath);

	std::string tstr;

	do 
	{
		tstr = skelFile.substr(0, skelFile.find('\n'));
		skelFile = skelFile.substr(skelFile.find('\n')+1,skelFile.length());
		if(tstr.length() < 3) break;

		/* Get the info about this bone*/
		sscanf(tstr.c_str(), "%s\n", next_type);
	 
		if(strcmp(next_type,"skeleton")==0)
		{
			ParseSkeleton(skelFile);
		}
		else if(strcmp(next_type,"animation")==0)
		{
			ParseAnimation(skelFile);
		}
	}while (skelFile.length() > 0 && tstr.length() > 0);
	
	_position_x = x;
	_position_y = y;
	
	_x_offset = 0;
	_y_offset = 0;
	
	_rotation = 0;
	_flip = false;
	
	_SingleAnimation = false;
	
	_attackBone = Armor::Category::HEAD;
	_isAttacking = false;
}

Skeleton::~Skeleton()
{
}

void Skeleton::ParseSkeleton(std::string file)
{
	int i = 0;
	
 	char bone_name[100];
	int bone_count; 
	int bone_id,
		parent_bone;
	
	float angle, length;
	GXColor color = {0.0, 255.0, 0.0, 255.0};

	std::string tstr;

	tstr     = file.substr(0, file.find('\n'));
	file = file.substr(file.find('\n')+1,file.length());

 	/* Get the info about this bone*/
 	sscanf(tstr.c_str(), "%d\n", &bone_count);
 
 	while (i < bone_count)
 	{
		tstr     = file.substr(0, file.find('\n'));
		file = file.substr(file.find('\n')+1,file.length());

 		/* Get the info about this bone*/
 		sscanf(tstr.c_str(), "%d %d %f %f %s\n", &bone_id, &parent_bone, &angle, &length, bone_name);
 
 		/* Avoid empty strings, but this is ineffective for invalid strings */
 		if (tstr.length() < 3)
 			continue;
 
		if(angle < 0) angle += 360;
 
		if(parent_bone == -1)
		{
			_BoneVector.push_back(new Bone(NULL, angle, length, color, bone_name));
		}
		else
		{
			if((int)_BoneVector.size() > parent_bone)
			{
				_BoneVector.push_back(new Bone(_BoneVector[parent_bone], angle, length, color, bone_name));
			}
		}
		
		i++;
 	}

}

void Skeleton::ParseAnimation(std::string file)
{
	int i = 0;
	
	int frame_count;
 
	std::string tstr;

	tstr     = file.substr(0, file.find('\n'));
	file = file.substr(file.find('\n')+1,file.length());

	Animation::Type newAnim;
 	/* Get the info about this bone*/
 	sscanf(tstr.c_str(), "%s %d %d\n", newAnim.name, &newAnim.anim_id , &frame_count);
	
	newAnim.frame_count = frame_count;
	
 	while (i < frame_count)
 	{
	
		int j = 0;
		int num_bones = 0;
		
 		/* Read a row from the file (I hope that 512 characters are sufficient for a row) */
		KeyFrame::Type nextFrame;
		
		tstr     = file.substr(0, file.find('\n'));
		file = file.substr(file.find('\n')+1,file.length());

 		/* Get the info about this bone*/
 		sscanf(tstr.c_str(), "%f %f %d %f\n", &nextFrame.x, &nextFrame.y, &num_bones, &nextFrame.frame_delay);
 
		while(j < num_bones)
		{
			BonePosition::Type nextBone;
			
			tstr     = file.substr(0, file.find('\n'));
			file = file.substr(file.find('\n')+1,file.length());

			/* Get the info about this bone*/
			sscanf(tstr.c_str(), "%d %f\n", &nextBone.bone_id, &nextBone.angle);

			nextFrame.bone.push_back(nextBone);
			j++;
		}
		newAnim.frame.push_back(nextFrame);
		i++;
 	}
	
	_Animations.push_back(newAnim);

}


int Skeleton::GetBoneId(Armor::Category::Type type, Armor::Side::Type side)
{
	for(int i = 0; i < (int)_BoneVector.size(); i++)
	{
		if(_BoneVector[i]->GetType() == type)
		{
			if(_BoneVector[i]->GetSide() == side)
			{
				return i;
			}
		}
	}
	
	return -1;
}

void Skeleton::SetPosition(float x, float y){
	_x_offset = 0;
	_y_offset = 0;
	
	_position_x = x;
	_position_y = y;
	
	for(int i = 0; i < (int)_BoneVector.size(); i++)
	{
		if(_BoneVector[i]->IsRoot())
		{
			_BoneVector[i]->Kinematics(_position_x, _position_y, _rotation, _flip);
		}
	}
}

void Skeleton::SetRotation(float ang){
	_rotation = ang;
	
	for(int i = 0; i < (int)_BoneVector.size(); i++)
	{
		if(_BoneVector[i]->IsRoot())
		{
			_BoneVector[i]->Kinematics(_position_x, _position_y, _rotation, _flip);
		}
	}
}

void Skeleton::SetBoneRotation(int boneId, float ang){
	_rotation = ang;
	
	if(boneId < (int)_BoneVector.size())
	{
		_BoneVector[boneId]->SetAngle(ang);
		for(int i = 0; i < (int)_BoneVector.size(); i++)
		{
			if(_BoneVector[i]->IsRoot())
			{
				_BoneVector[i]->Kinematics(_position_x, _position_y, _rotation, _flip);
			}
		}
	}
}

void Skeleton::SetBoneImage(int boneId, Image* img){
	if(boneId >= 0 && boneId < (int)_BoneVector.size())
	{
		_BoneVector[boneId]->SetBoneImage(img);
	}
}

void Skeleton::SetBoneImageOffsets(int boneId, float dx, float dy, float dang){
	if(boneId >= 0 && boneId < (int)_BoneVector.size())
	{
		_BoneVector[boneId]->SetImageOffsets(dx, dy, dang);
	}
}

void Skeleton::Draw(float x_offset, float y_offset){
	for(int i = 0; i < (int)_BoneVector.size(); i++){
		if(_BoneVector[i] != NULL)
			_BoneVector[i]->Draw(x_offset, y_offset);
	}
	
	_BoneVector[GetBoneId(Armor::Category::TORSO)]->Draw(x_offset, y_offset);
	
	_BoneVector[GetBoneId(Armor::Category::BICEP, Armor::Side::LEFT)]->Draw(x_offset, y_offset);
	_BoneVector[GetBoneId(Armor::Category::FOREARM, Armor::Side::LEFT)]->Draw(x_offset, y_offset);
	_BoneVector[GetBoneId(Armor::Category::HAND, Armor::Side::LEFT)]->Draw(x_offset, y_offset);
	
}


char* Skeleton::GetAnimationNameById(int anim_id)
{
	for(int i = 0; i < (int)_Animations.size(); i++)
	{
		if(_Animations[i].anim_id == anim_id)
		{
			return _Animations[i].name;
		}
	}
	
	return NULL;
}

int Skeleton::GetFrameCount(const char* name)
{
	for(int i = 0; i < (int)_Animations.size(); i++)
	{
		if(strcmp(_Animations[i].name, name) == 0)
		{
			return _Animations[i].frame_count;
		}
	}
	
	return 0;
}
		
int Skeleton::GetAnimationIdByName(const char* name)
{
	for(int i = 0; i < (int)_Animations.size(); i++)
	{
		if(strcmp(_Animations[i].name, name) == 0)
		{
			return _Animations[i].anim_id;
		}
	}
	
	return -1;
}

void Skeleton::SetCurrentAnimation(int anim_id){
	if(_SingleAnimation)
		return;

	_CurrentAnimation = anim_id;
	_SingleAnimation  = false;
	
	if(_CurrentAnimation < 0) _CurrentAnimation = (int)_Animations.size() - 1;
	
	if(_CurrentAnimation >= (int)_Animations.size()) _CurrentAnimation = 0;
	
	//Reset Animation Frame
	_animationFrame = 0;
}

void Skeleton::SetCurrentAnimation(int anim_id, int nextAnimation){
	if(_SingleAnimation)
		return;
		
	_CurrentAnimation = anim_id;
	_NextAnimation    = nextAnimation;
	_SingleAnimation  = true;
	
	if(_CurrentAnimation < 0) _CurrentAnimation = (int)_Animations.size() - 1;
	
	if(_CurrentAnimation >= (int)_Animations.size()) _CurrentAnimation = 0;
	
	//Reset Animation Frame
	_animationFrame = 0;
}


float Skeleton::CircleDistance (float rot1, float rot2){ //Finds the distance from rot1 to rot2
	float pt1 = rot1;
	float pt2 = rot2;
	float ret = 0;
	
	while (pt1 >= 360.0f){
		pt1 -= 360.0f;
	}
	
	while (pt1 < 0.0f){
		pt1 += 360.0f;
	}
	
	while (pt2 >= 360.0f){
		pt2 -= 360.0f;
	}
	
	while (pt2 < 0.0f){
		pt2 += 360.0f;
	}
	
	
	if (pt2 > pt1)
	{
		if (fabs(pt2-pt1)<fabs((pt2-pt1)-360.0f))
		{
			ret = pt2-pt1;
		}
		else
		{
			ret = (pt2-pt1)-360.0f;
		}
	}
	else
	{
		if (fabs(pt2-pt1)<fabs((pt2-pt1)+360.0f))
		{
			ret = pt2-pt1;
		}
		else
		{
			ret = (pt2-pt1)+360.0f;
		}
	}
	return ret;
}

void Skeleton::StepAnimation(float step_size, float current_step){
		
	if(_CurrentAnimation < (int)_Animations.size() && _CurrentAnimation >= 0)
	{
		
		int f = _animationFrame % _Animations[_CurrentAnimation].frame_count;
		int next_f = (_animationFrame+1) % _Animations[_CurrentAnimation].frame_count;
		
		float x_int = (1-(current_step/step_size))*_Animations[_CurrentAnimation].frame[f].x 
							+ (current_step/step_size)*_Animations[_CurrentAnimation].frame[next_f].x;

		float y_int = (1-(current_step/step_size))*_Animations[_CurrentAnimation].frame[f].y 
							+ (current_step/step_size)*_Animations[_CurrentAnimation].frame[next_f].y;
							
		_position_x = x_int + _x_offset;
		_position_y = y_int + _y_offset;
		
		for(int i = 0; i < (int)_Animations[_CurrentAnimation].frame[f].bone.size(); i++)
		{
			BonePosition::Type *bonePtr = &(_Animations[_CurrentAnimation].frame[f].bone[i]);
			BonePosition::Type *nextBonePtr = &(_Animations[_CurrentAnimation].frame[next_f].bone[i]);
			
			if(bonePtr->bone_id >= 0 && bonePtr->bone_id < (int)_BoneVector.size() && 
			  (nextBonePtr->bone_id >= 0 && nextBonePtr->bone_id < (int)_BoneVector.size()))
			{
				float ang_int = bonePtr->angle + (CircleDistance(bonePtr->angle,nextBonePtr->angle)*(current_step/step_size));
				//float ang_int = (1-(current_step/step_size))*bonePtr->angle + ((current_step/step_size))*nextBonePtr->angle;
				_BoneVector[bonePtr->bone_id]->SetAngle(ang_int);
				
				if(_BoneVector[bonePtr->bone_id]->IsRoot()) {
					_BoneVector[bonePtr->bone_id]->Kinematics(_position_x, _position_y, 0, true);
				}
			}
		}
	}
	
		if(step_size == current_step)
			_animationFrame++;
		
	if(_animationFrame+1 >= _Animations[_CurrentAnimation].frame_count && _SingleAnimation)
	{
		_SingleAnimation = false;
		SetCurrentAnimation(_NextAnimation);
		
		//Kill attacking just incase this was an attack animation
		_attackBone = Armor::Category::HEAD;
		_isAttacking = false;
	}
}	

Sprite* Skeleton::GetBoneSprite(Armor::Category::Type boneType, Armor::Side::Type sideType)
{	
	for(int i = 0; i < (int)_BoneVector.size(); i++)
	{
		if(_BoneVector[i]->GetType() == boneType && _BoneVector[i]->GetSide() == sideType)
		{
			return _BoneVector[i]->GetSprite();
		}
	}


	return NULL;
}
		
bool Skeleton::CollidesWith(Sprite* colSprite, Armor::Category::Type boneType, Armor::Side::Type sideType)
{
	for(int i = 0; i < (int)_BoneVector.size(); i++)
	{
		if(_BoneVector[i]->GetType() == boneType  && _BoneVector[i]->GetSide() == sideType)
		{
			if(colSprite->CollidesWith(_BoneVector[i]->GetSprite(), true))
			{
				return true;
			}
		}
	}
	
	return false;
}

void Skeleton::SetAttacking(Armor::Category::Type attackBone)
{
	_attackBone = attackBone;
	_isAttacking = true;
}

//Text debug print

void Skeleton::Print(){
	printf("Num Bones: %d\n",_BoneVector.size());
	
	for(int i = 0; i < (int)_BoneVector.size(); i++)
	{
		printf("   id: %d ang: %f mag: %f\n",i,_BoneVector[i]->GetAngle(), _BoneVector[i]->GetMagnitude());
	}
	
	printf("\n");
	
	printf("Num Animations: %d\n", _Animations.size());
	
	for(int i = 0; i < (int)_Animations.size(); i++)
	{
		printf(" Animation (%d) name: %s id: %d num_frames: %d\n",i,_Animations[i].name, _Animations[i].anim_id, _Animations[i].frame_count);
		
		for(int j = 0; j < (int)_Animations[i].frame.size(); j++)
		{
			printf("    Frame (%d) x: %f y: %f Delay: %f\n",j,_Animations[i].frame[j].x, _Animations[i].frame[j].y, _Animations[i].frame[j].frame_delay);
			
			for(int k = 0; k < (int)_Animations[i].frame[j].bone.size(); k++)
			{
				printf("       Bone (%d) id: %d ang: %f\n",k,_Animations[i].frame[j].bone[k].bone_id, _Animations[i].frame[j].bone[k].angle);
			}
		}
	}
	
	printf("----------------------------------\n");

}
