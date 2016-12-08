#ifndef NCENUMS_H
#define NCENUMS_H

enum EConfigDirection
{
	CD_Invalid,
	CD_Up,
	CD_Down,
	CD_Left,
	CD_Right
};

enum EDPadDirection
{
	DPD_Center = -1,
	DPD_Up = 0,
	DPD_UpRight = 45,
	DPD_Right = 90,
	DPD_DownRight = 135,
	DPD_Down = 180,
	DPD_DownLeft = 225,
	DPD_Left = 270,
	DPD_UpLeft = 315
};

#endif // NCENUMS_H
