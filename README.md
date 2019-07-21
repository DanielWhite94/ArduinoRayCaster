### Overview

This project is a proof of concept of how one might implement ray casting efficiently on a modest system such as an Arduino board. Ray casting is already very fast, but we also use fixed-point arithmetic to avoid slow emulated floating point (as the Atmega2560 and others do not have FPUs).

For now the makefile targets a standard PC, not an Arduino,  to ease development. To make this possible there is a wrapper (see the ``sdl`` directory) which provides the same interface one would have using the Arduino EsploraTFT library.

### Screenshots
![Screenshot of Arduino Ray Casting](https://github.com/DanielWhite94/ArduinoRayCaster/blob/master/screenshots/a.png)

![Screenshot of Arduino Ray Casting](https://github.com/DanielWhite94/ArduinoRayCaster/blob/master/screenshots/b.png)

![Screenshot of Arduino Ray Casting](https://github.com/DanielWhite94/ArduinoRayCaster/blob/master/screenshots/c.png)

### Compiling and Using

To build use the included `Makefile` - the produced executable is called ``main``. Once running one can use the arrow keys to move around.
