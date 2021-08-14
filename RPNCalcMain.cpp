/*
    RPNCalcMain.cpp - main program and immediately supporting code

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




#include <avr/interrupt.h>
#include <util/atomic.h>

#include "AVRTools/GpioPinMacros.h"
#include "AVRTools/InitSystem.h"
#include "AVRTools/SystemClock.h"

#include "PinAssignments.h"
#include "KeyPad.h"
#include "Lcd.h"
#include "DisplayFloat.h"

// #define pRedLed     GpioPin( B, 0 )

// Flag set by time interrupt to indicate the 1-second clock tick
bool gTimerFlag = 0;


ISR( TIMER1_COMPA_vect )
{
    gTimerFlag = 1;
}


void initializeTimer()
{
    // Select CTC mode with prescalar = 256
    TCCR1B = ( 1 << WGM12 ) | ( 1 << CS12 );

    // "Top" value for 1Hz output with prescalar of 256
    const uint16_t kTimer1At1Hz  = 62449;
    // Load the CompA "top" counter value
    OCR1A = kTimer1At1Hz;

    // Enable the CompA interrupt for Timer1
    TIMSK1 = ( 1 << OCIE1A );
}


void updateWatchIcon( Lcd& theLcd )
{
    static uint8_t iconCounter = 0;

    ATOMIC_BLOCK( ATOMIC_RESTORESTATE )
    {
        gTimerFlag = 0;
    }

    ++iconCounter;
    iconCounter %= 4;

    theLcd.setCursor( 1, 0 );
    theLcd.write( static_cast<char>( iconCounter ) );
}


int main()
{
    initSystem();
    initSystemClock();

    setGpioPinModeOutput( pRedLed );
    setGpioPinModeOutput( pGreenLed );
    setGpioPinHigh( pRedLed );
//    setGpioPinHigh( pGreenLed );

    delayMilliseconds( 1000 );

    Lcd theLcd;
    theLcd.init();
    //                     0123456789012345
    theLcd.displayTopRow( "Press any key..." );

    configureKeyPad();

    initializeTimer();

    // These are to manage button press delays to debounce buttons
    const int kMinTimeBetweenButtonChecks = 250;            // milliseconds
    static unsigned long sNextTimeButtonPressAccepted = 0;

    while ( 1 )
    {
        if ( gTimerFlag )
        {
            updateWatchIcon( theLcd );
        }

        if ( keyPressed() && millis() > sNextTimeButtonPressAccepted )
        {
            uint8_t keyNbr = getKeyPressed();
            theLcd.clearBottomRow();
            theLcd.setCursor( 1, 15 );
            char c;
            switch ( keyNbr )
            {
                case kKeyZero:
                    displayFloat( 87654321.0, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyOne:
                    displayFloat( 12348765.0, 1, theLcd );;
                    c = 'n';
                    break;

                case kKeyTwo:
                    displayFloat( 12345678.0, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyThree:
                    displayFloat( 1234567.8e1, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyFour:
                    displayFloat( 1234567.8, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyFive:
                    displayFloat( 1234567.8e2, 1, theLcd );
                    c = 'n';
                    break;

                case kKeySix:
                    displayFloat( 1234876.5, 1, theLcd );
                    c = 'n';
                    break;

                case kKeySeven:
                    displayFloat( 1234876.5e1, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyEight:
                    displayFloat( 1234876.5e2, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyNine:
                    displayFloat( -0.12345678, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyChangeSign:
                    displayFloat( 1.0e5, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyEnter:
                    displayFloat( -1.0e3, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyAdd:
                    displayFloat( 1.0e18, 1, theLcd );
                    c = 'n';
                    break;

                case kKeySubtract:
                    displayFloat( -1.0e13, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyMultiply:
                    displayFloat( -1.0e-10, 1, theLcd );
                    c = 'n';
                    break;

                case kKeyDivide:
                    displayFloat( -1.0e21, 1, theLcd );
                    c = 'n';
                    break;

                default:
                    c = 'X';
                    break;
            }

            if ( c != 'n' )
            {
                theLcd.write( c );
            }

            sNextTimeButtonPressAccepted = millis() + kMinTimeBetweenButtonChecks;
        }

    }

}
