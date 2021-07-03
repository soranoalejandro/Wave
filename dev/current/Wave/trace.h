#pragma once
//#include <stdint.h>

#define trace_size 256
//#define trace_last ( trace_size - 1 )
uint8_t trace_array[ trace_size ];
uint8_t trace_read = 0;
uint8_t trace_write = 0;

//  TRACE TYPES
enum trace_type {
  NONE, TIMER='-', HARDWARE='H', IDLE='I', SLEEP='S', WAKE='W', USART_R='>', USART_S='<' };

//#define limit( data, limit)   { if ( data >= limit ) data = 0; }

#define trace( type)        { trace_array[ trace_write++ ] = type;  /*limit( trace_write, trace_size); */ }
#define trace_safe( type )   { cli();  trace( type );  sei(); }
#define trace_get( data )      { \
  if ( trace_read != trace_write )  { data = ( trace_type )trace_array[ trace_read++];   /*limit( trace_read, trace_size);*/ } else { data = NONE; } }


