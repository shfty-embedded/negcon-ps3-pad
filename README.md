# negcon-ps3-pad

Firmware for a configurable Teensyduino-powered DirectInput NeGcon adapter.

(Hardware diagrams and reference images available [here](http://imgur.com/a/RzTdb))

**Setup**

This project is designed to run on a [PJRC Teensy USB microcontroller](http://www.pjrc.com/teensy/index.html).

It's configured for the Teensy 3.1 by default and hasn't been tested with any other models, but in theory it should run on any of them.

Make sure to configure your board for 'Keyboard + Mouse + Joystick' if you use a different model. Clock speed is configured for 96MHz by default, but the project may be able to run acceptably at lower speeds.

**Configuration**

After compiling and loading the firmware onto the Teensy via the Teensyduino software, it should show up as a USB HID device

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

**Usage**

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
