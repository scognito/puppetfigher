#include "bullet.h"


Bullet::Bullet(float x, float y, b2Vec2 velocity, Image* img, int max_tof)
{
   _velocity = velocity;
   
   b2Vec2 vecT(0,1);
   
   _start_x = x;
   _start_y = y;
   
   _bulletSprite.SetPosition(x, y);
   _bulletSprite.SetImage(img);
   
   float ang = b2Dot(_velocity, vecT);
   
   _bulletSprite.SetRotation(ang/2.0);
   
   _time_of_flight = 1;
   
   _max_tof = max_tof;
   
}

Bullet::~Bullet(){}

bool Bullet::Update()
{
   if(_time_of_flight < _max_tof)
	{
	   b2Vec2 tv = _velocity;
	   tv *= _time_of_flight;
	   _bulletSprite.SetPosition(_start_x + tv.x, _start_y + tv.y);
	   _time_of_flight++;
	   return true;
	}
	return false;
}

void Bullet::Draw()
{
   _bulletSprite.Draw();
}
