#ifndef NCPADSTATE_H
#define NCPADSTATE_H

#include "../Enums/NCEnums.h"

#define DPAD_BYTE_UP          0x1
#define DPAD_BYTE_UPRIGHT     0x3
#define DPAD_BYTE_RIGHT       0x2
#define DPAD_BYTE_DOWNRIGHT   0x6
#define DPAD_BYTE_DOWN        0x4
#define DPAD_BYTE_DOWNLEFT    0xC
#define DPAD_BYTE_LEFT        0x8
#define DPAD_BYTE_UPLEFT      0x9

struct NCPadState
{
  byte Buttons1;
  byte Buttons2;
  byte AxisTwist;
  byte AxisI;
  byte AxisII;
  byte AxisL;
  
  static const uint8_t TriggerThreshold = 30;
  static const uint8_t FaceButtonThreshold = 10;
  
  bool A() { return Buttons2 & 0x20; };
  bool B() { return Buttons2 & 0x10; };
  bool I() { return AxisI > FaceButtonThreshold; };
  bool II() { return AxisII > FaceButtonThreshold; };
  bool L() { return AxisL < TriggerThreshold; };
  bool R() { return Buttons2 & 0x8; };
  bool Start() { return Buttons1 & 0x8; };
  
  EDPadDirection DPadAngle()
  {
	EDPadDirection Angle = EDPadDirection::DPD_Center;
    switch(Buttons1 >> 4)
    {
    case DPAD_BYTE_UP:
      Angle = EDPadDirection::DPD_Up;
      break;
    case DPAD_BYTE_UPRIGHT:
      Angle = EDPadDirection::DPD_UpRight;
      break;
    case DPAD_BYTE_RIGHT:
      Angle = EDPadDirection::DPD_Right;
      break;
    case DPAD_BYTE_DOWNRIGHT:
      Angle = EDPadDirection::DPD_DownRight;
      break;
    case DPAD_BYTE_DOWN:
      Angle = EDPadDirection::DPD_Down;
      break;
    case DPAD_BYTE_DOWNLEFT:
      Angle = EDPadDirection::DPD_DownLeft;
      break;
    case DPAD_BYTE_LEFT:
      Angle = EDPadDirection::DPD_Left;
      break;
    case DPAD_BYTE_UPLEFT:
      Angle = EDPadDirection::DPD_UpLeft;
      break;
    default:
      break;
    }
    
    return Angle;
  }; 
};

#endif //NCPADSTATE_H
