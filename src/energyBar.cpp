#include "energyBar.h"

EnergyBar::EnergyBar()
{
	_p1Energy = 100;
	_p2Energy = 100;

	p1EnergyBar.SetWidth(300);
	p1EnergyBar.SetHeight(32);
	p1EnergyBar.SetBorder(1);
	p1EnergyBar.SetFillColor((GXColor){0xFF, 0xFF, 0x00, 0xFF});

	p2EnergyBar.SetWidth(300);
	p2EnergyBar.SetHeight(32);
	p2EnergyBar.SetBorder(1);
	p2EnergyBar.SetFillColor((GXColor){0xFF, 0xFF, 0x00, 0xFF});

	p1EnergyBarEmpty.SetWidth(300);
	p1EnergyBarEmpty.SetHeight(32);
	p1EnergyBarEmpty.SetBorder(1);
	p1EnergyBarEmpty.SetFillColor((GXColor){0xFF, 0x00, 0x00, 0xFF});

	p2EnergyBarEmpty.SetWidth(300);
	p2EnergyBarEmpty.SetHeight(32);
	p2EnergyBarEmpty.SetBorder(1);
	p2EnergyBarEmpty.SetFillColor((GXColor){0xFF, 0x00, 0x00, 0xFF});
}

EnergyBar::~EnergyBar()
{

}

void EnergyBar::UpdateValues(int p1EnergyVal, int p2EnergyVal){

	p1EnergyBar.SetWidth(3*p1EnergyVal);
	p2EnergyBar.SetWidth(3*p2EnergyVal);
}

void EnergyBar::Draw()
{
	p1EnergyBarEmpty.Draw(6, 32);
	p2EnergyBarEmpty.Draw(334, 32);


	p1EnergyBar.Draw(6+300-(p1EnergyBar.GetWidth()), 32);
	p2EnergyBar.Draw(334, 32);

}
