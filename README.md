# arduino-hid-gamepad-test

This is a test program for a game controller made with an Arduino Pro Micro.

## Background

The program uses the NicoHood HID library which, by the way, can be found in the
official Arduino library manager. The controller uses 10 generic push button switches
from a random electronics starter kit, plus a nintendo switch replacement thumbstick module
wired up to the breadboard using a 5 position 0.5mm pitch FPC (fine-pitch connector) from digikey
and a 6 position 0.5mm FPC breakout board.

## Parts Reference

Link to Nintendo Switch Replacement Parts:
https://www.amazon.com/gp/product/B08BL4LY84/ref=ppx\_yo\_dt\_b\_asin\_title\_o02\_s00?ie=UTF8&psc=1

Link to FPC connector:
https://www.digikey.com/short/znv9p3

^^ I found out what this was from this helpful page:
https://github.com/dekuNukem/Nintendo\_Switch\_Reverse\_Engineering/issues/59
https://github.com/dekuNukem/Nintendo\_Switch\_Reverse\_Engineering

Link to breakout board:
https://www.amazon.com/gp/product/B0191ELDL0/ref=ppx\_yo\_dt\_b\_asin\_title\_o00\_s00?ie=UTF8&psc=1

##  Nintendo Switch Thumbstick

It is important to note that the Switch thumbstick is designed to work with 1.8V apparently (see
the Nintendo Switch Reverse Engineering git repo above). The thumbstick can also work perfectly fine
at 5V as well, with the only difference being that the potentiometer values assume a larger range.

At 1.75V, the raw range of the thumbstick appears to be:

x axis -> min: 80, max: 315
y axis -> min: 50, max: 303

In the arduino program, I needed to add some leeway for the analog value mapping because the
joystick output signal is noisy. About 5- 10 in both directions was good:

x axis -> min: 70, max: 325
y axis -> min: 45, max: 315

At 5V, the raw range of the thumbstick appears to be:

x axis -> min: 195, max: 835
y axis -> min: 215, max: 800

Also note: these thumbsticks are very noisy so they may fluctuate quickly around the values above
and somewhat inconsistent. I think what happens is that the ranges may change slightly at
different points of wear and tear, so it would be good to write code to prepare for that.
