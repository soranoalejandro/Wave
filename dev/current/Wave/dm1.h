#pragma once
//#include <stdint.h>
#include "bit.h"

//  ARRAY AND INDEX
#define dm1_size 1024
#define dm1_page_size 8
#define dm1_pages ( dm1_size / dm1_page_size )
#define dm1_last_page ( dm1_pages - 1 )
#define dm1_pages_per_byte 8
#define dm1_index_size ( dm1_pages / dm1_pages_per_byte )
#define dm1_last_index ( dm1_index_size - 1 )
#define dm1_index_displacement 3  //  index offset = page >> dm1_index_displacement

#define dm1_FULL 0xff
#define dm1_cache_size 28
#define dm1_cache_last ( dm1_cache_size - 1 )
uint8_t dm1_cache_pos = 0;
uint8_t dm1_cache[ dm1_cache_size ];
uint8_t dm1_index[ dm1_index_size ];
uint8_t dm1[ dm1_size ];// __attribute__((section(".noinit")));   // do not initialize on restart
uint8_t dm1_current = 0;

//  DEFINITION
void dm1_init();
uint8_t dm1_get_page();
uint8_t dm1_return_page( uint8_t );

#define dm1_cache_write( page ) {if ( dm1_cache_pos < dm1_cache_last ) { dm1_cache[ ++dm1_cache_pos ] = page; } }
#define dm1_get() ( ( dm1_cache_pos > 0 )? dm1_cache[ dm1_cache_pos--] : dm1_get_page() )
#define dm1_return ( page )    {if ( dm1_cache_pos < dm1_cache_last ) { dm1_cache[ ++dm1_cache_pos ] = page; } else { dm1_return_page(page); } }


//  INIT
void dm1_init() {
  uint8_t x = dm1_cache_last;
  while ( x-- > 0) {
    dm1_cache_write( dm1_get_page() );
  }
}

//  RETURN
uint8_t dm1_return_page( uint8_t page ) {
  uint8_t index, mask;
  index = page >> dm1_index_displacement;
  mask = page & ( 1 << dm1_index_displacement - 1 );
  if ( index < dm1_current ) dm1_current = index;
  mask = BIT_OFFSET_TO_MASK[ mask ];
  dm1_index[ index ] ^= mask;
}

//  GET PAGE
uint8_t dm1_get_page() {
  uint8_t iteration = 0;
  uint8_t value;
  do {
    value = ~dm1_index[ dm1_current ];
    if ( value > 0 ) {
      uint8_t mask;
      uint8_t off;
      uint8_t bits = lower_nible(value);
      if ( bits & 0x0f ) {
        first_bit_4L( bits, mask, off );
      } else {
        bits = upper_nible(value);
        first_bit_4H( bits, mask, off );
      }
      dm1_index[ dm1_current ] |= mask;
      return dm1_current + off;
    } else {
      dm1_current++;
      if ( dm1_current >= dm1_pages ) dm1_current = 0;
    }
    iteration++;
  } while ( iteration < dm1_pages );
  return 0;
}
