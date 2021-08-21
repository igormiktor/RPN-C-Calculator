/*
    RpnStack.cpp - Maintain the RPN calculator stack

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


#include "RpnStack.h"

#include <math.h>


/*
    Implement a standard RPN calculator 4-level stack
    with registers X, Y, Z, and T.

    X is replicated on every stack lift
    T is replicated on every stack drop
*/


RpnStack::RpnStack()
: mX( 0.0 ), mY( 0.0 ), mZ( 0.0 ), mT( 0.0 )
{
    // Nothing else to do
}



void RpnStack::push( double d )
{
    lift();
    mX = d;
}



double RpnStack::pop()
{
    double d = mX;
    drop();
    return d;
}



void RpnStack::lift()
{
    // X --> Y --> Z --> T --> <discard>
    // X unchanged
    mT = mZ;
    mZ = mY;
    mY = mX;
}



void RpnStack::drop()
{
    // <discard> <-- X <-- Y <-- Z <-- T
    // T unchanged
    mX = mY;
    mY = mZ;
    mZ = mT;
}



void RpnStack::clear()
{
    mX = mY = mZ = mT = 0.0;
}




void RpnStack::addDigitToX( uint8_t i )
{
    mX *= 10.0;
    if ( mX < 0.0 )
    {
        // Must interpret digits for negative numbers as negative
        mX -= i;
    }
    else
    {
        mX += i;
    }
}



bool RpnStack::isInfiniteX()
{
    return isinf( mX );
}



bool RpnStack::isNanX()
{
    return isnan( mX );
}



void RpnStack::changeSign()
{
    mX *= -1.0;
}



void RpnStack::add()
{
    mY += mX;
    drop();
}



void RpnStack::subtract()
{
    mY -= mX;
    drop();
}



void RpnStack::multiply()
{
    mY *= mX;
    drop();
}



void RpnStack::divide()
{
    mY /= mX;
    drop();
}
