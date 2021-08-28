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


#include <inttypes.h>

#include <avr/interrupt.h>
#include <util/atomic.h>

#include "AVRTools/GpioPinMacros.h"
#include "AVRTools/InitSystem.h"
#include "AVRTools/SystemClock.h"

#include "PinAssignments.h"
#include "KeyPad.h"
#include "Lcd.h"
#include "RpnStack.h"
#include "DisplayFloat.h"

// #define pRedLed     GpioPin( B, 0 )


void displayStack( RpnStack& stack, Lcd& lcd );
void initializeTimer();
void updateWatchIcon( Lcd& theLcd );
void startNumericEntryMode();
void endNumericEntryMode();
void doNumericKey( RpnStack& stack, uint8_t value );
void doEnterKey( RpnStack& stack );
void displayStack( RpnStack& stack, Lcd& lcd );



// Helper class to manage flags
class FlagType
{
public:
    FlagType() : mMode( false ) {}

    bool isSet() { return mMode; }

    void clear() { mMode = false; }
    void set() { mMode = true; }

private:
    bool mMode;
};


// Flag to indicate when we are in numeric entry mode
FlagType gNumericEntryMode;

// Flag to indicate that prior key was "Enter"
FlagType gPreviousKeyWasEnter;

// Flag to indicate the 1-second clock tick
FlagType gTimer1SecondFlag;





int main()
{
    initSystem();
    initSystemClock();

    setGpioPinModeOutput( pRedLed );
    setGpioPinModeOutput( pGreenLed );
    setGpioPinHigh( pRedLed );
    setGpioPinHigh( pGreenLed );

    Lcd theLcd;
    theLcd.init();
    //                     0123456789012345
    theLcd.displayTopRow( "RPN Calculator+" );

    configureKeyPad();

    initializeTimer();

    RpnStack stack;

    delayMilliseconds( 1000 );

    // We are ready to start
    setGpioPinLow( pRedLed );
    setGpioPinLow( pGreenLed );
    //                     0123456789012345
    theLcd.displayTopRow( "Press any key..." );

    // These are to manage button press delays to debounce buttons
    const unsigned int kMinTimeBetweenButtonChecks = 250;       // milliseconds
    static unsigned long sNextTimeButtonPressAccepted = 0;

    // Use this to know to clear LCD on the first keystroke
    bool isFirstKeyStroke = true;

    while ( 1 )
    {
        if ( gTimer1SecondFlag.isSet() )
        {
            updateWatchIcon( theLcd );
        }

        if ( keyPressed() && millis() > sNextTimeButtonPressAccepted )
        {
            // Clear top row on first keystroke
            if ( isFirstKeyStroke )
            {
                isFirstKeyStroke = false;
                theLcd.clearTopRow();
            }

            uint8_t keyNbr = getKeyPressed();
            theLcd.clearBottomRow();
            theLcd.setCursor( 1, 15 );
            switch ( keyNbr )
            {
                // Numeric keys...

                case kKeyZero:
                    doNumericKey( stack, 0 );
                    break;

                case kKeyOne:
                    doNumericKey( stack, 1 );
                    break;

                case kKeyTwo:
                    doNumericKey( stack, 2 );
                    break;

                case kKeyThree:
                    doNumericKey( stack, 3 );
                    break;

                case kKeyFour:
                    doNumericKey( stack, 4 );
                    break;

                case kKeyFive:
                    doNumericKey( stack, 5 );
                    break;

                case kKeySix:
                    doNumericKey( stack, 6 );
                    break;

                case kKeySeven:
                    doNumericKey( stack, 7 );
                    break;

                case kKeyEight:
                    doNumericKey( stack, 8 );
                    break;

                case kKeyNine:
                    doNumericKey( stack, 9 );
                    break;


                // Non-numeric keys...

                case kKeyEnter:
                    endNumericEntryMode();
                    doEnterKey( stack );
                    break;

                case kKeyChangeSign:
                    stack.changeSign();
                    gPreviousKeyWasEnter.clear();
                    break;

                case kKeyAdd:
                    endNumericEntryMode();
                    stack.add();
                    gPreviousKeyWasEnter.clear();
                    break;

                case kKeySubtract:
                    endNumericEntryMode();
                    stack.subtract();
                    gPreviousKeyWasEnter.clear();
                    break;

                case kKeyMultiply:
                    endNumericEntryMode();
                    stack.multiply();
                    gPreviousKeyWasEnter.clear();
                    break;

                case kKeyDivide:
                    endNumericEntryMode();
                    stack.divide();
                    gPreviousKeyWasEnter.clear();
                    break;

                default:
                    break;
            }

            displayStack( stack, theLcd );

            sNextTimeButtonPressAccepted = millis() + kMinTimeBetweenButtonChecks;
        }

    }

}



void doNumericKey( RpnStack& stack, uint8_t value )
{
    if ( !gNumericEntryMode.isSet() )
    {
        // Enter numeric entry mode
        startNumericEntryMode();

        // Only lift the stack if previous key was NOT enter and
        // don't currently have a NaN or Inf in X.
        // NOTE: in a real calculator, want the NaN/Inf to propagate,
        // but in this calculator there is no way to clear these.  So
        // this is a bit of a hack.
        if ( !gPreviousKeyWasEnter.isSet() && !stack.isNanX()
                && !stack.isInfiniteX() )
        {
            stack.lift();
        }

        // Always clear X
        stack.clearX();
    }

    // Once in numeric entry mode, we add the number we are accumulating to the stack X
    stack.addDigitToX( value );
    gPreviousKeyWasEnter.clear();
    if ( stack.isInfiniteX() )
    {
        // Set the warning LED to indicate the INF
        setGpioPinHigh( pRedLed );

        // Causing an overflow on digit entry clears numeric entry mode
        // This allow user to re-start entering a number (which clears X)
        // No other choice since we don't have a clear or backspace key...
        // Numeric entry LED stays on to indicate this
        gNumericEntryMode.clear();
        // Pretend previous key as a stack lift to avoid re-lifting the stack
        gPreviousKeyWasEnter.set();

        // Note that we don't just clear X at this time because we need
        // to display the infinte X together with the INF (red) Led.
    }
}



void doEnterKey( RpnStack& stack )
{
    stack.lift();
    gPreviousKeyWasEnter.set();
}



void startNumericEntryMode()
{
    setGpioPinHigh( pGreenLed );
    gNumericEntryMode.set();
}


void endNumericEntryMode()
{
    setGpioPinLow( pGreenLed );
    gNumericEntryMode.clear();
}



void displayStack( RpnStack& stack, Lcd& lcd )
{
    // Set NAN and OVF LCD accordingly
    displayFloat( stack.Y(), 0, lcd );
    uint8_t ret = displayFloat( stack.X(), 1, lcd );

    // Set NaN/Inf indicator LED accordingly
    switch ( ret )
    {
        case kNan:
        case kInfinity:
            setGpioPinHigh( pRedLed );
            break;

        default:
            setGpioPinLow( pRedLed );
            break;
    }
}



ISR( TIMER1_COMPA_vect )
{
    gTimer1SecondFlag.set();
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
        gTimer1SecondFlag.clear();
    }

    ++iconCounter;
    iconCounter %= 4;

    theLcd.setCursor( 1, 0 );
    theLcd.write( static_cast<char>( iconCounter ) );
}
