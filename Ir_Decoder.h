// Ir_Decoder.h

#ifndef _IR_DECODER_h
#define _IR_DECODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
	#include "Ir_Signal.h"
	#include "Input.h"
	#include "SD_Card.h"
#else
	#include "WProgram.h"
#endif
class Ir_Decoder
{
public:
	Ir_Decoder(short int const release_Time = 10000, byte const deviation = 25);
	void read(Input* pinput);
	bool compare(Ir_Signal* input, byte* channel_Signal_Length, String* channel_File_Name, File* pmyFile);
	bool logic_Low();
	bool logic_High();


private:
	byte _pin;
	short int _release_Time;
	byte _deviation;
};

#endif

