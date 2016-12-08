#include "../Public/NCPadDriver.h"

#include "../Public/EEPROM/EEPROMAnything.h"
#include "../Public/Input/NCInputManager.h"
#include "../Public/Config/NCConfigManager.h"
#include "../Public/Serial/NCSerial.h"
#include "../Public/Teensy/NCPins.h"

#define MODE_EEPROM_OFFSET 2 // The byte offset of the first mode config in EEPROM

void NCPadDriver::Initialize()
{
	// Setup PSX serial pins
	SetupPins(DAT_PIN, CMD_PIN, ATT_PIN, CLK_PIN);

	// Establishes LED pin as an output so the LED can be seen
	pinMode(LED_PIN, OUTPUT);

	// Set the Joystick API to send manually
	Joystick.useManualSend(1);

	Serial.begin(9600);
}

void NCPadDriver::Update()
{
	NCPadState& PadState = NCInputManager::Get().GetPadState();
	NCModeConfig& ModeConfig = NCConfigManager::Get().GetModeConfig();

	if(ModeConfig.CenterOffset != 0)
	{
		ApplyCenterOffset(PadState, ModeConfig.CenterOffset);
	}

	if(ModeConfig.TwistSensitivity != 1.0f)
	{
		ApplyTwistSensitivity(PadState, ModeConfig.TwistSensitivity);
	}

	// Linear map to remove deadzone
	if(ModeConfig.InverseDeadzone > 0)
	{
		ApplyInverseDeadzone(PadState, ModeConfig.InverseDeadzone);
	}

	if(ModeConfig.ButtonSensitivity != 1.0f)
	{
		ApplyButtonSensitivity(PadState, ModeConfig.ButtonSensitivity);
	}

	SendJoystickState(PadState);
}

void NCPadDriver::SetupPins(byte DataPin, byte CommandPin, byte AttentionPin, byte ClockPin)
{
	pinMode(DataPin, INPUT);
	digitalWrite(DataPin, HIGH);	// Turn on internal pull-up

	pinMode(CommandPin, OUTPUT);

	pinMode(AttentionPin, OUTPUT);
	digitalWrite(AttentionPin, HIGH);

	pinMode(ClockPin, OUTPUT);
	digitalWrite(ClockPin, HIGH);
}

void NCPadDriver::ApplyCenterOffset(NCPadState& PadState, const int8_t CenterOffset)
{
	// Apply center point correction
	if(PadState.AxisTwist + CenterOffset > 255)
	{
		PadState.AxisTwist = 255;
	}
	else if(PadState.AxisTwist + CenterOffset < 0)
	{
		PadState.AxisTwist = 0;
	}
	else
	{
		PadState.AxisTwist += CenterOffset;
	}
}

void NCPadDriver::ApplyTwistSensitivity(NCPadState& PadState, const float TwistSensitivity)
{
	int Temp = PadState.AxisTwist - 127;
	Temp *= TwistSensitivity;
	if(Temp > 127)
	{
		Temp = 255;
	}
	else if(Temp < -127)
	{
		Temp = 0;
	}
	else
	{
		Temp += 127;
	}
	PadState.AxisTwist = Temp;
}

void NCPadDriver::ApplyInverseDeadzone(NCPadState& PadState, const uint8_t InverseDeadzone)
{
	int Sign = 0;
	int AxisOffset = PadState.AxisTwist - 127;
	if(AxisOffset > 0) Sign = 1;
	else if(AxisOffset < 0) Sign = -1;
	if(Sign != 0)
	{
		PadState.AxisTwist = map(AxisOffset, 0, Sign * 127, Sign * InverseDeadzone, Sign * 127) + 127;
	}
}

void NCPadDriver::ApplyButtonSensitivity(NCPadState& PadState, const float ButtonSensitivity)
{
	PadState.AxisI = constrain(PadState.AxisI * ButtonSensitivity, 0, 255);
	PadState.AxisII = constrain(PadState.AxisII * ButtonSensitivity, 0, 255);
}

