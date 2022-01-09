// Master_Signal.h

#ifndef _MASTER_SIGNAL_h
#define _MASTER_SIGNAL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
struct Master_Signal
{
	String file_Name;
	byte signal_Length = 66;
};

#endif

