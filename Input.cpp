// 
// 
// 

#include "Input.h"

Input::Input(byte const pin)
{
	_pin = pin;
	pinMode(_pin, INPUT);
}

bool Input::not_Available()
{
	_state = digitalRead(_pin);
	return _state;
}

bool Input::is_Available()
{
	return !not_Available();
}

byte Input::getPin()
{
	return _pin;
}

void Input::clear()
{
	for (byte i = 0; i<input_Signal.length; i++)
	{
		input_Signal.signal[i] = 0;
	}
	input_Signal.length = 0;
}