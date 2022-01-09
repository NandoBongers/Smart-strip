#include "SD_Card.h"
#include "Ir_Signal.h"
#include "Ir_Decoder.h"
#include "Input.h"
#include "Channel.h"
#include "Button.h"
#include "Display.h"
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
File file;
SD_Card sd_Card(4);
Display display(&lcd, 5, &file, 3);


Button toggle(7);
Button select(8);

Input input(6);
SoftwareSerial bt_Serial(10, 9);

Channel channel_1('1', '2', &bt_Serial, "1A", "1B", "D1", "M1");
Channel channel_2('3', '4', &bt_Serial, "2A", "2B", "D2", "M2");
Channel channel_3('5', '6', &bt_Serial, "3A", "3B", "D3", "M3");
Ir_Decoder ir_Decoder;


void setup()
{  
	display.power_On();

	if (!SD.begin(sd_Card.csPin))
	{
		return;
	}

	Serial.begin(9600);
	bt_Serial.begin(38400);
	display.init();
	display.print();
	display.backlight();
	display.setBrightness(display.brightness);

	sd_Card.get_Channel_Data(&channel_1, &file);
	sd_Card.get_Channel_Data(&channel_2, &file);
	sd_Card.get_Channel_Data(&channel_3, &file);
}

void loop()
{  
		while (input.not_Available())
		{
			if (display.timer() > 15000)
			{
				sleepMode();
			}

			if (toggle.is_Pressed())
			{
				display.resetTimer();
				display.menuToggle();
			}

			if (select.is_Pressed())
			{
				display.resetTimer();
				display.menuSelect();
			}

			switch (display.menu)
			{
			case 60:
				program(&channel_1);
				break;
			case 61:
				program(&channel_2);
				break;
			case 62:
				program(&channel_3);
				break;
			default:
				break;
			}
			while (sd_Card.timer() > 1000)
			{
				SD.begin(sd_Card.csPin);
				sd_Card.resetTimer();
			}
		}
		ir_Decoder.read(&input);
		checkSignal(&channel_1);
		checkSignal(&channel_2);
		checkSignal(&channel_3);
		delay(200);
}


void checkSignal(Channel* pchannel)
{
	if (ir_Decoder.compare(&input.input_Signal, &pchannel->signal_Length_A, &pchannel->file_Name_A, &file))
	{
		pchannel->turn_On_Off();
	}
	else if(ir_Decoder.compare(&input.input_Signal, &pchannel->signal_Length_B, &pchannel->file_Name_B, &file))
	{
		pchannel->turn_On_Off();
	}
	else if (ir_Decoder.compare(&input.input_Signal, &pchannel->master_signal.signal_Length, &pchannel->master_signal.file_Name, &file))
	{
		pchannel->turn_On_Off();
	}
}



void sleepMode()
{
	display.fadeOut();
	display.power_Off();
	while (select.is_Not_Pressed() && toggle.is_Not_Pressed()) //Wait for a button to be pressed
	{
		
		while (sd_Card.timer() > 1000)
		{
			SD.begin(sd_Card.csPin);
			sd_Card.resetTimer();
		}
		
		if (input.is_Available())
		{
			ir_Decoder.read(&input);
			checkSignal(&channel_1);
			checkSignal(&channel_2);
			checkSignal(&channel_3);
			delay(200);
		}

		if (display.timer() > 30000)
		{
			display.menu = 10;
		}

	}
	
	display.resetTimer();
	display.power_On();
	display.init();
	display.print();
	display.setBrightness(display.brightness);
	delay(200);
}



void program(Channel* pchannel)
{
	bool programming_Mode = true;
	bool realSignal = false;
	delay(200);

	while (!realSignal && programming_Mode)
	{
		while ((input.not_Available()) && (programming_Mode == true))
		{
			if (select.is_Pressed() || toggle.is_Pressed())
			{
				programming_Mode = false;//Exit programming mode
				display.menuToggle();
			}
		}

		if (programming_Mode)
		{
			ir_Decoder.read(&input);
			if (input.input_Signal.length > 10)
			{
				sd_Card.store_Signal(&input.input_Signal, &file, &pchannel->file_Name_A);
				pchannel->signal_Length_A = input.input_Signal.length;
				realSignal = true;
				display.menuRemote();
			}

			input.clear();
			delay(100); // For ignoring any double signals 
			
		}
	}

	
	realSignal = false;
	
	
	while (!realSignal && programming_Mode)
	{
		while ((input.not_Available()) && (programming_Mode == true))
		{
			if (select.is_Pressed() || toggle.is_Pressed())
			{
				programming_Mode = false;//Exit programming mode
			}
		}

		if (programming_Mode)
		{
			ir_Decoder.read(&input);
			if (input.input_Signal.length > 10)
			{
				sd_Card.store_Signal(&input.input_Signal, &file, &pchannel->file_Name_B);
				pchannel->signal_Length_B = input.input_Signal.length;
				realSignal = true;
				
				sd_Card.store_Channel_Data(&pchannel->file_Name_Data, &pchannel->signal_Length_A, &pchannel->signal_Length_B, &file);
				display.menuRemote();
			}
			input.clear();
			
		}
	}
}


