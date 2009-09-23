#ifndef _Player_H_
#define _Player_H_

#include "skeleton.h"

#include "armor.h"
#include "weapon.h"
#include "bullet.h"

#include <Box2D.h>

#include "commontypes.h"
class Bullet;
class Player : public Skeleton{

	public:
		Player(float x, float y, const char* animation_file, b2World *w, float playerHeight, float playerWidth);
		~Player();
	
		void SetArmor(Armor::Type armor);
		void MovePlayer(float dx, float dy, bool skipSetAnimation = false);
		
		void SetWeapon(Weapon::Type weapon);
		Weapon::Type GetWeapon(){return _weapon;};
		
		Bullet* FireWeapon(b2Vec2 direction);
		
		void AimArm(float angle);
		
		void Jump();
		
		void Render();
		
		void Crouch();
		void UnCrouch();
		void setDamage(int damage);
		
		b2Body *GetBody(){return _body;}
		
	private:
		Skeleton* _skeleton;

		//Armor (Images)
		Armor::Type _armor[Armor::Category::SIZE];

		//Inventory
		
		//weapon
		Weapon::Type _weapon;
		
		int _crouchOffset;
		int _jumpTimer;
		
		//Physics Stuff
		b2Body *_body;
		b2World *_world;
		float _last_y;
		float _width;
		float _height;

		int _energy;
};

#endif //_Player_H_
