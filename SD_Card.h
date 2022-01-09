// SD_Card.h

#ifndef _SD_CARD_h
#define _SD_CARD_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"

#else
#include "WProgram.h"
#endif
#include "Ir_Signal.h"
#include <SD.h>
#include <SPI.h>
#include "Channel.h"
class SD_Card
{
public:
	SD_Card(const byte Pin);
	void store_Signal(Ir_Signal* signal, File* pmyFile, String* file_Name);
	byte csPin;
	void store_Channel_Data(String* file_Name_Channel_Data, byte* signal_A_Length, byte* signal_B_Length, File* pmyFile);
	void get_Channel_Data(Channel* pchannel, File* pmyFile);
	int timer();
	void resetTimer();

private:
	unsigned long _counter_A;
	unsigned long _counter_B;
	bool _firstTime = true;
};

#endif
