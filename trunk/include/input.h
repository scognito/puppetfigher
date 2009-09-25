#ifndef _INPUT_H_
#define _INPUT_H_

#include <wiiuse/wpad.h>

enum {
	INPUT_GC = 0,
	INPUT_WII,
	INPUT_WII_SIDE,
};

enum {
	BUTTON_UP = 0,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_PAUSE,
	BUTTON_PUNCH,
	BUTTON_KICK,
	BUTTON_OPTION_1,
	BUTTON_OPTION_2,
};

enum {
	ACTION_DOWN = 0,
	ACTION_UP,
	ACTION_HELD,
};

class Input {

	public:
		Input();
		~Input();

		int getType();
		void scanPads();
		void setType(int padType);
		bool doButton(int padNumber, int button, int action);

	private:
		int _type;
};

#endif
