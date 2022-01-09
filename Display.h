// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"

#else
#include "WProgram.h"
#endif
#include "Display.h"
#include "SD_Card.h"
#include <LiquidCrystal_I2C.h>




class Display
{
public:
	Display(LiquidCrystal_I2C* lcd, const int backlightPin, File* file, byte power_Pin);

	void backlight();
	void print();
	void init();
	void fadeOut();
	void menuToggle();
	void menuSelect();
	void menuRemote();
	void setBrightness(short int brightness);
	int timer();
	void resetTimer();
	short int brightness = 75;
	byte menu = 10;
	File* pmyFile;
	void power_On();
	void power_Off();

private:
	byte _backlightPin;
	unsigned long _counter_A;
	unsigned long _counter_B;
	bool _firstTime = true;
	LiquidCrystal_I2C* _plcd;
	byte _power_Pin;

};

#endif
