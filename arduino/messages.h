/*
 * Copyright (c) 2015 Nelson Tran
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MESSAGES_H
#define MESSAGES_H

// mouse commands
const uint8_t MOUSE_CMD            = 0xE0;
const uint8_t MOUSE_CALIBRATE      = 0xE1;
const uint8_t MOUSE_PRESS          = 0xE2;
const uint8_t MOUSE_RELEASE        = 0xE3;

const uint8_t MOUSE_CLICK          = 0xE4;
const uint8_t MOUSE_FAST_CLICK     = 0xE5;
const uint8_t MOUSE_MOVE           = 0xE6;
const uint8_t MOUSE_BEZIER         = 0xE7;

/*
 * The Arduino constants (MOUSE_LEFT, MOUSE_MIDDLE, and MOUSE_RIGHT) 
 * should not be confused with the constants used for serial 
 * communication (LEFT_BUTTON, MIDDLE_BUTTON, and RIGHT_BUTTON).
 */
const uint8_t LEFT_BUTTON          = 0xEA; 
const uint8_t RIGHT_BUTTON         = 0xEB;
const uint8_t MIDDLE_BUTTON        = 0xEC;

// keyboard commands
const uint8_t KEYBOARD_CMD         = 0xF0;
const uint8_t KEYBOARD_PRESS       = 0xF1;
const uint8_t KEYBOARD_RELEASE     = 0xF2;
const uint8_t KEYBOARD_RELEASE_ALL = 0xF3;
const uint8_t KEYBOARD_PRINT       = 0xF4;
const uint8_t KEYBOARD_PRINTLN     = 0xF5;
const uint8_t KEYBOARD_WRITE       = 0xF6;
const uint8_t KEYBOARD_TYPE        = 0xF7;

// etc.
const uint8_t SCREEN_CALIBRATE     = 0xFF;
const uint8_t COMMAND_COMPLETE     = 0xFE;

#endif // MESSAGES_H

