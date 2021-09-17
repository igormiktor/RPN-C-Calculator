# RPN-C-Calculator
An ATmega328-based RPN calculator in C++

This creates a simple four-function (+, - , *, /) RPN calculator
out of a bare ATmega328p chip wired to a 4x4 button keypad
(with classic row-column wiring) and a 2x16 LCD, all powered
by a 9V battery.

The calculator implements 32-bit floating point arithmetic using
a traditional four-level RPN stack (X, Y, Z, and T as in the
classic HP calculators).  The LCD displays the RPN X register
on the lower row and the RPN Y register on the upper row.

There are two LEDs.  They both flash at start-up just to confirm
operation.  While using the calculator, the green LED lights while
a number is being entered.  The red LED lights up when an overflow,
underflow, or NaN occurs (and an appropriate message displays on
the lower row of the LCD).

The keypad is set up as follows:

| | Col 1 | Col 2 | Col 3 | Col 4 |
| :---: | :---: | :---: | :---: | :---: |
| **Row 1** | 1 | 2 | 3 | / |
| **Row 2** | 4 | 5 | 6 | x |
| **Row 3** | 7 | 8 | 9 | - |
| **Row 4** | +/- | 0 | Enter | + |

Notice there is no decimal point key nor exponentiation ('E'
or 'EE') key.  Only integers can be entered directly: fractional
numbers or numbers in "scientific notation" must be entered by
either division or multiplication.  For example:

* To enter the number 123.456, the key strokes are:
    * 123456
    * 'Enter'
    * 1000
    * '/' (divide)
* To enter the number 1.0e16, the key strokes are:
    * 100000000
    * 'Enter'
    * 100000000
    * '*' (multiply)

This is a limitation of only having 16 keys, not of the chip
or software.  It would be possible to use chords to designate
the decimal point or 'E' keys, but that seemed rather
unintuitive and not worth the trouble.

The display automatically shifts to scientific notation whenever
needed.

A schematic of the circuit and a Fritzing wiring diagram (both in
PDF) are available in the Schematic folder, along with the Fritzing file.

Various design notes appear in the Notes folder.

The Images directory has photos of the calculator.
