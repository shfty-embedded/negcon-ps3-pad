#include "../../Public/Serial/NCSerial.h"

#include "../../Public/Teensy/NCPins.h"

// Delay (in microseconds) between clock pulses
#define SERIAL_DELAY 20

// Does the actual shifting, both in and out simultaneously
byte NCSerial::Shift(byte DataOut)
{
	bool Temp = 0;
	byte DataIn = 0;

	for(byte i = 0; i <= 7; i++)
	{
		if(DataOut & (1 << i))
		{
			// Writes out the _dataOut bits
			digitalWrite(CMD_PIN, HIGH);
		}
		else
		{
			digitalWrite(CMD_PIN, LOW);
		}

		digitalWrite(CLK_PIN, LOW);
		delayMicroseconds(SERIAL_DELAY);

		// Reads the data pin
		Temp = digitalRead(DAT_PIN);
		if(Temp)
		{
			// Shifts the read data into dataIn
			DataIn = DataIn | (B00000001 << i);
		}

		digitalWrite(CLK_PIN, HIGH);
		delayMicroseconds(SERIAL_DELAY);
	}

	return DataIn;
}
