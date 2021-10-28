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

#include <Arduino.h>
#include "keyboard.h"
#include <Keyboard.h>

void parseKeyboardCommand()
{
  while (!Serial.available());
  uint8_t command = Serial.read();
  
  switch(command)
  {
    case KEYBOARD_PRESS:
      Keyboard.press(readByte());
      break;
    
    case KEYBOARD_RELEASE:
      Keyboard.release(readByte());
      break;
    
    case KEYBOARD_RELEASE_ALL:
      Keyboard.releaseAll();
      break;
      
    case KEYBOARD_WRITE:
      Keyboard.write(readByte());
      break;
    
    case KEYBOARD_PRINT:
      Keyboard.print(Serial.readStringUntil('\0'));
      break;
      
    case KEYBOARD_PRINTLN:
      Keyboard.println(Serial.readStringUntil('\0'));
      break;
    
    case KEYBOARD_TYPE:
      String str = Serial.readStringUntil('\0');
      uint8_t wpm = readByte();
      bool mistakes = readByte();
      uint8_t accuracy = readByte();
      type(str, wpm, mistakes, accuracy);
      break;
  }
  
  Serial.write(COMMAND_COMPLETE);
}

uint8_t readByte()
{
  while (!Serial.available());
  return Serial.read();
}

void type(String str, uint8_t wpm, bool mistakes, uint8_t accuracy)
{
  // assuming that 5 characters = 1 word
  const int MILLISECONDS_PER_CHARACTER = 12000 / wpm;
  
  for (int i = 0; i < str.length(); i++)
  {
    Keyboard.press(str[i]);
    
    delay(
      constrain(
        random(MILLISECONDS_PER_CHARACTER * 0.1, 
               MILLISECONDS_PER_CHARACTER * 0.2),
        5,  // do not hold key for less than 5 ms
        50  // and no more than 50 ms
      )
    );
    
    Keyboard.release(str[i]);
    
    delay(random(MILLISECONDS_PER_CHARACTER * 0.2,
                 MILLISECONDS_PER_CHARACTER * 1.4));
    
    if (mistakes && random(0, 100) > accuracy)
    {
      int num_mistakes = random(1, 5);
      
      // make mistakes
      for (int j = 0; j < num_mistakes; j++)
      {
        int key_index = constrain(random(i - 2, i + 2), 
                                  0, str.length() - 1);
                             
        Keyboard.press(str[key_index]);
        
        delay(
          constrain(
            random(MILLISECONDS_PER_CHARACTER * 0.2, 
                   MILLISECONDS_PER_CHARACTER * 0.4),
            5,  // do not hold key for less than 5 ms
            50  // and no more than 50 ms
          )
        );
        
        Keyboard.release(str[key_index]);
        
        delay(random(MILLISECONDS_PER_CHARACTER * 0.2,
                     MILLISECONDS_PER_CHARACTER * 1.4));
      }
      
      // realize mistake and reach for the backspace key
      delay(random(500, 1000));
      
      // fix mistakes
      for (int j = 0; j < num_mistakes; j++)
      {
        Keyboard.press(KEY_BACKSPACE);
        delay(random(20, 50));
        Keyboard.release(KEY_BACKSPACE);
        delay(random(100, 200));
      }
    }
  }
}

