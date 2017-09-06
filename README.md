# WählscheibeHID
This software is for an arduino pro micro (atmega32u4).
It acts as an USB keyboard and converts impulses from a rotary disk
into digits transmitted via USB to any keyboard supporting software.

[example at youtube](https://www.youtube.com/watch?v=h1p7Oikf-b4)

Impulse contact (`nsi`) is connected to pin 10 and `nsa` to pin 9. `nsa` gets closed
as soon as the disk is revolved. `nsi` starts generating impulses as soon as the
disk is released and rotates back.

Needs only 3 wires: `nsi`, `nsa`, and 1x ground to the 2 switches. Internal pull-up is used
for pin 9 and 10.

Uses [TimerOne library](https://code.google.com/archive/p/arduino-timerone/downloads).
Search for how-to tutorials if it is your first arduino library you install.

<img src="https://github.com/antonmeyer/WaehlscheibeHID/blob/master/IMG_5230.JPG" height="256" width="342">

If you connect it to your computer (OS does not matter, as long as it supports USB [HID](https://en.wikipedia.org/wiki/Human_interface_device)), you might get
an error message. This is for the programming serial line, also implemented on that USB device.
You can ignore that, after ..9 seconds rotary disk keyboard should be ready.

And if you think twice, impulse dialing is digital dialing. Since 1913 (or so)
