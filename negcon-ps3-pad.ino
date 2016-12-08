#include <Timer.h>
#include <Event.h>
#include <EEPROM.h>

#include "Source/Public/Config/NCConfigManager.h"
#include "Source/Public/Config/NCModeConfig.h"
#include "Source/Public/Input/NCInputManager.h"
#include "Source/Public/NCPadDriver.h"

//#define DEBUG_PRINT

#define CENTER_OFFSET 2
#define RR64_DEADZONE 30
#define OUTRUN2_DEADZONE 25
#define WOHD_DEADZONE 44
#define REDOUT_DEADZONE 40

NCPadDriver PadDriver;

void setup()
{
	NCConfigManager& ConfigManager = NCConfigManager::Get();

	// PC
	ConfigManager.RegisterModeConfig(
		NCModeConfig(false, false, CENTER_OFFSET, 0, 2.5f, 1.25f),
		EConfigDirection::CD_Up
	);

	// PC - Ridge Racer 64
	ConfigManager.RegisterModeConfig(
		NCModeConfig(false, false, CENTER_OFFSET, RR64_DEADZONE, 2.5f, 1.25f),
		EConfigDirection::CD_Right
	);

	// PC - OutRun 2
	ConfigManager.RegisterModeConfig(
		NCModeConfig(false, false, CENTER_OFFSET, OUTRUN2_DEADZONE, 2.5f, 1.25f),
		EConfigDirection::CD_Right
	);

	// PC - Custom Deadzone
	ConfigManager.RegisterModeConfig(
		NCModeConfig(false, true, CENTER_OFFSET, 0, 2.5f, 1.25f),
		EConfigDirection::CD_Up
	);

	// PS3 - WipEout HD
	ConfigManager.RegisterModeConfig(
		NCModeConfig(true, false, CENTER_OFFSET, WOHD_DEADZONE, 2.5f, 1.25f),
		EConfigDirection::CD_Left
	);

	// Menu Mode
	ConfigManager.RegisterModeConfig(
		NCModeConfig(false, false, CENTER_OFFSET, 0, 0.0f, 1.25f),
		EConfigDirection::CD_Down
	);

	ConfigManager.Initialize();
	PadDriver.Initialize();
}

void loop()
{
	NCInputManager::Get().Update();
	NCConfigManager::Get().Update();
	PadDriver.Update();

#ifdef DEBUG_PRINT
	PadDriver.PrintDebugLog();
#endif //DEBUG_PRINT
}

