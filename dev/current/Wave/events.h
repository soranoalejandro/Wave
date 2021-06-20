#pragma once
#include <stdint.h>
#include "bit.h"


/*  MODEL:
  A BYTE variable keeps track of 'Event Types' as 8 bit flags.
  The position of each bit flag determines the order of priority in wich
  events will be handled. HARDWARE EVENTS are always executed first.
  */
#define event_flags           GPIOR0
#define HARDWARE_BIT_POSITION   7   //  HW
#define INMEDIATE_BIT_POSITION  6   //  INMEDIATE
#define NORMAL_BIT_POSITION     5   //  NORMAL
#define MEMORY_BIT_POSITION     4   //  DYNAMIC MEMORY

#define set_HARDWARE_event_flag()     { set_bit( event_mask, HARDWARE_BIT_POSITION ); }
#define clear_HARDWARE_event_flag()   { clear_bit( event_mask, HARDWARE_BIT_POSITION ); }
#define set_INMEDIATE_event_flag()    { set_bit( event_mask, INMEDIATE_BIT_POSITION ); }
#define clear_INMEDIATE_event_flag()  { clear_bit( event_mask, INMEDIATE_BIT_POSITION ); }
#define set_NORMAL_event_flag()       { set_bit( event_mask, NORMAL_BIT_POSITION ); }
#define clear_NORMAL_event_flag()     { clear_bit( event_mask, NORMAL_BIT_POSITION ); }
#define set_MEMORY_event_flag()       { set_bit( event_mask, MEMORY_BIT_POSITION ); }
#define clear_MEMORY_event_flag()     { clear_bit( event_mask, MEMORY_BIT_POSITION ); }


void f_event_none () {};          //  EVENT HANDLER FUNCTIONS
void f_event_hardware ();
void f_event_inmediate ();
void f_event_normal ();
void f_event_memory ();
void f_event_bulk ();

typedef void (*fp_event_t)(void);           //  HANDLER FUNCTIONS TYPE AND MAPPINGS
const fp_event_t f_events[ 16 ] = {
  f_event_none,       f_event_hardware,     // 0000 - 0001
  f_event_inmediate,  f_event_hardware,     // 0010 - 0011
  f_event_normal,     f_event_hardware,     // 0100 - 0101
  f_event_inmediate,  f_event_hardware,     // 0110 - 0111
  f_event_memory,     f_event_hardware,     // 1000 - 1001
  f_event_inmediate,  f_event_hardware,     // 1010 - 1011
  f_event_normal,     f_event_hardware,     // 1100 - 1101
  f_event_inmediate,  f_event_hardware, };  // 1110 - 1111

fp_event_t event_handler = f_event_none;



// #define send_message ( event_bit, address, format )  { set_bit( event_mask, event_bit ); \
//   /* hardware_buffer[ hardware_end++ ];*/ }
// #define send_message_data ( data )

// uint8_t hardware_buffer[32];  uint8_t hardware_start = 0;  uint8_t hardware_end = 0;