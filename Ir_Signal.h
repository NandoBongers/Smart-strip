// Ir_Signal.h

#ifndef _IR_SIGNAL_h
#define _IR_SIGNAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

struct Ir_Signal
{
	short int signal[67];
	byte length;
};

#endif