void NCPadDriver::SendJoystickState(NCPadState& PadState)
{
	NCModeConfig& ModeConfig = NCConfigManager::Get().GetModeConfig();

	// Set data in Joystick
	Joystick.X(PadState.AxisTwist * 4);

	if(ModeConfig.PS3Mapping == 0)
	{
		Joystick.Y(PadState.AxisL * 4);
		Joystick.Z(PadState.AxisI * 4);
		Joystick.Zrotate(PadState.AxisII * 4);
	}
	else
	{
		Joystick.Y(512);
		Joystick.Z(512);
		Joystick.Zrotate(512);
	}

	Joystick.hat(PadState.DPadAngle());

	if(ModeConfig.PS3Mapping == 0)
	{
		Joystick.button(1, 0); // Square
		Joystick.button(2, 0); // X
		Joystick.button(3, PadState.A()); // Circle
		Joystick.button(4, PadState.B()); // Triangle
		Joystick.button(5, PadState.L()); // L1
		Joystick.button(6, PadState.R()); // R1
		Joystick.button(7, 0); // L2
		Joystick.button(8, 0); // R2
		Joystick.button(9, 0); // Select
		Joystick.button(10, PadState.Start()); // Start
		Joystick.button(11, 0); // L3
		Joystick.button(12, 0); // R3
		Joystick.button(13, 0); // PS Button
	}
	else
	{
		Joystick.button(1, PadState.II()); // Square
		Joystick.button(2, PadState.I()); // X
		Joystick.button(3, PadState.A()); // Circle
		Joystick.button(4, PadState.B()); // Triangle
		Joystick.button(5, PadState.L()); // L1
		Joystick.button(6, PadState.R()); // R1
		Joystick.button(7, 0); // L2
		Joystick.button(8, 0); // R2
		Joystick.button(9, 0); // Select
		Joystick.button(10, PadState.Start()); // Start
		Joystick.button(11, 0); // L3
		Joystick.button(12, 0); // R3
		Joystick.button(13, PadState.L() && PadState.R() && PadState.Start()); // PS Button
	}

	Joystick.send_now();
}

void NCPadDriver::PrintDebugLog()
{
	NCPadState& PadState = NCInputManager::Get().GetPadState();
	NCModeConfig& ModeConfig = NCConfigManager::Get().GetModeConfig();

	Serial.print("Mode Index:\t");
	Serial.print(EEPROM.read(0));
	Serial.print("\t");

	Serial.print("Mode Count:\t");
	Serial.print(EEPROM.read(1));
	Serial.print("\t");

	Serial.print("Mode:\t\t");

	const byte* p = (const byte*)(const void*)&ModeConfig;
	unsigned int i;
	for(i = 0; i < sizeof(ModeConfig); i++)
	{
		if(i == 0)
		{
			for(unsigned int o = 0; o < 8; ++o)
			{
				Serial.print((*p >> o) & 0x01);
			}
			++p;
			Serial.print(" ");
		}
		else
		{
			Serial.print(*p++);
			Serial.print(" ");
		}
	}
	Serial.println();

	Serial.print("Buttons 1:\t");
	for(unsigned int mask = 0x80; mask; mask >>= 1)
	{
		Serial.print(mask & PadState.Buttons1 ? '1' : '0');
	}
	Serial.print("\tButtons 2:\t");
	for(unsigned int mask = 0x80; mask; mask >>= 1)
	{
		Serial.print(mask & PadState.Buttons2 ? '1' : '0');
	}
	Serial.print("\tDPad:\t");
	Serial.print((PadState.Buttons1 >> 4), HEX);
	Serial.print("\tTwist:\t");
	Serial.print(PadState.AxisTwist);
	Serial.print("\tI:\t");
	Serial.print(PadState.AxisI);
	Serial.print("\tII:\t");
	Serial.print(PadState.AxisII);
	Serial.print("\tL:\t");
	Serial.print(PadState.AxisL);
	Serial.println();
}
