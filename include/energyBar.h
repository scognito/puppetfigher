#ifndef _ENERGYBAR_H_
#define _ENERGYBAR_H_

#include "wiisprite.h"
#include "Box2D.h"
#include "player.h"

using namespace wsp;

class EnergyBar {

	public:
		EnergyBar();
		~EnergyBar();

		void UpdateValues(int p1EnergyVal, int p2EnergyVal);
		void Draw();

	private:
		int _p1Energy;
		int _p2Energy;

		Quad p1EnergyBar;
		Quad p1EnergyBarEmpty;

		Quad p2EnergyBar;
		Quad p2EnergyBarEmpty;
};

#endif
