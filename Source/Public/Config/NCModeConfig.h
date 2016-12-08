#ifndef NCMODECONFIG_H
#define NCMODECONFIG_H

#include <Arduino.h>

struct NCModeConfig
{
	NCModeConfig();
	NCModeConfig(bool PS3Mapping, bool CustomInverseDeadzone, int8_t CenterOffset, uint8_t InverseDeadzone, float TwistSensitivity, float ButtonSensitivity);

	uint8_t PS3Mapping : 1; // 0 = PC, 1 = PS3
	uint8_t CustomInverseDeadzone : 1;
	uint8_t : 6;

	int8_t CenterOffset;
	uint8_t InverseDeadzone;
	float TwistSensitivity;
	float ButtonSensitivity;
};

#endif // NCMODECONFIG_H
