#include "../../Public/Config/NCConfigManager.h"

#include "../../Public/EEPROM/EEPROMAnything.h"
#include "../../Public/Input/NCInputManager.h"
#include "../../Public/Teensy/NCPins.h"

#define MODE_EEPROM_OFFSET 2 // The byte offset of the first mode config in EEPROM

NCConfigManager::NCConfigManager() :
	ModeIndex(0),
	ModeDirection(EConfigDirection::CD_Up),
	ModeCount(0),
	ModeSwitched(false)
{

}

NCConfigManager::~NCConfigManager()
{

}

void NCConfigManager::RegisterModeConfig(NCModeConfig Config, EConfigDirection Direction, bool WriteEEPROM /* = false */)
{
	if(WriteEEPROM)
	{
		EEPROM_writeAnything(MODE_EEPROM_OFFSET + (ModeCount * sizeof(NCModeConfig)), Config);
		EEPROM.write(1, ModeCount);
	}

	CrossArray.Insert(ModeCount, Direction);
	++ModeCount;
}

void NCConfigManager::Initialize()
{
	// Restore mode from EEPROM address 0
	ModeIndex = EEPROM.read(0);

	// Restore mode count from EEPROM address 1
	ModeCount = EEPROM.read(1);

	SwitchMode(ModeIndex);
}

void NCConfigManager::Update()
{
	LEDTimer.update();
	CheckModeSwitch();
}

bool NCConfigManager::IsModeSwitchActive()
{
	return NCInputManager::Get().GetPadState().Start();
}

void NCConfigManager::SwitchMode(uint8_t ModeIndex)
{
	EEPROM_readAnything(MODE_EEPROM_OFFSET + (ModeIndex * sizeof(NCModeConfig)), ModeConfig);
}

void NCConfigManager::CheckModeSwitch()
{
	NCPadState& PadState = NCInputManager::Get().GetPadState();

	uint8_t CrossArrayIndex = 0;

	if(IsModeSwitchActive() && !ModeSwitched)
	{
		EConfigDirection NewDirection = CD_Invalid;
		switch(PadState.DPadAngle())
		{
			case EDPadDirection::DPD_Up:
				NewDirection = CD_Up;
				break;
			case EDPadDirection::DPD_Down:
				NewDirection = CD_Down;
				break;
			case EDPadDirection::DPD_Left:
				NewDirection = CD_Left;
				break;
			case EDPadDirection::DPD_Right:
				NewDirection = CD_Right;
				break;
			default:
				break;
		}

		if(NewDirection != CD_Invalid)
		{
			if(NewDirection == ModeDirection)
			{
				++ModeIndex;
				if(ModeIndex > CrossArray.GetCount(ModeDirection) - 1)
				{
					ModeIndex = 0;
				}
				ModeSwitched = true;
			}
			else
			{
				ModeDirection = NewDirection;
				ModeIndex = 0;
				ModeSwitched = true;
			}
		}

		if(ModeSwitched)
		{
			CrossArrayIndex = CrossArray.Get(ModeIndex, ModeDirection);

			Serial.print("Mode Switch: ");
			Serial.print(CrossArrayIndex);
			Serial.println();
			Serial.println();

			// Read mode config from EEPROM
			SwitchMode(CrossArrayIndex);

			// Write mode to EEPROM address 0
			EEPROM.write(0, ModeIndex);

			// Flash LED
			LEDTimer.oscillate(LED_PIN, 100, LOW, CrossArrayIndex + 1);
		}
	}

	// Store current twist value as a temporary inverse deadzone on switch
	if(ModeSwitched && ModeConfig.CustomInverseDeadzone == 1)
	{
		ModeConfig.InverseDeadzone = abs(128 - PadState.AxisTwist) * 2;
	}

	if(PadState.DPadAngle() == EDPadDirection::DPD_Center)
	{
		ModeSwitched = false;
	}
}