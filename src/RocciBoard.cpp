/** 
 * @file        rocciboard.h
 *
 * @mainpage    RocciBoard Library
 * This library was developed by the AK-Entwicklung of the RoCCI e. V. junior robotics association in 2023 together with its hardware complement, 
 * the RocciBoard-Shield for Arduino Mega/Giga, to provide students an easy to learn platform and a first entry into the world of microcontrollers and C++ programming.
 * Because it is meant for young students, this library may not provide all functions and possibilies of the underlying hardware, 
 * but rather the fundamentals needed when starting off with robotics.
 *
 * If you have questions or notice bugs, please feel free to contact the author using the contact details below!
 *
 * @section     Author
 * Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>)
 *
 * @section     License
 * MIT License
 * Copyright (c) 2023 Robotics Competence Center Illertal e. V.
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
 * 
 * @section     History
 * 0.0 [06-2023] Started development
 * 1.0 [09-2023] First stable release
*/

#ifndef rocciboard_h
#define rocciboard_h

#include <Arduino.h>
#include <TCA9548A.h>

bool RocciBoard::Init (void)
{
    // Initializing Error-LED
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    // Initializing Motor Drivers
    motor[0].Init();
    motor[1].Init();
    motor[2].Init();
    motor[3].Init();
    // Initializing I2C-Multiplexer
    tca_.begin(Wire);
    tca_.closeAll();
}

void RocciBoard::OpenChannel (uint8_t index)
{
    tca_.openChannel(index);
}

void RocciBoard::CloseChannel (uint8_t index)
{
    tca_.closeChannel(index);
}

void RocciBoard::CloseAllChannels (void)
{
    tca_.closeAll();
}
