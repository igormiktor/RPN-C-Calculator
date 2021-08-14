/*
    DisplayFloat.cpp - Code to format a double for display on the LCD.

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



#include "DisplayFloat.h"

#include <math.h>
#include <inttypes.h>
#include <string.h>

#include <avr/pgmspace.h>
#include "avr/io.h"

#include "Lcd.h"


const uint8_t kNumberOfSignificantDigits    = 7;
const uint8_t kNumberOfDecimals             = kNumberOfSignificantDigits - 1;


// char gTheRealBuffer[ 128];
// char* gBuffer = gTheRealBuffer;

//                         0123456789012345
//                         xxx+d.dddddde+dd
const PROGMEM char sNan[]   = " * Nan * ";
const PROGMEM char sInf[]   = " * Inf * ";
const PROGMEM char sOvf[]   = " * Ovf * ";
const uint8_t kFltMsgLen    = 9;
const uint8_t kStartCol     = 3;        // Col count starts at 0


void displayExponent( int8_t ee, uint8_t row, Lcd& theLcd );

/*
size_t printFloat( float number, int digits )
{
    size_t n = 0;

    if ( isnan( number ) )
    {
        char tmp[ kFltMsgLen + 1 ];
        strncpy_P( tmp, sNan, kFltMsgLen );
        // Ensure null-terminated
        tmp[ kFltMsgLen ] = 0;

        return sprintf( gBuffer, "%s", tmp );
    }
    if ( isinf( number ) )
    {
        char tmp[ kFltMsgLen + 1 ];
        strncpy_P( tmp, sInf, 3 );
        // Ensure null-terminated
        tmp[ kFltMsgLen ] = 0;

        return sprintf( gBuffer, "%s", tmp );
    }
    if ( number >  4294967040.0 || number < -4294967040.0 )   // constants determined empirically
    {
        char tmp[ kFltMsgLen ];
        strncpy( tmp, sOvf, 3 );
        // Ensure null-terminated
        tmp[3] = 0;

        return sprintf( gBuffer, "%s", tmp );
    }

    // Handle negative numbers
    if ( number < 0.0 )
    {
        n += sprintf( gBuffer, "%c", '-' );
        number = -number;
    }

    // Round correctly so that print( 1.999, 2 ) prints as "2.00"
    float rounding = 0.5;
    for ( int i = 0; i < digits; ++i )
    {
        rounding /= 10.0;
    }

    number += rounding;

    // Extract the integer part of the number and print it
    unsigned long int_part = static_cast<unsigned long>( number );
    float remainder = number - static_cast<float>( int_part );
    n += sprintf( gBuffer + n, "%lu", int_part );

    // Print the decimal point, only if there are digits beyond
    if ( digits > 0 )
    {
        n += sprintf( gBuffer + n, "%c", '.' );
    }

    // Extract digits from the remainder one at a time
    while ( digits-- > 0 )
    {
        remainder *= 10.0;
        int toPrint = static_cast<int>( remainder );
        n += sprintf( gBuffer + n, "%d", toPrint );
        remainder -= toPrint;
    }

    sprintf( gBuffer+n, "%c", 0 );

    return n;
}
*/



void displayFloat( double number, uint8_t row, Lcd& theLcd )
{
    // Clear our portion of LCD
    theLcd.setCursor( row, kStartCol );
    for ( uint8_t i = kStartCol; i < 16; ++i )
    {
        theLcd.write( ' ' );
    }

    // First handle special cases
    if ( isnan( number ) )
    {
        char tmp[ kFltMsgLen + 1 ];
        strncpy_P( tmp, sNan, kFltMsgLen );
        tmp[ kFltMsgLen ] = 0;

        // TODO: set NAN indicator LED

        theLcd.setCursor( row, kStartCol );
        theLcd.write( tmp );
        return;
    }
    if ( isinf( number ) )
    {
        char tmp[ kFltMsgLen + 1 ];
        strncpy_P( tmp, sInf, kFltMsgLen );
        tmp[ kFltMsgLen ] = 0;

        // TODO: set INF indicator LED

        theLcd.setCursor( row, kStartCol );
        theLcd.write( tmp );
        return;
    }

    /*
        Process the number...
        (1) Make it positive (and display sign as appropriate)
        (2) If it is within range, display without exponent portion
        (3) If it is out of range, multiply by a power of ten and display
    */

    // Set LCD to where the number starts...
    theLcd.setCursor( row, kStartCol );

    // If positive display a space where + sign would go
    if ( number >= 0.0 )
    {
        theLcd.write( ' ' );
        // The cursor is moved 1 char to the right (desired)
    }

    // Figure out the order of magnitude of the number
    // log10() is expensive -- candidate to maybe replace a
    // series of comparisons to figure out order of magnitude
    int8_t oom = floor( log10( fabs( number ) ) );

    // If it is in range to display as a plain number, do it...
    if ( 0 <= oom && oom < kNumberOfDecimals )
    {
        // How many decimals should we display?
        int8_t decimalsToDisplay = kNumberOfDecimals - oom;
        theLcd.print( number, decimalsToDisplay );
    }
    else
    {
        // It is out of range, so shift it into range
        // by dividing by the order of magnitude
        number *= pow( 10.0, -oom );
        theLcd.print( number, kNumberOfDecimals );

        // Now handle the exponent explicitly
        displayExponent( oom, row, theLcd );
    }
}


void displayExponent( int8_t ee, uint8_t row, Lcd& theLcd )
{
    // Dsiplay the 'e'
    theLcd.write( 'e' );

    // Display the sign and convert to positive value
    if ( ee < 0 )
    {
        theLcd.write( '-' );
        ee *= -1;
    }
    else
    {
        theLcd.write( '+' );
    }

    int8_t hundreds = ee / 100;
    if ( hundreds )
    {
        char tmp[ kFltMsgLen + 1 ];
        strncpy_P( tmp, sNan, kFltMsgLen );
        tmp[ kFltMsgLen ] = 0;

        // TODO: set overflow indicator LED

        theLcd.setCursor( row, kStartCol );
        theLcd.write( tmp );
    }
    else
    {
        int8_t tens = ee / 10;
        char e1 = '0' + tens;
        theLcd.write( e1 );
        ee -= tens * 10;
        char e2 = '0' + ee;
        theLcd.write( e2 );
    }
}




/*

int main()
{
    igorFloat( 123.0 );
    igorFloat( 0.0123 );
    igorFloat( 12300.01 );

    igorFloat( 12345678. );
    igorFloat( 1234567.8 );
    igorFloat( 1234.5678 );
    igorFloat( 1.2345678 );
    igorFloat( .12345678 );
    igorFloat( 12345678e18 );
    igorFloat( 1. );
    igorFloat( 1.e3 );
    igorFloat( 1.e18 );
    igorFloat( 1.e-3);
    igorFloat( 1.e-13);
    igorFloat( -1. );
    igorFloat( -1.e3 );
    igorFloat( -1.e18 );
    igorFloat( -1.e-3);
    igorFloat( -1.e-13);
    igorFloat( -1.e-1 );

}

*/
