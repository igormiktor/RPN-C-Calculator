/*
    Lcd.cpp

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


#include "Lcd.h"

// #include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <avr/pgmspace.h>
#include "avr/io.h"

#include "AVRTools/SystemClock.h"

#include "PinAssignments.h"





namespace
{
    // These are the command the HD44780U understands

    // Commands
    const uint8_t kLcdClearDisplay            = 0x01;
    const uint8_t kLcdReturnHome              = 0x02;
    const uint8_t kLcdEntryModeSet            = 0x04;
    const uint8_t kLcdDisplayControl          = 0x08;
    const uint8_t kLcdCursorShift             = 0x10;
    const uint8_t kLcdFunctionSet             = 0x20;
    const uint8_t kLcdSetCGRamAddr            = 0x40;
    const uint8_t kLcdSetDDRamAddr            = 0x80;

    // Flags for display entry mode
    const uint8_t kLcdEntryRight              = 0x00;
    const uint8_t kLcdEntryLeft               = 0x02;
    const uint8_t kLcdEntryShiftIncrement     = 0x01;
    const uint8_t kLcdEntryShiftDecrement     = 0x00;

    // Flags for display on/off control
    const uint8_t kLcdDisplayOn               = 0x04;
    const uint8_t kLcdDisplayOff              = 0x00;
    const uint8_t kLcdCursorOn                = 0x02;
    const uint8_t kLcdCursorOff               = 0x00;
    const uint8_t kLcdBlinkOn                 = 0x01;
    const uint8_t kLcdBlinkOff                = 0x00;

    // Flags for display/cursor shift
    const uint8_t kLcdDisplayMove             = 0x08;
    const uint8_t kLcdCursorMove              = 0x00;
    const uint8_t kLcdMoveRight               = 0x04;
    const uint8_t kLcdMoveLeft                = 0x00;

    // Flags for function set
    const uint8_t kLcd8BitMode                = 0x10;
    const uint8_t kLcd4BitMode                = 0x00;
    const uint8_t kLcd2Line                   = 0x08;
    const uint8_t kLcd1Line                   = 0x00;
    const uint8_t kLcd5x10Dots                = 0x04;
    const uint8_t kLcd5x8Dots                 = 0x00;


    // Watch face icons
    const uint8_t kWatchIconDataLen = 4*8;
    const PROGMEM char sWatchIcons[] =
    {
        0x00, 0x0e, 0x15, 0x15, 0x11, 0x0e, 0x00, 0x00,     // 12 o'clock
        0x00, 0x0e, 0x15, 0x17, 0x11, 0x0e, 0x00, 0x00,     // 3 o'clock
        0x00, 0x0e, 0x15, 0x15, 0x15, 0x0e, 0x00, 0x00,     // 6 o'clock
        0x00, 0x0e, 0x15, 0x1d, 0x11, 0x0e, 0x00, 0x00      // 9 o'clock
    };

    const uint8_t kNumLines     = 2;

    const char* kBlankLine      = "                ";

};



Lcd::Lcd() :
mDisplayControl( 0 ),
mDisplayMode( 0 )
{
}


void Lcd::init()
{
    // Configure LCD pins for output
    setGpioPinModeOutput( pLcdD4 );
    setGpioPinModeOutput( pLcdD5 );
    setGpioPinModeOutput( pLcdD6 );
    setGpioPinModeOutput( pLcdD7 );
    setGpioPinModeOutput( pLcdEnable );
    setGpioPinModeOutput( pLcdDataSelect );

    // Set LCD pins low
    setGpioPinLow( pLcdD4 );
    setGpioPinLow( pLcdD5 );
    setGpioPinLow( pLcdD6 );
    setGpioPinLow( pLcdD7 );
    setGpioPinLow( pLcdEnable );
    setGpioPinLow( pLcdDataSelect );

    // Wait 50 milliseconds to ensure full voltage rise
    delayMilliseconds( 50 );

    // Pull Enable and Select low (already done)
    setGpioPinLow( pLcdEnable );
    setGpioPinLow( pLcdDataSelect );
    // Set now to send commands to LCD

    // THe initialization sequence for the LCD is something
    // like a magical incantation...

    // More seriously, the problem is we can't count on what
    // state the HD44780U is in because when the ATmega328p resets
    // we have no idea if the HD44780U also reset -- in fact the
    // HD44780U will only reset if the power is pulled.

    // The goal is to put the HD44780U in 4-bit mode regardless of
    // its current state.

    // The recipe below comes from the somewhat ambiguous instructions
    // on page 45/46 of the HD44780U datasheet and review of existing
    // code to initialize this device...

    // First send 0x03 three times...

    // First time...
    writeFourBitsToLcd( 0x03 );
    // Wait > 4.1 ms
    delayMicroseconds( 4500 );

    // Second time...
    writeFourBitsToLcd( 0x03 );
    // Wait > 4.1 ms
    delayMicroseconds( 4500 );

    // Third time...
    writeFourBitsToLcd( 0x03 );
    // Wait > 150 us
    delayMicroseconds( 200 );

    // Here we go with the actual configuration...

    // Set interface to 4-bit mode
    writeFourBitsToLcd( 0x02 );

    // Set nbr of lines and font
    sendCommand( kLcdFunctionSet | kLcd2Line | kLcd5x8Dots );

    // Turn on display, with cursor off and blinking off
    mDisplayControl = kLcdDisplayOn | kLcdCursorOff | kLcdBlinkOff;
    sendCommand( kLcdDisplayControl | mDisplayControl );

    // Set text entry mode (L to R)
    mDisplayMode = kLcdEntryLeft;
    sendCommand( kLcdEntryModeSet | mDisplayMode );

    loadCustomCharacters();

    clear();
    delayMicroseconds( 2000 );  // Clear cmd is slow to actually happen...
}


void Lcd::loadCustomCharacters()
{
    //  Load our watch icons as custom characters into the LCD
    // (actually, the HD44780U chip)

    // Move PROGMEM data to SRAM
    char tmp[ kWatchIconDataLen ];
    memcpy_P( tmp, sWatchIcons, kWatchIconDataLen );

    // Send it to the LCD
    sendCommand( kLcdSetCGRamAddr );
    for ( int8_t i = 0; i < kWatchIconDataLen; ++i )
    {
        sendCharToDisplay( tmp[ i ] );
    }
}



void Lcd::writeFourBitsToLcd( uint8_t value )
{
    // Load the lower 4 bits of value into LCD pins D4 thru D7
    // The 4 pins are wired the lower nibble of a single gpio PORT (PORTC)
    value &= 0x0F;                              // Keep only the lower nibble
    uint8_t portVal = getGpioPORT( pLcdD4 );    // This is pin PC0, so PORTC
    portVal &= 0xF0;                            // Keep only the upper nibble
    uint8_t newPortVal = value | portVal;
    getGpioPORT( pLcdD4 ) = newPortVal;         // Load new PORTC value

    // Pulse the enable pin to have the LCD read the value
    setGpioPinLow( pLcdEnable );
    delayMicroseconds( 2 );
    setGpioPinHigh( pLcdEnable );               // This is the actual enable/read pulse
    delayMicroseconds( 2 );                     // Enable pulse must be > 450ns
    setGpioPinLow( pLcdEnable );
    delayMicroseconds( 100 );                   // Docs say allow 37us, but doesn't work with even 70us...
}



int Lcd::sendCharOrCmdToLcd( uint8_t value, bool isChar )
{
    writeGpioPinDigital( pLcdDataSelect, isChar );

    // Send the high nibble
    writeFourBitsToLcd( value >> 4 );
    // Send the low nibble
    writeFourBitsToLcd( value & 0x0F );

    return 0;
}



void Lcd::clear()
{
    sendCommand( kLcdClearDisplay );    // Clear display, set cursor position to zero
    delayMilliseconds( 2 );             // Takes a while...
}



void Lcd::home()
{
    sendCommand( kLcdReturnHome );      // Set cursor position to zero
    delayMilliseconds( 2 );             // Takes a while...
}



void Lcd::setCursor(  uint8_t row, uint8_t col )
{
    int row_offsets[] = { 0x00, 0x40 };
    if ( row >= kNumLines )
    {
        // Count rows starting at 0 (in traditional C/C++ fashion)
        row %= kNumLines;
    }

    sendCommand( kLcdSetDDRamAddr | ( col + row_offsets[row] ) );
}



void Lcd::displayOff()
{
    mDisplayControl &= ~kLcdDisplayOn;
    sendCommand( kLcdDisplayControl | mDisplayControl );
}



void Lcd::displayOn()
{
    mDisplayControl |= kLcdDisplayOn;
    sendCommand( kLcdDisplayControl | mDisplayControl );
}



void Lcd::cursorOff()
{
    mDisplayControl &= ~kLcdCursorOn;
    sendCommand( kLcdDisplayControl | mDisplayControl );
}



void Lcd::cursorOn()
{
    mDisplayControl |= kLcdCursorOn;
    sendCommand( kLcdDisplayControl | mDisplayControl );
}



void Lcd::blinkOff()
{
    mDisplayControl &= ~kLcdBlinkOn;
    sendCommand( kLcdDisplayControl | mDisplayControl );
}



void Lcd::blinkOn()
{
    mDisplayControl |= kLcdBlinkOn;
    sendCommand( kLcdDisplayControl | mDisplayControl );
}




void Lcd::scrollDisplayLeft()
{
    sendCommand( kLcdCursorShift | kLcdDisplayMove | kLcdMoveLeft );
}



void Lcd::scrollDisplayRight()
{
    sendCommand( kLcdCursorShift | kLcdDisplayMove | kLcdMoveRight );
}



void Lcd::autoscrollOn()
{
    mDisplayMode |= kLcdEntryShiftIncrement;
    sendCommand( kLcdEntryModeSet | mDisplayMode );
}



void Lcd::autoscrollOff()
{
    mDisplayMode &= ~kLcdEntryShiftIncrement;
    sendCommand( kLcdEntryModeSet | mDisplayMode );
}




void Lcd::displayTopRow( const char* str )
{
    clearTopRow();
    setCursor( 0, 0 );
    write( str );
}


void Lcd::displayBottomRow( const char* str )
{
    clearBottomRow();
    setCursor( 1, 0 );
    write( str );
}



void Lcd::clearTopRow()
{
    setCursor( 0, 0 );
    write( kBlankLine );
}


void Lcd::clearBottomRow()
{
    setCursor( 1, 0 );
    write( kBlankLine );
}





size_t Lcd::write( uint8_t value )
{
    int err = sendCharToDisplay( value );
    return ( err ? 0 : 1 );
}




size_t Lcd::write( char value )
{
    int err = sendCharToDisplay( static_cast<uint8_t>( value ) );
    return ( err ? 0 : 1 );
}




size_t Lcd::write( const char* str )
{
    size_t n = 0;
    if ( str )
    {
        int err = 0;
        while ( *str && !err )
        {
            err = sendCharToDisplay( static_cast<uint8_t>( *str++ ) );
            ++n;
        }
    }
    return n;
}




size_t Lcd::write( const char* buffer, size_t size )
{
    return write( reinterpret_cast<const uint8_t*>( buffer), size );
}


size_t Lcd::write( const uint8_t* buffer, size_t size )
{
    size_t n = 0;
    if ( buffer )
    {
        int err = 0;
        while ( n < size && !err )
        {
             err = sendCharToDisplay( *buffer++ );
            ++n;
        }
    }
    return n;
}


void Lcd::flush()
{
    // Do nothing (no buffer to flush)
}
