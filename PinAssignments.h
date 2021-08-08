/*
    PinAssignments.h - GPIO pin assignments

    Copyright (c) 2021 Igor Mikolic-Torreira

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef PinAssignments_h
#define PinAssignments_h

#include "AVRTools/GpioPinMacros.h"


/*******************************************************************
********************************************************************

 P I N   A S S I G N M E N T S

********************************************************************
*******************************************************************/
/*
    ATmega328p Package = 28-pin-PDIP
    1: Reset                                      --> Reset switch
    2: PD0 RXD0 PCINT16
    3: PD1 TXD0 PCINT17
    4: PD2 INT0 PCINT18                           --> Red LED
    5: PD3 INT1 OC2B PCINT19                      --> Green LED
    6: PD4 T0 XCK0 PCINT20                        --> Keypad Column 4
    7: Vcc                                        --> +5V
    8: Gnd                                        --> Ground
    9: PB6 TOSC1 XTAL1 PCINT6                     --> 16 MHz Oscillator
    10: PB7 TOSC2 XTAL2 PCINT7                    --> 16 MHz Oscillator
    11: PD5 T1 OC0B PCINT21                       --> Keypad Column 3
    12: PD6 AIN0 OC0A PCINT22                     --> Keypad Column 2
    13: PD7 AIN1 PCINT23                          --> Keypad Column 1
    14: PB0 ICP1 CLKO PCINT0                      --> Keypad Row 4
    15: PB1 OC1A PCINT1                           --> Keypad Row 3
    16: PB2 SS OC1B PCINT2                        --> Keypad Row 2
    17: PB3 MOSI OC2A PCINT3                      --> Keypad Row 1
    18: PB4 MISO PCINT4
    19: PB5 USCK PCINT5
    20: AVCC                                      --> +5V
    21: AREF                                      --> +5V
    22: Gnd                                       --> Ground
    23: PC0 ADC0 PCINT8                           --> LCD Pin D4 (Data)
    24: PC1 ADC1 PCINT9                           --> LCD Pin D5 (Data)
    25: PC2 ADC2 PCINT10                          --> LCD Pin D6 (Data)
    26: PC3 ADC3 PCINT11                          --> LCD Pin D7 (Data)
    27: PC4 ADC4 SDA PCINT12                      --> LCD Pin E  (Enable)
    28: PC5 ADC5 SCL PCINT13                      --> LCD Pin RS (Data/Cmd Select)
*/


// Implement GPIO pin assignments

#define pRedLed         GpioPin( D, 2 )
#define pGreenLed       GpioPin( D, 3 )

#define pKeyPadCol4     GpioPin( D, 4 )
#define pKeyPadCol3     GpioPin( D, 5 )
#define pKeyPadCol2     GpioPin( D, 6 )
#define pKeyPadCol1     GpioPin( D, 7 )
#define pKeyPadRow4     GpioPin( B, 0 )
#define pKeyPadRow3     GpioPin( B, 1 )
#define pKeyPadRow2     GpioPin( B, 2 )
#define pKeyPadRow1     GpioPin( B, 3 )

#define pLcdD7          GpioPin( C, 3 )
#define pLcdD6          GpioPin( C, 2 )
#define pLcdD5          GpioPin( C, 1 )
#define pLcdD4          GpioPin( C, 0 )
#define pLcdEnable      GpioPin( C, 4 )
#define pLcdDataSelect  GpioPin( C, 5 )


#endif  // PinAssignments_h
