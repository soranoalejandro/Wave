#pragma once
#include <stdint.h>
#include "bit.h"

//  ARRAY AND INDEX
#define dm1_size 1024
#define dm1_page_size 8
#define dm1_pages ( dm1_size / dm1_page_size )
#define dm1_last_page ( dm1_pages - 1 )
#define dm1_pages_per_byte 8
#define dm1_index_size ( dm1_pages / dm1_pages_per_byte )
#define dm1_last_index ( dm1_index_size - 1 )

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

#define dm1_cache_write( page ) {if ( dm1_cache_pos < dm1_cache_last ) { dm1_cache[ ++dm1_cache_pos ] = page; } }
#define dm1_cache_read( ) ( ( dm1_cache_pos > 0 )? dm1_cache[ dm1_cache_pos--] : dm1_get_page() )

//  DECLARATION
void dm1_init() {
  uint8_t x = dm1_cache_last;
  while ( x-- > 0) {
    dm1_cache_write( dm1_get_page() );
  }
}

//  GET PAGE
uint8_t dm1_get_page() {
  uint8_t iteration = 0;
  uint8_t value;
  do {
    value = ~dm1_index[dm1_current];
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
      dm1_index[dm1_current] |= mask;
      return dm1_current + off;
    } else {
      dm1_current++;
      if ( dm1_current >= dm1_pages ) dm1_current = 0;
    }
    iteration++;
  } while ( iteration < dm1_pages );
  return 0;
}


// uint8_t dm1_get() {
//   uint8_t iteration = 0;
//   //uint8_t value;
//   do {
//   value = dm1_index[dm1_current];
//   if ( value < 0xff ) {
//     uint8_t mask;
//     uint8_t off;
//     //  FIND AND RESERVE THE FREE SLOT
//     if ( value != 0x0f ) {
      
//       if ( value & 0b00000001 )  { value = 0b00000001; off = 0; }
//       if ( value & 0b00000010 )  { value = 0b00000010; off = 1; }
//       if ( value & 0b00000100 )  { value = 0b00000100; off = 2; }
//       if ( value & 0b00001000 )  { value = 0b00001000; off = 3; }

//     } else {
//       if ( value & 0b00010000 )  { value = 0b00010000; off = 4; }
//       if ( value & 0b00100000 )  { value = 0b00100000; off = 5; }
//       if ( value & 0b01000000 )  { value = 0b01000000; off = 6; }
//       if ( value & 0b10000000 )  { value = 0b10000000; off = 7; }
//     }
    
//     //  RESERVE AND RETURN
//     dm1_index[dm1_current] |= mask;
//     return dm1_current + off;
//   } else {
//     //  ADVANCE INDEX
//     dm1_current++;
//     if ( dm1_current >= dm1_pages ) dm1_current = 0;
//   }
//   iteration++;
//   } while ( iteration < dm1_pages );
//   return 0;// TCNT0 + TCNT1 | TCNT2;
// }

// void bit_to_mask_n_offset(uint8_t B) {
//   uint8_t offset, mask;
//   B = ~B;
//   if ( B & 1 )                { offset = 0; mask = 1; break; }
//   B = B >> 1;   if ( B & 1 )  { offset = 1; mask = 2; break; }
//   B = B >> 1;   if ( B & 1 )  { offset = 2; mask = 4; break; }
//   B = B >> 1;   if ( B & 1 )  { offset = 3; mask = 8; break; }

//   B = B >> 1;   if ( B & 1 )  { offset = 4; mask = 16; break; }
//   B = B >> 1;   if ( B & 1 )  { offset = 5; mask = 32; break; }
//   B = B >> 1;   if ( B & 1 )  { offset = 6; mask = 64; break; }
//   B = B >> 1;   if ( B & 1 )  { offset = 7; mask = 128; break; }
//   return;
// }