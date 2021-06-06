#pragma once
#include <stdint.h>

#define lower_nible( B ) ( B & 0x0f )
#define upper_nible( B ) ( B & 0xf0 )
#define swap(b) ( (b & 0x0f)<<4 | (b & 0xf0)>>4 )

#define first_bit_4L( b, m, o ) { if ( b & 3 )  { if ( b & 1 ) {m=1; o=0;} else {m=2; o=1;} }  else  { if ( b & 4 ) {m=4; o=2;} else {m=8; o=3;} } }
#define first_bit_4H( b, m, o ) { if ( b & 0x3f )  { if ( b & 0x1f ) {m=16; o=4;} else {m=32; o=5;} }  else  { if ( b & 0x4f ) {m=64; o=6;} else {m=128; o=7;} } }
#define first_bit_4L_m( b, m ) { if ( b & 3 )  { if ( b & 1 ) {m=1;} else {m=2;} }  else  { if ( b & 4 ) {m=4;} else {m=8;} } }
#define first_bit_4H_m( b, m ) { if ( b & 0x3f )  { if ( b & 0x1f ) {m=16;} else {m=32;} }  else  { if ( b & 0x4f ) {m=64;} else {m=128;} } }

const uint8_t BIT_OFFSET_TO_MASK [8] {
  1, 2, 4, 8,  16, 32, 64, 128
};

const uint8_t BIT4_FIRST_CLEAR_OFFSET[16] {
   1, 2, 1, 3,  1, 2, 1, 4,  1, 2, 1, 3,  1, 2, 1, 0
};

const uint8_t BIT4_TO_FIRST_CLEAR [16] = {
  0b00000001, 0b00000010, 0b00000001, 0b00000100,
  0b00000001, 0b00000010, 0b00000001, 0b00001000,
  0b00000001, 0b00000010, 0b00000001, 0b00000100,
  0b00000001, 0b00000010, 0b00000001, 0b00000000,
};