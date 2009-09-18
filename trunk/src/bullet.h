#ifndef _Bullet_H_
#define _Bullet_H_

#include <wiisprite.h>
#include "Box2D.h"
#include "player.h"

using namespace wsp;

class Player;
class Bullet{
   public:
	  Bullet(float x, float y, b2Vec2 velocity, Image* img, int max_tof);
	  ~Bullet();
	  
      //return true if still in the world, else false
      bool Update();

	  float GetX(){return _bulletSprite.GetX();}
	  float GetY(){return _bulletSprite.GetY();}
	  float GetAngle(){return _bulletSprite.GetRotation();}
	  
	  void Draw();

	  void Delete(){_time_of_flight = _max_tof+1;}

	  Sprite* GetSprite(){return &_bulletSprite;}

   private:
      int _max_distance();
	  
	  float _time_of_flight;
	  float _max_tof;
	  
	  float _start_x;
	  float _start_y;
	  
	  b2Vec2 _velocity;
	  	  
	  Sprite _bulletSprite;
	  
	  Player* owner; //Pointer to who shot the bullet
};

#endif //_Bullet_H_
