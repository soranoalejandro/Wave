#pragma once

#include <stdint.h>
#include "keyboard_scan_codes.h"

//  PRINT:    decimal, bin, hex
//  PARSE:    
//  DECODE:   font

#define DIGIT_TO_ASCII( d )   ( ( d < 10 )?  ( d + '0' )  : ( d - 10 + 'A' ) )

//  PRINT FUNCTIONS
uint8_t print_uint8_c( uint8_t b, buffer_circular buffer, uint8_t array[] ) {
  uint8_t size = 0, c = '0', d, u ;
  
  //  100
  if ( b > 99) {
    b -= 100; c++;  if ( b > 99) { b -= 100; c++; }
    bufferc_add( c, buffer, array );  size++;   //  print '2', '1' or nothing
  }
  //  load u
  d = upper_nible( b );
  u = lower_nible( b );   if ( u > 9 )  { u -= 10;  d = 1; }
  //  load d
  b = d * 6; //  max 36 d
  if ( b > 19 )  { b -= 19;  d += 2; }
  if ( b > 9 )  { b -= 9;  d ++; }
  //  print d
  if ( size | d ) { bufferc_add( d, buffer, array );  ++size; }   //  print '9' to '0' or nothing
  //  print u
  bufferc_add( u, buffer, array );  ++size;   //  print '9' to '0'
  return size;
}