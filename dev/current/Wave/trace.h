#pragma once
#include <stdint.h>

#define trace_size 200
#define trace_last ( 200 - 1 )
uint8_t trace_array[ trace_size ];
uint8_t trace_read = 0;
uint8_t trace_write = 0;

//  TRACE TYPES
enum trace_type {
  NONE, TIMER, HARDWARE, IDLE, SLEEP, WAKE };

#define limit( data, limit)   { if ( data >= limit ) data = 0; }
#define trace( type, time)        { trace_array[ trace_write++ ] = type;  limit( trace_write, trace_size); }
#define trace_safe( type, time)   { cli();  trace( type, time);  sei(); }
#define trace_get( data )      { \
  if ( trace_read != trace_write )  { data = ( trace_type )trace_array[ trace_read++];   limit( trace_read, trace_size); } else { data = NONE; } }

//  TRACE OUTPUT BUFFER
#define TRACE_OUT_ARRAY
#define TRACE_OUT_SIZE 8
buffer_circular TRACE_OUT;

//  INIT
void trace_init() {
  TRACE_OUT.len = 0;   TRACE_OUT.start = 0;
  TRACE_OUT.end = 0;   TRACE_OUT.last = TRACE_OUT_SIZE;
}

