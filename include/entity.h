#ifndef _Entity_H_
#define _Entity_H_

#include "wiisprite.h"
#include "bullet.h"

#include "Box2D.h"

using namespace wsp;

class Entity {

	public:
		Entity(float x, float y, Image* img);
		~Entity();

		void UpdatePosition(float x, float y);
		void UpdateDirection(b2Vec2 direction);
		
		bool CheckHit(Bullet* bullet);
		
		void Draw();
		
		void SetXOffset(float shiftx);
		
		bool IsAlive(){return _isAlive;}
		
		float GetX(){return _sprite.GetX();}
		float GetY(){return _sprite.GetY();}
		
	private:
		Sprite _sprite;
		
		b2Vec2 _direction;
		bool _isAlive;
		
		float _screenX, _screenY;
		
};

#endif //_Entity_H_
