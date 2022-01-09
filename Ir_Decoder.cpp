// 
// 
// 

#include "Ir_Decoder.h"

Ir_Decoder::Ir_Decoder(short int const release_Time = 10000, byte const deviation = 25)
{
	_release_Time = release_Time;
	_deviation = deviation;
}


void Ir_Decoder::read(Input* pinput)
{
	//Input input = *pinput;
	bool signal_Receiving = true;//Keeps reading, calculating and storing data as long as this value stays true;
	unsigned long int begin_Time = 0;//Time when counting starts.
	unsigned long int end_Time = 0;//Time when counting stops.
	short int duration;//Difference between beginTim and endTime.
	short int counter = 0;//This counter increases the index of the received_Signal[] array.
	_pin = pinput->getPin();

	while (logic_Low()) // Wait for the first pulse.
	{
	}

	while (signal_Receiving)//Stores the value of the time between each pulse in received_Signal[] as long as an ir signal is being received.
	{
		begin_Time = micros(); //Signal is high, start counting.
		while (logic_High())//Waits for the signal to get low. 
		{
			end_Time = micros();
			if ((end_Time - begin_Time)> _release_Time)//If the signal is high for too long, we assume that all data is received. 
			{
				signal_Receiving = false;//Stop storing data.
				pinput->input_Signal.length = counter;
				break;
			}
		}
		end_Time = micros();//Signal is low, stop counting.

		if (signal_Receiving)//Calculates the time that the signal was high, stores it in received_Signal[] and increases the index of the received_Signal[] array.
		{
			duration = end_Time - begin_Time;//Calculates the time that the signal was high.
			pinput->input_Signal.signal[counter] = duration;//Stores the time that the signal was high in received_Signal[].
			counter++;//Increase the index of the received_Signal[] array.
		}
		begin_Time = micros();//Signal is low, start counting.

		while (logic_Low())//Waits for the signal to get high. 
		{
		}
		end_Time = micros();//Signal is high, stop counting.

		if (signal_Receiving)//Calculates the time that the signal was low, stores it and increases the index of the received_Signal[] array.
		{
			duration = end_Time - begin_Time;//Calculates the time that the signal was low.
			pinput->input_Signal.signal[counter] = duration;//Stores the time that the signal was low in received_Signal[].
			counter++;//Increase the index of the received_Signal[] array.  
		}
	}
}

bool Ir_Decoder::compare(Ir_Signal* input, byte* channel_Signal_Length, String* channel_File_Name, File* pmyFile)
{
	bool signals_Are_Equal = true;
	short int channel_Signal;

	if (input->length != *channel_Signal_Length)
	{
		signals_Are_Equal = false;
	}
	else
	{
		*pmyFile = SD.open(*channel_File_Name);
		if (*pmyFile)
		{
			for (byte i = 0; i < input->length; i++) //Checks if the received data is the same as the data that is assigned to chanel 1.
			{
				channel_Signal = (pmyFile->readStringUntil('\n')).toInt();
				short int min_Dev = input->signal[i] - ((input->signal[i] / 100)*_deviation); //Calculates the minimum value of the time between each pulse.
				short int max_Dev = input->signal[i] + ((input->signal[i] / 100)*_deviation); //Calculates the maximal value of the time between each pulse.

				if (channel_Signal<min_Dev || channel_Signal>max_Dev) //The signal is the same as the signal asigned to channel 1 as long as the time between each pulse is beween minimal and maximal.  
				{
					signals_Are_Equal = false; //The signal is NOT the same as the signal asigned to channel 1
					break;
				}
				else
				{
				}
			}
			pmyFile->close();
		}
		else
		{
			signals_Are_Equal = false;
		}
	}
	return signals_Are_Equal;
}
bool Ir_Decoder::logic_Low()
{
	if (digitalRead(_pin) == LOW)
		return true;
	else
		return false;
}

bool Ir_Decoder::logic_High()
{
	if (digitalRead(_pin) == HIGH)
		return true;
	else
		return false;
}