# PyDuino-MK
A simple Python API that interacts (via serial communication) with Arduino devices for USB mouse and keyboard emulation. It is compatible with all Arduino devices (Leonardo, Micro, etc.) that support the Arduino Mouse/Keyboard libraries.

![architecture](https://cloud.githubusercontent.com/assets/10904556/8175573/34c2cbec-13a1-11e5-8274-ab77e87a1164.PNG)

# Features
* Simple Python 2.7 API
* Absolute Mouse Positioning
* Vanilla Arduino (w/o HID modifications)
* Extended mouse and keyboard functions
* Bezier curve mouse movement
* Human-like keyboard typing

# Requirements
* [Python 2.7.x](https://www.python.org/) (does not currently work with Python 3.x)
* [PySerial 2.7](http://pyserial.sourceforge.net/)
* [Arduino IDE 1.6+](http://www.arduino.cc/en/Main/Software)
* A compatible Arduino device

# Installation
To install PyDuino-MK from the PyPI repository, run the following from a command line:

```
pip install pyduino_mk
```
To install PyDuino-MK locally from the source directory, `cd` to the `python` directory containing `setup.py` and run:

```
python setup.py build install
```

# Setup
1. Plug your Arduino device into a computer via USB.
2. `cd` to the `arduino` folder and open the `arduino.ino` file in the Arduino IDE.
3. Upload the sketch to the Arduino device.

After the Arduino sketch has been uploaded, the Arduino device is now ready to accept serial messages from the Python API.

# Usage
To use PyDuino-MK, you must first import the Arduino-MK mouse/keyboard constants and the `Arduino` class encapsulating the Arduino commands. The mouse/keyboard constants are used to designate mouse buttons (i.e. `MOUSE_LEFT`, `MOUSE_RIGHT`) and keyboard keys (i.e. `F1`, `CTRL`, `INSERT`).

```python
from arduino_mk.constants import *
from arduino_mk import Arduino
```

Instantiating the `Arduino` class is simple and easy.

```python
arduino = Arduino()
```

PyDuino-MK automatically detects and establishes a connection with the serial port that the Arduino device resides on. But if for any reason PyDuino-MK is unable to do so, a port can be explicitly provided in an optional parameter.

```python
arduino = Arduino(port='COM5')  # Windows example
```

```python
arduino = Arduino(port='/dev/tty.usbmodemfa141')  # OSX example
```

```python
arduino = Arduino(port='/dev/ttyS2')  # Linux example
```

## Moving the Mouse
PyDuino-MK provides a couple of functions for moving the mouse from one location to another. These functions take two arguments that represent a Cartesian coordinate. A coordinate system where the top-left of the screen represents the origin, `(0, 0)`, such that pixel coordinates increase in the right and down directions is assumed.

```python
# Calling this module will move the mouse from the current mouse position to 
# the specified mouse position in a linear motion.
arduino.move(300, 300)
```
![besenham](https://cloud.githubusercontent.com/assets/10904556/8178406/a19b4b9c-13c2-11e5-847e-b364a73d7445.gif)

```python
# Calling this module will move the mouse from the current mouse position to 
# the specified mouse position in a cubic bezier motion. This module generates
# two random control points every call to vary the mouse paths.
arduino.bezier_move(300, 300)
```
![bezier](https://cloud.githubusercontent.com/assets/10904556/8178416/b67bfdae-13c2-11e5-9a39-234df8d34675.gif)

## Clicking the Mouse
To click using the mouse, call the `click(button)` module. This module holds down the designated button for a random interval between 50-100ms before releasing the button. Make sure that the mouse/keyboard constants are imported into the Python script.

```python
# Left-click (2 ways)
arduino.click()
arduino.click(MOUSE_LEFT)
```

```python
# Middle-click
arduino.click(MOUSE_MIDDLE)
```

```python
# Right-click
arduino.click(MOUSE_RIGHT)
```

To click without holding the mouse button down for a brief moment, use the `fast_click(button)` module.

```python
# Auto-click very quickly
while True:
  arduino.fast_click(MOUSE_LEFT)
```

It may be useful to be able to hold down the mouse button and release it on command. This is where the `press(button)` and `release(button)` modules come in handy.

```python
import time

# Hold the right mouse button for 5 seconds
arduino.press(MOUSE_RIGHT)
time.sleep(5)
arduino.release(MOUSE_RIGHT)
```

```python
# Drag the left mouse button to (500, 500)
arduino.press()
arduino.bezier_move(500, 500)
arduino.release()
```

# License
PyDuino-MK is licensed under the MIT License (see `LICENSE` for details).
