// 
// 
// 

#include "SD_Card.h"

SD_Card::SD_Card(byte Pin)
{
	csPin = Pin;
	pinMode(csPin, OUTPUT);

}

void SD_Card::store_Signal(Ir_Signal* signal, File* pmyFile, String* file_Name)
{
	if (SD.exists(*file_Name))
	{
		SD.remove(*file_Name);
	}

	*pmyFile = SD.open(*file_Name, FILE_WRITE);
	if (*pmyFile)
	{
		for (byte i = 0; i < signal->length; i++)
		{
			pmyFile->println(signal->signal[i]);
		}
		pmyFile->close();
	}
}


void SD_Card::store_Channel_Data(String* file_Name_Channel_Data, byte* signal_A_Length, byte* signal_B_Length, File* pmyFile)
{
	if (SD.exists(*file_Name_Channel_Data))
	{
		SD.remove(*file_Name_Channel_Data);
	}

	*pmyFile = SD.open(*file_Name_Channel_Data, FILE_WRITE);
	if (*pmyFile)
	{
		pmyFile->println(*signal_A_Length);
		pmyFile->println(*signal_B_Length);

		pmyFile->close();
	}
}

void SD_Card::get_Channel_Data(Channel* pchannel, File* pmyFile)
{
	if (SD.exists(pchannel->file_Name_Data))
	{
		*pmyFile = SD.open(pchannel->file_Name_Data);

		if (*pmyFile)
		{
			pchannel->signal_Length_A = (pmyFile->readStringUntil('\n')).toInt();
			pchannel->signal_Length_B = (pmyFile->readStringUntil('\n')).toInt();

			pmyFile->close();
		}
		else
		{
			pchannel->signal_Length_A = 0;
			pchannel->signal_Length_B = 0;
		}
	}
}

int SD_Card::timer()
{
	int time = 0;
	if (_firstTime)
	{
		_counter_A = millis();
		_firstTime = LOW;
	}

	_counter_B = millis();
	time = _counter_B - _counter_A;
	return time;
}

void SD_Card::resetTimer()
{
	_firstTime = true;
}