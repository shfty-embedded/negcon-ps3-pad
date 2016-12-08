#ifndef NCPADDRIVER_H
#define NCPADDRIVER_H

#include "Config/NCModeConfig.h"
#include "Input/NCPadState.h"

class NCPadDriver
{
public:
	void Initialize();
	void Update();
	void PrintDebugLog();

private:
	void SetupPins(byte dataPin, byte cmndPin, byte attPin, byte clockPin);
	void ApplyCenterOffset(NCPadState& PadState, const int8_t CenterOffset);
	void ApplyTwistSensitivity(NCPadState& PadState, const float TwistSensitivity);
	void ApplyInverseDeadzone(NCPadState& PadState, const uint8_t InverseDeadzone);
	void ApplyButtonSensitivity(NCPadState& PadState, const float ButtonSensitivity);
	void SendJoystickState(NCPadState& PadState);
};

#endif //NCPADDRIVER_H
