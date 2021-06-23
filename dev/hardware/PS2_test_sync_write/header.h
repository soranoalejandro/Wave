


#include "bit.h"

//  OSCILATOR FREQUENCY
#define OSC_FREQUENCY 16000000

//  ENCODING DOT H
const uint8_t HEX_TO_ASCII_TABLE [16] = {
  '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', };
#define DIGIT_TO_ASCII(d) ( HEX_TO_ASCII_TABLE[ d ] )

#include "usart0.h"