#include "input.h"

Input::Input()
{
	_type = INPUT_WII_SIDE;
}

Input::~Input()
{

}

int Input::getType()
{
	return _type;
}

void Input::setType(int padType)
{
	_type = padType;
}

void Input::scanPads()
{
	switch(_type){
		case INPUT_WII:
		case INPUT_WII_SIDE:
			WPAD_ScanPads();
			break;

		case INPUT_GC:
			PAD_ScanPads();
			break;
	}
}

bool Input::doButton(int padNumber, int button, int action)
{
	switch(button)
	{
		case BUTTON_RIGHT:
			switch(_type){
				case INPUT_WII:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_RIGHT;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_RIGHT;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_RIGHT;
						break;
					}
				break;

				case INPUT_WII_SIDE:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_DOWN;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_DOWN;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_DOWN;
						break;
					}
				break;

				case INPUT_GC:
					switch(action){
						case ACTION_DOWN:
							return PAD_ButtonsDown(padNumber) & PAD_BUTTON_RIGHT;
						break;
						case ACTION_UP:
							return PAD_ButtonsUp(padNumber) & PAD_BUTTON_RIGHT;
						break;
						case ACTION_HELD:
							return PAD_ButtonsHeld(padNumber) & PAD_BUTTON_RIGHT;
						break;
					}
				break;
			}
		break;

		case BUTTON_LEFT:
			switch(_type){
				case INPUT_WII:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_LEFT;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_LEFT;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_LEFT;
						break;
					}
				break;

				case INPUT_WII_SIDE:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_UP;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_UP;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_UP;
						break;
					}
				break;

				case INPUT_GC:
					switch(action){
						case ACTION_DOWN:
							return PAD_ButtonsDown(padNumber) & PAD_BUTTON_LEFT;
						break;
						case ACTION_UP:
							return PAD_ButtonsUp(padNumber) & PAD_BUTTON_LEFT;
						break;
						case ACTION_HELD:
							return PAD_ButtonsHeld(padNumber) & PAD_BUTTON_LEFT;
						break;
					}
				break;
			}
		break;

		case BUTTON_UP:
			switch(_type){
				case INPUT_WII:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_UP;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_UP;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_UP;
						break;
					}
				break;

				case INPUT_WII_SIDE:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_RIGHT;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_RIGHT;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_RIGHT;
						break;
					}
				break;

				case INPUT_GC:
					switch(action){
						case ACTION_DOWN:
							return PAD_ButtonsDown(padNumber) & PAD_BUTTON_UP;
						break;
						case ACTION_UP:
							return PAD_ButtonsUp(padNumber) & PAD_BUTTON_UP;
						break;
						case ACTION_HELD:
							return PAD_ButtonsHeld(padNumber) & PAD_BUTTON_UP;
						break;
					}
				break;
			}
		break;

		case BUTTON_DOWN:
			switch(_type){
				case INPUT_WII:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_DOWN;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_DOWN;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_DOWN;
						break;
					}
				break;

				case INPUT_WII_SIDE:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_LEFT;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_LEFT;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_LEFT;
						break;
					}
				break;

				case INPUT_GC:
					switch(action){
						case ACTION_DOWN:
							return PAD_ButtonsDown(padNumber) & PAD_BUTTON_DOWN;
						break;
						case ACTION_UP:
							return PAD_ButtonsUp(padNumber) & PAD_BUTTON_DOWN;
						break;
						case ACTION_HELD:
							return PAD_ButtonsHeld(padNumber) & PAD_BUTTON_DOWN;
						break;
					}
				break;
			}
		break;

		case BUTTON_PAUSE:
			switch(_type){
				case INPUT_WII:
				case INPUT_WII_SIDE:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_HOME;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_HOME;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_HOME;
						break;
					}
				break;

				case INPUT_GC:
					switch(action){
						case ACTION_DOWN:
							return PAD_ButtonsDown(padNumber) & PAD_BUTTON_START;
						break;
						case ACTION_UP:
							return PAD_ButtonsUp(padNumber) & PAD_BUTTON_START;
						break;
						case ACTION_HELD:
							return PAD_ButtonsHeld(padNumber) & PAD_BUTTON_START;
						break;
					}
				break;
			}
		break;

		case BUTTON_KICK:
			switch(_type){
				case INPUT_WII:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_A;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_A;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_A;
						break;
					}
				break;

				case INPUT_WII_SIDE:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_2;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_2;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_2;
						break;
					}
				break;

				case INPUT_GC:
					switch(action){
						case ACTION_DOWN:
							return PAD_ButtonsDown(padNumber) & PAD_BUTTON_X;
						break;
						case ACTION_UP:
							return PAD_ButtonsUp(padNumber) & PAD_BUTTON_X;
						break;
						case ACTION_HELD:
							return PAD_ButtonsHeld(padNumber) & PAD_BUTTON_X;
						break;
					}
				break;
			}
		break;

		case BUTTON_PUNCH:
			switch(_type){
				case INPUT_WII:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_B;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_B;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_B;
						break;
					}
				break;

				case INPUT_WII_SIDE:
					switch(action){
						case ACTION_DOWN:
							return WPAD_ButtonsDown(padNumber) & WPAD_BUTTON_1;
						break;
						case ACTION_UP:
							return WPAD_ButtonsUp(padNumber) & WPAD_BUTTON_1;
						break;
						case ACTION_HELD:
							return WPAD_ButtonsHeld(padNumber) & WPAD_BUTTON_1;
						break;
					}
				break;

				case INPUT_GC:
					switch(action){
						case ACTION_DOWN:
							return PAD_ButtonsDown(padNumber) & PAD_BUTTON_Y;
						break;
						case ACTION_UP:
							return PAD_ButtonsUp(padNumber) & PAD_BUTTON_Y;
						break;
						case ACTION_HELD:
							return PAD_ButtonsHeld(padNumber) & PAD_BUTTON_Y;
						break;
					}
				break;
			}
		break;
	}

	return false;
}

