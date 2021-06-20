#pragma once

//  DATATYPES
typedef struct {
  uint8_t frame;
  uint8_t current;
  bool parity;
} ps2_frame;

//  FUNCTIONS

//  INIT
#define  ps2_frame_init( frame )    {  frame.frame = 0;  frame.current = 0;  frame.parity = false;  }

//  RECEIVE
bool PS2_shift_in( ps2_frame * f, bool bit ) {
  if ( f->current == 0 ) { f->current = 1;  f->frame = 0;  f->parity = false;  return false; }
  f->current += 1;
  if ( f->current < 10 )  {
    f->frame = f->frame >> 1;
    if ( bit )  f->frame += 0b10000000;
    f->parity ^= bit; return false; }

  //  check parity bit
  if ( f->current == 10 )  {
    f->parity ^= bit;
    return false; }

  if ( f->current == 11 )  {
    f->current = 0;  return f->parity; }
}
