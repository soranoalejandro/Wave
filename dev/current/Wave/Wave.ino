#include "header.h"

void loop() {  
  //cli();
  while ( event_flags ) {
    event_handler = f_events[ event_flags ] ;
    event_flags = 0;
    //sei();
  }
  //  PROFILING
  trace_decode();
}

void trace_decode() {
  static trace_type last_type = NONE;
  static uint8_t repeat = 0;
  uint8_t dat;
  trace_type current;   trace_get( current );   trace_get( dat );

  if ( current != NONE ) {
    //  DECODE TYPE
    if ( ( current != last_type ) || ( repeat == 244 ) ) { //  current != last_type
                
      printBYTE( current + '0' );   printHEX( repeat );
      
      repeat = 0;
      last_type = current;
      printBYTE( '\n' );
    } else {
      repeat++;
    }

    
    //  DECODE DATA

  }
}