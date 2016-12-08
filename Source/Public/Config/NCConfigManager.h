#ifndef NCCONFIGMANAGER_H
#define NCCONFIGMANAGER_H

struct NCPadState;

#include <Arduino.h>
#include <Timer.h>

#include "NCModeConfig.h"
#include "../../Public/Storage/NCCrossArray.h"
#include "../../Public/Enums/NCEnums.h"

class NCConfigManager
{
public:
	static NCConfigManager& Get()
	{
		static NCConfigManager Instance;
		return Instance;
	}

	void RegisterModeConfig(NCModeConfig Config, EConfigDirection Direction, bool WriteEEPROM = false);
	void Initialize();
	void Update();

	bool IsModeSwitchActive();

	NCModeConfig& GetModeConfig() { return ModeConfig; }

protected:
	NCConfigManager();
	NCConfigManager(const NCConfigManager&);
	NCConfigManager& operator=(const NCConfigManager&);
	~NCConfigManager();

private:
	void SwitchMode(uint8_t ModeIndex);
	void CheckModeSwitch();

private:
	NCModeConfig ModeConfig;
	NCCrossArray CrossArray;

	Timer LEDTimer;

	int8_t ModeIndex;
	EConfigDirection ModeDirection;
	int8_t ModeCount;
	bool ModeSwitched;
};

#endif // NCCONFIGMANAGER_H
