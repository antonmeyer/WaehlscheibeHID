# WaehlscheibeHID
This software is for an arduino pro micro (atmega u32).
It acts as an USB keyboard and converts impulses from a rotory disk
into digits transmitted via USB to any software supporting keyboard.

impulse contact (nsi) is connected to pin 10 and nsa to pin 9. nsa get closed
as soon disk is revolved. nsi starts generatiing impulses as soon
disk is released and rotates back.

Needs only 3 wires, for nsi, nsa and 1x ground to the 2 switches. internal pull-up is used
for pin 9 and 10.

If you connect it to your computer (OS does not matter, if it supports USB HID), you might get
an error message. This is for the programming serial line, also implemented on that USB device.
You can ignore that, after ..9 seconds rotory disk keyboard should be ready.

anybody how knows how to resolve tzhsire5 might contact me direct.

