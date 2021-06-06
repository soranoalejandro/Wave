#pragma once

/*  Make use of the 3 general purpose I/O registers
    to store the most frecuently used/most critical variable
    in order to reduce execution time.

    The AVR ATmega328P has 2 fast access, byte addressable registers:
    - GPIOR2 and GPIOR2
    and 1 fast access, byte and bit addressable register:
    - GPIOR0

    in this file we declare the variables we want to allocate in these registers. */

//  Register GPIOR1 may be used internally by the compiler, need to confirm this before allocating GPIOR1
//#define _VARIABLE_NAME0 GPIOR0    //  Byte addressable (IN / OUT intruction), and bit addressable ( SBI, CBI, SBIS, SBIC ).
// #define _VARIABLE_NAME2 GPIOR2    //  Byte addressable (IN / OUT intruction only).

//#define CYCLE_H GPIOR2