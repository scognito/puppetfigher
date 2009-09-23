#include "player.h"

Player::Player(float x, float y, const char* animation_file, b2World* w, float playerHeight, float playerWidth) :
	Skeleton(x, y, animation_file)
{
	this->SetCurrentAnimation(0);
	
	_world = w;
	b2BodyDef bodyDef;
	bodyDef.position.Set((x)/ CommonTypes::PIXELS_PER_UNIT, (y)/ CommonTypes::PIXELS_PER_UNIT);
	bodyDef.angle = 0;
	_body = _world->CreateBody(&bodyDef);
	
	_last_y = y;
	
	_width = playerWidth;
	_height = playerHeight;
	
	_energy = 100;

	b2PolygonDef polydef;
	polydef.SetAsBox((float32(playerWidth/CommonTypes::PIXELS_PER_UNIT)/2.0), (float32(playerHeight/CommonTypes::PIXELS_PER_UNIT)/2.0));
	
  	polydef.density = CommonTypes::DEFAULT_DENSITY;
		
	polydef.friction = CommonTypes::DEFAULT_FRICTION;
	polydef.restitution = CommonTypes::DEFAULT_RESTITUTION;
	
	_body->CreateShape(&polydef);	
	
	_body->SetMassFromShapes();
	_jumpTimer    = 0;
	_crouchOffset = 0;
}

Player::~Player()
{

}

void Player::MovePlayer(float dx, float dy, bool skipSetAnimation)
{
	//TODO Fix these so they reference animations by name

	if(!skipSetAnimation)
	{
		if(dx == 0 && dy == 0)
		{
			if(this->GetCurrentAnimation() != 0)
				this->SetCurrentAnimation(0);
		}
		else if(abs(dx) > 0)
		{
			//Right now just have the walk animation, later, add run
			if(this->GetCurrentAnimation() != 1)
				this->SetCurrentAnimation(1);
		}
	}
	
	b2Vec2 pos = _body->GetWorldCenter();
	
	b2Vec2 v(pos.x + dx/ CommonTypes::PIXELS_PER_UNIT, pos.y+dy/ CommonTypes::PIXELS_PER_UNIT);
	_body->SetXForm(v, 0);
}

void Player::SetArmor(Armor::Type armor)
{
	_armor[armor.armor_type] = armor;
	
	switch(armor.armor_type)
	{
		case Armor::Category::HEAD: 
		case Armor::Category::TORSO: 
			this->SetBoneImage(this->GetBoneId(armor.armor_type), armor.img);
			this->SetBoneImageOffsets(this->GetBoneId(armor.armor_type), armor.dx, armor.dy, armor.dang);
			break;
		case Armor::Category::BICEP: 
		case Armor::Category::FOREARM: 
		case Armor::Category::HAND: 
		case Armor::Category::THIGH: 
		case Armor::Category::CALF: 
		case Armor::Category::FOOT: 
			this->SetBoneImage(this->GetBoneId(armor.armor_type, Armor::Side::LEFT), armor.img);
			this->SetBoneImageOffsets(this->GetBoneId(armor.armor_type, Armor::Side::LEFT), armor.dx, armor.dy, armor.dang);
			
			this->SetBoneImage(this->GetBoneId(armor.armor_type, Armor::Side::RIGHT), armor.img);
			this->SetBoneImageOffsets(this->GetBoneId(armor.armor_type, Armor::Side::RIGHT), armor.dx, armor.dy, armor.dang);
			break;
		default:
			break;
	}
	
}

Bullet* Player::FireWeapon(b2Vec2 direction)
{
   //TODO add some check to see if you can fire
   //TODO get arm angle using cross prod of direction and 1,0
   if(true)
   {
      b2Vec2 tv = direction;
	  tv*=_weapon.velocity;
      Bullet* bullet = new Bullet(this->GetX(), this->GetY(),tv,_weapon.bullet_image,_weapon.max_tof);
	  
	  
	  return bullet;
   }

   return NULL;
}

void Player::AimArm(float angle)
{
	  this->SetBoneRotation(this->GetBoneId(Armor::Category::BICEP, Armor::Side::LEFT), angle);
	  this->SetBoneRotation(this->GetBoneId(Armor::Category::FOREARM, Armor::Side::LEFT), 0);
	  this->SetBoneRotation(this->GetBoneId(Armor::Category::HAND, Armor::Side::LEFT), 0);
}


void Player::SetWeapon(Weapon::Type weapon)
{
	_weapon = weapon;
}

void Player::Jump()
{

	if(_jumpTimer == 0)
	{
		_jumpTimer = 120;
		
		b2Vec2 movement(0.0, 0.0);
		movement.y = 120.0;
		_body->ApplyImpulse( movement , _body->GetWorldCenter());
	}
	
}

void Player::Crouch()
{
	
	if(_crouchOffset < 40)
		_crouchOffset += 1;

}

void Player::UnCrouch()
{
	
	if(_crouchOffset > 0)
		_crouchOffset -= 1;
	//if(_crouchOffset > 0)
	//	_crouchOffset = 0;
}

void Player::setDamage(int damage)
{
	_energy -= damage;

	if(_energy < 0)
		_energy = 0;
}

void Player::Render()
{	
	if(_jumpTimer > 0)
		_jumpTimer--;

	b2Vec2 pos = _body->GetWorldCenter();
	
	_last_y = CommonTypes::PIXELS_PER_UNIT*pos.y;
	
	
	b2Vec2 v(pos.x, pos.y);
	_body->SetXForm(v, 0);
	
/* DEBUG Physics	
	GXColor color = {0.0, 255.0, 0.0, 255.0};

	Rectangle rect;
	Quad quad;
	rect.x = CommonTypes::PIXELS_PER_UNIT*pos.x - _width/2.0 + 20.0;
	rect.y = CommonTypes::PIXELS_PER_UNIT*pos.y - _height/2.0 + 25.0;
	rect.width = _width;
	rect.height = _height;
	quad.SetRectangle(&rect);
	quad.SetFillColor(color);
	quad.Draw();
	*/
	this->SetPosition(CommonTypes::PIXELS_PER_UNIT*pos.x, (int)(CommonTypes::PIXELS_PER_UNIT*pos.y) + _crouchOffset);
	
	this->Draw(0, _height/3.0);
}
