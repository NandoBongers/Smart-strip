// Input.h

#ifndef _INPUT_h
#define _INPUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
	#include "Ir_Signal.h"
#else
	#include "WProgram.h"
#endif
class Input
{
public:
	Input(byte const pin);
	bool not_Available();
	bool is_Available();
	byte getPin();
	void clear();

	Ir_Signal input_Signal;
private:
	byte _pin;
	bool _state;
};

#endif

