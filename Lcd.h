/*
    Lcd.h - Driver for a hard-wired 16 character, 2 row LCD.

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




#ifndef Lcd_h
#define Lcd_h

#include <inttypes.h>
#include "AVRTools/Writer.h"




/*
 * This class provides a high-level interface via direct gpio pinouts to a
 * HD44780U controlling the LCD.
 *
 * This class derives from Writer, thus providing the various numeric conversion functions.
 */

class Lcd : public Writer
{
public:

    /*
     * These constants are used to set the backlight color on the LCD.
     */
    enum
    {
        kBacklight_Red      = 0x1,        //!< Backlight red            \hideinitializer
        kBacklight_Yellow   = 0x3,        //!< Backlight yellow         \hideinitializer
        kBacklight_Green    = 0x2,        //!< Backlight green          \hideinitializer
        kBacklight_Teal     = 0x6,        //!< Backlight teal           \hideinitializer
        kBacklight_Blue     = 0x4,        //!< Backlight blue           \hideinitializer
        kBacklight_Violet   = 0x5,        //!< Backlight violet         \hideinitializer
        kBacklight_White    = 0x7         //!< Backlight white          \hideinitializer
    };


    /*
     * Constructor simply initializes some internal bookkeeping
     * Can't actually initialize the LCD if the constructor is called
     * in global scope
     */
    Lcd();


    /*
     * Initialize the Lcd object.  This must be called before using the Lcd, or
     * calling any of the other member functions.
     *
     * The LCD display is initialized in 16-column, 2-row mode.
     */
    void init();


    /*
     * Clear the display (all rows, all columns).
     */
    void clear();


    /*
     * Move the cursor home (the top row, left column).
     */
    void home();


    /*
     * Display a C-string on the top row.
     */
    void displayTopRow( const char* str );


    /*
     * Display a C-string on the bottom row.
     */
    void displayBottomRow( const char* str );


    /*
     * Clear the top row.
     */
    void clearTopRow();


    /*
     * Clear the bottom row.
     */
    void clearBottomRow();



    /*
     * Turn the display off.
     */
    void displayOff();


    /*
     * Turn the display on.
     */
    void displayOn();


    /*
     * Do not blink the cursor.
     */
    void blinkOff();


    /*
     * Blink the cursor.
     */
    void blinkOn();


    /*
     * Hide the cursor.
     */
    void cursorOff();


    /*
     * Display the cursor.
     */
    void cursorOn();


    /*
     * Scroll the display to the left.
     */
    void scrollDisplayLeft();


    /*
     * Scroll the display to the right.
     */
    void scrollDisplayRight();


    /*
     * Turn on automatic scrolling of the display.
     */
    void autoscrollOn();


    /*
     * Turn off automatic scrolling of the display.
     */
    void autoscrollOff();


    /*
     * Move the cursor the a particular row and column.
     * Row & column numbering starts at 0.
     */
    void setCursor( uint8_t row, uint8_t col );


    /*
     * Pass a command to the LCD.
     * Argument cmd must be a valid HD44780U command.
     */
    void command( uint8_t cmd );



    /*
     * Write a single character to the LCD at the current cursor location.
     * This implements the pure virtual function Writer::write( char c ).
     * Returns the number of bytes written.
     */
    virtual size_t write( char c );


    /*
     * Write a C-string to the LCD at the current cursor location.
     * This implements the pure virtual function Writer::write( const char* str ).
     * Returns the number of bytes written.
     */
    virtual size_t write( const char* str );


    /*
     * Write a given number of characters from a buffer to the LCD at the current cursor location.
     * This implements the pure virtual function Writer::write( const char* buffer, size_t size ).
     * Returns the number of bytes written.
     */
    virtual size_t write( const char* buffer, size_t size );


    /*
     * Write a given number of bytes from a buffer to the LCD at the current cursor location.
     * This implements the pure virtual function Writer::write( const uint8_t* buffer, size_t size ).
     * Returns the number of bytes written.
     */
    virtual size_t write( const uint8_t* buffer, size_t size );


    /*
     * This function does nothing.  It simply implements the pure virtual
     * function Writer::flush().
     */
    virtual void flush();


private:

    enum
    {
        kWriteFourBitsSendCommand = 0,
        kWriteFourBitsSendChar = 1
    };

    void loadCustomCharacters();
    size_t write( uint8_t value );
    void writeFourBitsToLcd( uint8_t value );
    int sendCharOrCmdToLcd( uint8_t value, bool isCommand );

    int sendCommand( uint8_t cmd )
    {
        return sendCharOrCmdToLcd( cmd, kWriteFourBitsSendCommand );
    }

    int sendCharToDisplay( uint8_t value )
    {
        return sendCharOrCmdToLcd( value, kWriteFourBitsSendChar );
    }

    uint8_t             mDisplayControl;
    uint8_t             mDisplayMode;
};

#endif
