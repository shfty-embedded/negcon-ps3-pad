# negcon-ps3-pad

Firmware for a configurable Arduino-powered DirectInput NeGcon adapter.

(Hardware diagrams and reference images available [here](http://imgur.com/a/RzTdb))

**Setup**

In theory, this should run on any of the Teensy boards. I've only tested with the 3.1 though, so your mileage may vary.

The project is configured for the 3.2/3.1 by default, make sure to configure your board for 'Keyboard + Mouse + Joystick' if you use a different model.

As for the clock speed, I run mine at 96MHz.

**Usage**

After compiling and loading the firmware onto the Teensy via the Arduino software, it should show up as a USB HID device

(DirectInput on Windows, untested on Mac but it should work)


The adapter has several modes that are defined in negcon-ps3-pad.ino. The parameters for each are as follows:

_PS3 Mapping_ (true/false)

Controls PS3 compatibility.

_Custom Inverse Deadzone_ (true/false)

Sets inverse deadzone to the twist axis' current value on activation. (Carried over from an older mode switching setup, may be impractical to activate now.)

_Center Offset_(-127 - 127)

Applies an offset to the center point of the NeGcon's output. Used to compensate for drift on old hardware.

_Inverse Deadzone_ (0-255)

Applies an inverse deadzone to the twist axis' output. Use to negate games' built-in deadzones for finer control.

_TwistSensitivity_ (0.0 - infinity)

Multiplier applied to the NeGcon's twist axis.

_ButtonSensitivity_ (0.0 - infinity)

Multiplier applied to the NeGcon's button axes.


You switch between these modes at runtime by holding start and pressing directions on the d-pad.

By default, the bindings are as follows:

Up
* PC
* PC (Custom Deadzone)

Right
* Ridge Racer 64 (Emulated)
* OutRun 2 (PC Version)

Left
* WipEout HD/Fury (PS3)

Down
* Menu Mode (Disables twist to prevent inverse deadzone from affecting menu)
