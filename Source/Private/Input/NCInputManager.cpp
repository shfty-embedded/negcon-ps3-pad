#include "../../Public/Input/NCInputManager.h"

#include <EEPROM.h>

#include "../../Public/Teensy/NCPins.h"
#include "../../Public/Serial/NCSerial.h"

void NCInputManager::Update()
{
	digitalWrite(ATT_PIN, LOW);

	NCSerial::Shift(0x01); // Start Command
	NCSerial::Shift(0x42); // Request Data, receive controller ID
	NCSerial::Shift(0xFF); // Receive 0x5A (Data Incoming)
	PadState.Buttons1 = ~NCSerial::Shift(0xFF); // Receive first set of buttons
	PadState.Buttons2 = ~NCSerial::Shift(0xFF); // Receive second set of buttons
	PadState.AxisTwist = NCSerial::Shift(0xFF); // Receive twist axis
	PadState.AxisI = NCSerial::Shift(0xFF); // Receive I button axis
	PadState.AxisII = NCSerial::Shift(0xFF); // Receive II button axis
	PadState.AxisL = ~NCSerial::Shift(0xFF); // Receive L trigger axis

	digitalWrite(ATT_PIN, HIGH);
}
