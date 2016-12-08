#ifndef NCCROSSARRAY_H
#define NCCROSSARRAY_H

#include <Arduino.h>
#include "../Enums/NCEnums.h"

class NCCrossArray
{
public:
	NCCrossArray();

	uint8_t GetCount(EConfigDirection Direction);
	uint8_t Get(uint8_t Index, EConfigDirection Direction);
	void Insert(uint8_t Value, EConfigDirection Direction);

private:
	uint8_t Up[4];
	uint8_t Down[4];
	uint8_t Left[4];
	uint8_t Right[4];

	uint8_t UpCount;
	uint8_t DownCount;
	uint8_t LeftCount;
	uint8_t RightCount;
};

#endif // NCCROSSARRAY_H
