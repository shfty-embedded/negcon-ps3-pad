#include "../../Public/Storage/NCCrossArray.h"

NCCrossArray::NCCrossArray() :
	UpCount(0),
	DownCount(0),
	LeftCount(0),
	RightCount(0)
{
}

uint8_t NCCrossArray::GetCount(EConfigDirection Direction)
{
	switch(Direction)
	{
		case EConfigDirection::CD_Up:
			return UpCount;
			break;
		case EConfigDirection::CD_Down:
			return DownCount;
			break;
		case EConfigDirection::CD_Left:
			return LeftCount;
			break;
		case EConfigDirection::CD_Right:
			return RightCount;
			break;
		default:
			break;
	}

	return -1;
}

uint8_t NCCrossArray::Get(uint8_t Index, EConfigDirection Direction)
{
	uint8_t* DirectionArray = nullptr;
	uint8_t DirectionCount = 0;

	switch(Direction)
	{
		case EConfigDirection::CD_Up:
			DirectionArray = Up;
			DirectionCount = UpCount;
			break;
		case EConfigDirection::CD_Down:
			DirectionArray = Down;
			DirectionCount = DownCount;
			break;
		case EConfigDirection::CD_Left:
			DirectionArray = Left;
			DirectionCount = LeftCount;
			break;
		case EConfigDirection::CD_Right:
			DirectionArray = Right;
			DirectionCount = RightCount;
			break;
		default:
			break;
	}

	if(DirectionArray != nullptr && Index <= DirectionCount - 1)
	{
		return DirectionArray[Index];
	}

	return -1;
}

void NCCrossArray::Insert(uint8_t Value, EConfigDirection Direction)
{
	switch(Direction)
	{
		case EConfigDirection::CD_Up:
			Up[UpCount++] = Value;
			break;
		case EConfigDirection::CD_Down:
			Down[DownCount++] = Value;
			break;
		case EConfigDirection::CD_Left:
			Left[LeftCount++] = Value;
			break;
		case EConfigDirection::CD_Right:
			Right[RightCount++] = Value;
			break;
		default:
			break;
	}
}