#include "wasp.h"


Wasp::Wasp(float x, float y, Image* img)
 :Entity(x,y,img)
{

	_frameCount = 0;
	_switchDirection = true;
	_dx = 0;
	_dy = 0;
}

Wasp::~Wasp()
{

}

void Wasp::Render(float shiftx)
{

    if(_switchDirection)
	{
		_dx = rand()%10-5;
		_dy = rand()%10-5;
		
		_switchDirection = false;
		_frameCount = 0;
	}
	
	_frameCount++;
	
	if(_frameCount > 10)
	{
	   _switchDirection = true;
	}
	
    if(this->GetX() + _dx > 0 && this->GetX() + _dx < 480)
	{
		this->UpdatePosition(this->GetX()+_dx, this->GetY());
	}
	
    if(this->GetY() + _dy > 30 && this->GetY() + _dy < 300)
	{
		this->UpdatePosition(this->GetX(), this->GetY()+_dy);
	}
	
	this->SetXOffset(shiftx);
	
	this->Draw();

}