/*
    KeyPad.h - Driver for a 4x4 keypad used for RPN Calculator.

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

/*
    KeyPad layout:

            | Col 1 | Col 2 | Col 3 | Col 4 |
    | Row 1 |   1   |   2   |   3   |   /   |
    | Row 2 |   4   |   5   |   6   |   x   |
    | Row 3 |   7   |   8   |   9   |   -   |
    | Row 4 |  +/-  |   0   | Enter |   +   |

    Columns and rows are wired to pins:
        pKeyPadCol1
        pKeyPadCol2
		pKeyPadCol3
        pKeyPadCol4
		pKeyPadRow1
		pKeyPadRow2
		pKeyPadRow3
		pKeyPadRow4

    Keys are numbered:
         0   1   2   3
         4   5   6   7
         8   9  10  11
        12  13  14  15
*/

#ifndef KeyPad_h
#define KeyPad_h


#include <inttypes.h>



enum
{
    kKeyOne = 0,
    kKeyTwo,
    kKeyThree,
    kKeyDivide,
    kKeyFour,
    kKeyFive,
    kKeySix,
    kKeyMultiply,
    kKeySeven,
    kKeyEight,
    kKeyNine,
    kKeySubtract,
    kKeyChangeSign,
    kKeyZero,
    kKeyEnter,
    kKeyAdd
};

void configureKeyPad();
bool keyPressed();
uint8_t getKeyPressed();


#endif // KeyPad_h
