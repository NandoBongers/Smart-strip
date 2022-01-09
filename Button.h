// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Button
{
public:
	Button(byte const pin);
	bool is_Pressed();
	bool is_Not_Pressed();

private:
	byte _pin;
	bool _state;
};

#endif

