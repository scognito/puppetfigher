#include "entity.h"

Entity::Entity(float x, float y, Image* img)
{
	_sprite.SetPosition(x,y);
	_sprite.SetImage(img);
	
	_isAlive = true;
	
    _screenX = x;
	_screenY = y;
}


Entity::~Entity()
{

}

void Entity::UpdatePosition(float x, float y)
{
    _screenX = x;
	_screenY = y;
	_sprite.SetPosition(x,y);
}

void Entity::SetXOffset(float shiftx)
{
	_sprite.SetPosition(_screenX - shiftx,_screenY);
}

void Entity::UpdateDirection(b2Vec2 direction)
{
   //TODO
}

bool Entity::CheckHit(Bullet* bullet)
{
    //TODO currently 1 hit = 1 kill
	_isAlive = !((bullet->GetSprite())->CollidesWith(&_sprite));
	
	return _isAlive;
}


void Entity::Draw()
{
	_sprite.Draw();
}