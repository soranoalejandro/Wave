#pragma once
#include <stdint.h>
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
  f->current += 1;
  //  START     //  TODO - If start bit is not '0' discard this frame
  if ( f->current == 1 ) { f->parity = false;  return false; }
  //  DATA BITS - bits 2-9, LSB first
  if ( f->current < 10 )  {
    f->frame = f->frame >> 1;
    if ( bit )  f->frame += 0b10000000;
    f->parity ^= bit; return false; }
  //  PARITY - bit 10
  if ( f->current == 10 )  {
    f->parity ^= bit;
    return false; }
  //  STOP - bit 11       //  TODO - If stop bit is not '1' discard this frame
  f->frame = f->frame; f->current = 0;  return f->parity;
}

bool PS2_shift_out( ps2_frame * f, bool bit ) {
  f->current += 1;
  //  START     //  TODO - If start bit is not '0' discard this frame
  if ( f->current == 1 ) { f->parity = false;  return false; }
  //  DATA BITS - bits 2-9, LSB first
  if ( f->current < 10 )  {
    f->frame = f->frame >> 1;
    if ( bit )  f->frame += 0b10000000;
    f->parity ^= bit; return false; }
  //  PARITY - bit 10
  if ( f->current == 10 )  {
    f->parity ^= bit;
    return false; }
  //  STOP - bit 11       //  TODO - If stop bit is not '1' discard this frame
  if ( f->current == 11 )  {
    return false; }
  f->frame = f->frame; f->current = 0;  return true;
  
}
