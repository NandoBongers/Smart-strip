// 
// 
// 

#include "Display.h"


Display::Display(LiquidCrystal_I2C* lcd, const int backlightPin, File* file, byte power_Pin)
{
	_backlightPin = backlightPin;
	pinMode(_backlightPin, OUTPUT);
	_plcd = lcd;
	pmyFile = file;
	_power_Pin = power_Pin;

	pinMode(_power_Pin, OUTPUT);
}


void Display::backlight()
{
	_plcd->backlight();
}

void Display::init()
{
	_plcd->init();
}

void Display::fadeOut()
{
	short int i = brightness;
	for (i; i >= 0; i--)
	{
		setBrightness(i);
		delay(10);
	}
}

void Display::menuToggle()
{
	switch (menu) {
	case 10:
		menu = 20;
		break;
	case 20:
		menu = 21;
		break;
	case 21:
		menu = 20;
		break;
	case 22:
		//empty
		break;
	case 30:
		menu = 31;
		break;
	case 31:
		menu = 32;
		break;
	case 32:
		menu = 35;
		break;
	case 35:
		menu = 30;
		break;
	case 40:
		menu = 41;
		break;
	case 41:
		menu = 40;
		break;	
	case 50:
		menu = 51;
		break;
	case 51:
		menu = 52;
		break;
	case 52:
		menu = 50;
		break;
	case 60:
		menu = 20;
		break;
	case 61:
		menu = 20;
		break;
	case 62:
		menu = 20;
		break;
	case 70:
		menu = 20;
		break;
	case 71:
		menu = 20;
		break;
	default:
		menu = 20;
	}
	print();
	delay(200);
}

void Display::menuSelect()
{
	switch (menu) {
	case 10:
		menu = 20;
		break;
	case 20:
		menu = 30;
		break;
	case 21:
		menu = 40;
		break;
	case 22:
		break;
	case 30:
		menu = 60;
		break;
	case 31:
		menu = 61;
		break;
	case 32:
		menu = 62;
		break;
	case 35:
		menu = 20;
		break;
	case 40:
		menu = 50;
		break;
	case 41:
		menu = 21;
		break;
	case 50:
		brightness += 25;
		if (brightness > 250) brightness = 250;
		setBrightness(brightness);
		break;
	case 51:
		brightness -= 25;
		if (brightness < 5) brightness = 5;
		setBrightness(brightness);
		break;
	case 52:
		menu = 40;
		break;
	case 60:
		menu = 20;
		break;
	case 61:
		menu = 20;
		break;
	case 62:
		menu = 20;
		break;
	case 70:
		menu = 20;
		break;
	case 71:
		menu = 20;
		break;
	default:
		menu = 22;
	}
	print();
	delay(200);
}

void Display::menuRemote()
{
	switch (menu)
	{
	case 60:
		menu = 70;
		break;
	case 61:
		menu = 70;
		break;
	case 62:
		menu = 70;
		break;
	case 70:
		menu = 71;
		print();
		delay(2000);
		menu = 20;
		break;
	default:
		break;
	}
	print();
	delay(200);
}
void Display::setBrightness(short int brightness)
{
	analogWrite(_backlightPin, brightness);
}

void Display::print()
{
	switch (menu)
	{
	case 10:
		*pmyFile = SD.open("10");
		break;
	case 20:
		*pmyFile = SD.open("20");
		break;
	case 21:
		*pmyFile = SD.open("21");
		break;
	case 22:
		*pmyFile = SD.open("22");		
		break;
	case 30:
		*pmyFile = SD.open("30");
		break;
	case 31:
		*pmyFile = SD.open("31");
		break;
	case 32:
		*pmyFile = SD.open("32");
		break;
	case 35:
		*pmyFile = SD.open("35");
		break;
	case 40:
		*pmyFile = SD.open("40");
		break;
	case 41:
		*pmyFile = SD.open("41");
		break;
	case 50:
		*pmyFile = SD.open("50");
		break;
	case 51:
		*pmyFile = SD.open("51");
		break;
	case 52:
		*pmyFile = SD.open("52");
		break;
	case 60:
		*pmyFile = SD.open("60");
		break;
	case 61:
		*pmyFile = SD.open("60");
		break;
	case 62:
		*pmyFile = SD.open("60");
		break;
	case 70:
		*pmyFile = SD.open("70");
		break;
	case 71:
		*pmyFile = SD.open("71");
		break;
	default:
		break;
	}


	if (*pmyFile)
	{
		if (pmyFile->available())
		{
			_plcd->setCursor(0, 0);
			_plcd->print(pmyFile->readStringUntil('\n'));
			_plcd->setCursor(0, 1);
			_plcd->print(pmyFile->readStringUntil('\n'));
		}
	}
	pmyFile->close();
}

int Display::timer()
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

void Display::resetTimer()
{
	_firstTime = true;
}

void Display::power_On()
{
	digitalWrite(_power_Pin, HIGH);
}

void Display::power_Off()
{
	digitalWrite(_power_Pin, LOW);
}