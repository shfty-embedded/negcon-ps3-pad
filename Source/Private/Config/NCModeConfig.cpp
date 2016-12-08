#include "../../Public/Config/NCModeConfig.h"

NCModeConfig::NCModeConfig() :
	PS3Mapping(false),
	CustomInverseDeadzone(false),
	CenterOffset(0),
	InverseDeadzone(0),
	TwistSensitivity(1.0f),
	ButtonSensitivity(1.0f)
{
}

NCModeConfig::NCModeConfig(bool PS3Mapping, bool CustomInverseDeadzone, int8_t CenterOffset, uint8_t InverseDeadzone, float TwistSensitivity, float ButtonSensitivity) :
	PS3Mapping(PS3Mapping),
	CustomInverseDeadzone(CustomInverseDeadzone),
	CenterOffset(CenterOffset),
	InverseDeadzone(InverseDeadzone),
	TwistSensitivity(TwistSensitivity),
	ButtonSensitivity(ButtonSensitivity)
{
}
