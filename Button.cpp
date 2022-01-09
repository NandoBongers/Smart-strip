// 
// 
// 

#include "Button.h"

Button::Button(byte const pin)
{
	_pin = pin;
	pinMode(_pin, INPUT);
}

bool Button::is_Pressed()
{
	_state = digitalRead(_pin);
	return(_state);
}

bool Button::is_Not_Pressed()
{
	return !is_Pressed();
}