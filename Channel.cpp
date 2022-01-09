// 
// 
// 
#include "Channel.h"



Channel::Channel(const char on, const char off, SoftwareSerial* pbt_Serial, String file_Name_Signal_A, String file_Name_Signal_B, String file_Name_Channel_Data, String file_Name_Master_Signal)
{
	_on = on;
	_off = off;
	_pbt_Serial = pbt_Serial;
	file_Name_A = file_Name_Signal_A;
	file_Name_B = file_Name_Signal_B;
	file_Name_Data = file_Name_Channel_Data;
	master_signal.file_Name = file_Name_Master_Signal;
}


void Channel::turn_On()
{
	_pbt_Serial->write(_on);
	_state = HIGH;
}

void Channel::turn_Off()
{
	_pbt_Serial->write(_off);
	_state = LOW;
}

void Channel::turn_On_Off()
{
	if (_state)
		turn_Off();
	else
		turn_On();
}

