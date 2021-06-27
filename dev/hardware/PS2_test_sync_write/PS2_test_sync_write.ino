#include "header.h"

#define CK 5
#define DA 2

#define read_ck() ( bit_is_set( PIND, CK ) )
#define read_da() ( bit_is_set( PIND, DA ) )
#define wait_ck_high()   { loop_until_bit_is_set(PIND, CK); }
#define wait_ck_low()    { loop_until_bit_is_clear(PIND, CK); }

#define pull_ck()     { clear_bit( PORTD, CK );   set_bit( DDRD, CK ); }
#define release_ck()  { clear_bit( DDRD, CK );    set_bit( PORTD, CK ); }
#define pull_da()     { clear_bit( PORTD, DA );   set_bit( DDRD, DA ); }
#define release_da()  { clear_bit( DDRD, DA );    set_bit( PORTD, DA ); }

void setup() {
  cli();
  usart0_init_default();
  release_ck();
  release_da();
}



uint8_t frame = 0;
bool parity = true;
uint8_t command = 0xff;

void loop() {
  
  bool ck_low = !read_ck();
  if (ck_low) {
    //  START
    parity = true;
    wait_ck_high();   wait_ck_low();
    frame = 0;

    //  FIRST BIT
    shift_data();   shift_data();
    shift_data();   shift_data();
    shift_data();   shift_data();
    shift_data();   shift_data();

    //  PARITY
    wait_ck_low();  wait_ck_high();
    //  STOP
    wait_ck_low();  wait_ck_high();
    
    switch (frame) {
      case 0xf0:
      case 0xe0:
      case 0xe1:
        printHEX(frame);
      break;
      default:
        uint8_t d = keyboard_scan_codeset_2[ frame ];
        if ( d == 0) {
          printHEX(frame);
        } else {
          printBYTE( d );
        }
        printBYTE('\n');
      break;
    }
    

    if ( command ) {
      frame = command;
      command = 0;
      //  INHIBIT
      bus_inhibit( 100 );

      //  START
      wait_ck_low();
      parity = true;

      //  FIRST DATA BIT
      shift_data_out();   shift_data_out();
      shift_data_out();   shift_data_out();
      shift_data_out();   shift_data_out();
      shift_data_out();   shift_data_out();

      //  PARITY
      if ( parity ) { release_da(); } else { pull_da(); }
      wait_ck_high();   wait_ck_low();
      //  STOP
      release_da();     wait_ck_high();   wait_ck_low();
      //  READ ACK
      wait_ck_high();

      printHEX(frame);
      printBYTE('\n');
    }
    
  }

}

void bus_inhibit( int seconds) {
  pull_ck();
  delay( seconds );
  pull_da();
  delayMicroseconds(2);
  release_ck();
  wait_ck_high();
}

void shift_data() {
  wait_ck_low();
  frame = frame >> 1;
  bool r = read_da();
  parity ^= r;
  if ( r )  frame |= 0b10000000;
  wait_ck_high();
}

void shift_data_out() {
  wait_ck_high();
  //  frame write
  bool w = frame & 0b00000001;   //  load LSB TO WRITE
  //  WRITE TO DA
  if ( w ) { release_da(); } else { pull_da(); }
  //  SHIFT FRAME
  frame = frame >> 1;

  //  READ FROM ACTUAL LSB FROM DA
  bool r = read_da();
  parity ^= r;
  if ( r )  frame |= 0b10000000;
  wait_ck_low();
}