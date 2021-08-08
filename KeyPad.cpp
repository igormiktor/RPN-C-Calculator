/*
    KeyPad.cpp - Driver for a 4x4 keypad used for RPN calculator.

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


#include "KeyPad.h"

#include "AVRTools/SystemClock.h"

#include "PinAssignments.h"



void configureKeyPad()
{
    // Configure the keybad to accept inputs

    // Configure keypad column pins...

    // First set gpio pins PD4-PD7 (= columns), as output (PD0-PD3 unchanged)
    // This is the high nibble of register DDRD
    // Get current DDRD value, set high nibble to ones, write it back
    uint8_t ddrVal = getGpioDDR( pKeyPadCol1 );
    ddrVal |= 0xF0;
    getGpioDDR( pKeyPadCol1 ) = ddrVal;

    // Then set these pins low (high nibble of register PORTD)
    // Get current PORTD value, set high nibble to zeros, write it back
    uint8_t portVal = getGpioPORT( pKeyPadCol1 );
    portVal &= 0x0F;
    getGpioPORT( pKeyPadCol1 ) = portVal;

    // Configure keypad row pins...

    // First set gpio pins PB0-PB3 (= rows), as inputs (PB4-PB7 unchanged)
    // This is the low nibble of register DDRB
    // Get current DDRB value, set low nibble to zeros, write it back
    ddrVal = getGpioDDR( pKeyPadRow1 );
    ddrVal &= 0xF0;
    getGpioDDR( pKeyPadRow1 ) = ddrVal;

    // Then enable pull-up resistors on column pins
    // This is the low nibble of register PORTB
    // Get current PORTB, set low nibble to ones, write it back
    portVal = getGpioPORT( pKeyPadRow1 );
    portVal |= 0x0F;
    getGpioPORT( pKeyPadRow1 ) = portVal;

    // Allow time for the gpio circuits to settle
    delayMicroseconds( 200 );
}



bool keyPressed()
{
    // A key is pressed if any row goes low

    // Get the PINB register value
    uint8_t pinsVal = getGpioPIN( pKeyPadRow1 );

    // Keep only the low nibble (corresponding to rows)
    pinsVal &= 0x0F;

    // If pinsVal != 0x0F, then not all row pins are high, ergo key press
    return ( pinsVal != 0x0F );
}



uint8_t getKeyPressed()
{
    // This function assumes a key is actually been pressed
    // If this assumption is wrong, function returns 255...

    // This will store the key number
    uint8_t keyNbr = 255;

    // First find the row of the key press (which row pin is low)
    if ( !readGpioPinDigital( pKeyPadRow1 ) )
    {
        keyNbr = 0;
    }
    else if ( !readGpioPinDigital( pKeyPadRow2 ) )
    {
        keyNbr = 4;
    }
    else if ( !readGpioPinDigital( pKeyPadRow3 ) )
    {
        keyNbr = 8;
    }
    else if ( !readGpioPinDigital( pKeyPadRow4 ) )
    {
        keyNbr = 12;
    }

    // To read the column value need to flip the configuration of rows & columns
    // Change rows (low nibble) to outputs (set high)...
    uint8_t ddrVal = getGpioDDR( pKeyPadRow1 );
    ddrVal |= 0x0F;
    getGpioDDR( pKeyPadRow1 ) = ddrVal;
    // Set rows (low nibble) low
    uint8_t portVal = getGpioPORT( pKeyPadRow1 );
    portVal &= 0xF0;
    getGpioPORT( pKeyPadRow1 ) = portVal;
    // Change columns (high nibble) to inputs (set low)
    ddrVal = getGpioDDR( pKeyPadCol1 );
    ddrVal &= 0x0F;
    getGpioDDR( pKeyPadCol1 ) = ddrVal;
    // Set pull-up resistors on columns (high nibble) (set high)
    portVal = getGpioPORT( pKeyPadCol1 );
    portVal |= 0xF0;
    getGpioPORT( pKeyPadCol1 ) = portVal;

    // Allow time for the gpio circuits to settle
    delayMicroseconds( 200 );

    // Find the column of the key press (which row pin is low)
    if ( !readGpioPinDigital( pKeyPadCol1 ) )
    {
        keyNbr += 0;
    }
    else if ( !readGpioPinDigital( pKeyPadCol2 ) )
    {
        keyNbr += 1;
    }
    else if ( !readGpioPinDigital( pKeyPadCol3 ) )
    {
        keyNbr += 2;
    }
    else if ( !readGpioPinDigital( pKeyPadCol4 ) )
    {
        keyNbr += 3;
    }

    // restore keypad configuration
    configureKeyPad();

    return keyNbr;
}
