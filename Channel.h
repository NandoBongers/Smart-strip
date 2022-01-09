// Channel.h

#ifndef _CHANNEL_h
#define _CHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


#include "Ir_Signal.h"
#include <SoftwareSerial.h>
#include "Master_Signal.h"
class Channel
{
public:
	Channel(const char on, const char off, SoftwareSerial* pbt_Serial, String file_Name_Signal_A, String file_Name_Signal_B, String file_Name_Channel_Data, String file_Name_Master_Signal);
	String file_Name_A;
	String file_Name_B;
	String file_Name_Data;
	byte signal_Length_A;
	byte signal_Length_B;
	Master_Signal master_signal;
	void turn_On();
	void turn_Off();
	void turn_On_Off();

private:
	char _on;
	char _off;
	SoftwareSerial* _pbt_Serial;
	bool _state;
};

#endif

