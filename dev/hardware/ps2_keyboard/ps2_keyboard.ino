#define OSC_FREQUENCY   16000000L
#include "bit.h"

const uint8_t HEX_TO_ASCII_TABLE [16] = {
  '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', };
#define DIGIT_TO_ASCII(d) ( HEX_TO_ASCII_TABLE[ d ] )

#include "usart0.h"

void led_toggle() { digitalWrite( LED_BUILTIN, !digitalRead( LED_BUILTIN ) ); }
void led_on() { digitalWrite( LED_BUILTIN, true ); }
void led_off() { digitalWrite( LED_BUILTIN, false ); }

#define PS2_CK 2
#define PS2_CK_in 2
#define PS2_DA 4
#define PS2_DA_in 5

#define data_low()      { PORTD &= ~0b00010000;  DDRD |= 0b00010000; }
#define data_release()  { DDRD &= ~0b00010000;  PORTD |= 0b00010000; }
#define ck_low()        { PORTD &= ~0b00000100;  DDRD |= 0b00000100; }
#define ck_release()    { DDRD &= ~0b00000100;  PORTD |= 0b00000100; }
#define da_read()       (  (bool)( PIND & 0b00100000 ) )
#define da_read_port()  ( (bool)( PORTD & 0b00010000 ) )
#define ck_read()       (  (bool)( PIND & 0b00001000 ) )
#define ck_read_port()  ( (bool)( PORTD & 0b00000100 ) )

#include "PS2.h"
#include "pci.h"

ps2_frame frame;

void setup() {
  ps2_frame_init( frame );
  //  PCI
  cli();
  usart0_init_default();

  pinMode( LED_BUILTIN, OUTPUT );
  pinMode( PS2_CK, INPUT_PULLUP );
  pinMode( PS2_CK_in, INPUT_PULLUP );
  pinMode( PS2_DA, INPUT_PULLUP );
  pinMode( PS2_DA_in, INPUT_PULLUP );

  pci_init();
  pci2_interrupt_clear();
  pci2_mask_set_pin( PS2_CK );
  set_bit( pci2_filter, PS2_CK );
  //set_bit( pci2_filter_state, PS2_CK );
  sei();
}

uint8_t send = 0;

//  SLEEPY LOOP
void loop() {
  static uint8_t count = 0;
  
  if ( pci2_event ) {
    
    pci2_event = false;
    delayMicroseconds(3);
    if ( ck_read() )  return;
    //  READ DATA LIN STATE
    //bool state = da_read();
    //printBYTE( '0' + state );

    //  RECEIVE
    if ( send == 0 ) {
      bool state = da_read();
    printBYTE( '0' + state );
      if ( PS2_shift_in( &frame, state ) ) {
        
        send = 1;
        frame.current = 0;
        
        wait_release();
        
        //delayMicroseconds(15);
        ck_low();
        printBYTE(' ');
        
        delayMicroseconds(50);
        //pci2_event = false;
        // data_low();
        // delayMicroseconds(10);
        // ck_release();
      }
    }
    else if ( send == 1 ) {
      //data_low();
      delayMicroseconds(50);
      printHEX(frame.frame);
      printBYTE('\n');
      //frame.current = 0;
      data_low();
      //delayMicroseconds(100);
      //delayMicroseconds(1);
      //bool ss = da_read();
      //printBYTE( '0' + ss ); // + ss
      delayMicroseconds(5);
      ck_release();
      
      //data_release();
      send = 2;
      // frame.current++;
      // if ( frame.current == 2 ) {
      //   data_release();
      //   send = 2;
      // }
    } else if ( send == 2 ) {
      bool state = da_read();
      printBYTE( '0' + state );
      bool res = PS2_shift_out( &frame, state );
      
      if ( frame.current == 8 ) data_release();
      if ( frame.current == 7 ) data_release();
      if ( frame.current == 6 ) data_release();
      if ( frame.current == 5 ) data_release();
      if ( frame.current == 4 ) data_release();
      if ( frame.current == 3 ) data_release();
      if ( frame.current == 2 ) data_release();
      if ( frame.current == 1 ) data_release();

      if ( frame.current == 9 ) data_release();
      if ( frame.current == 10 ) data_release();


      if ( res ) {
        //data_release();
        printBYTE('e');

        count++;
        if (count == 10) {
          printBYTE('L');
          ck_low();
        }

        printHEX(frame.frame);
        printBYTE('\n');
        send = 0;
        frame.current = 0;
      }
    }
  }
}



void wait_release() {
  bool d = da_read();
  bool c = ck_read();
  while ( (!c) || (!d) ) {
    d = da_read();
    c = ck_read();
  };
}
