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
  
  trace_type current;   trace_get( current );

  if ( current != NONE ) {
    //  DECODE TYPE
    if ( ( current != last_type ) || ( repeat == 249 ) ) { //  current != last_type
      if ( ( ( last_type == TIMER ) & ( current != TIMER ) ) | ( repeat == 249 ) ) {
        //printBYTE( last_type );
        if ( repeat ) {
          printBYTE( last_type );
          printBYTE( '\t' );   printDEC( repeat + 1 );
          repeat = 0;
        }
        printBYTE( '\r' );  printBYTE( '\n' );
      }
            
      //  TIMER TICK
      if ( current == TIMER ) {
        last_type = current;
      } else {
        last_type = NONE;
      }
      //  USART RECEIVE
      if ( current == USART_R ) {
        printBYTE( current );
        trace_get( current );  printBYTE( '\t' );   printDEC( current );    //  DATA
        trace_get( current );  printBYTE( '\t' );   printDEC( current );    //  TIME
        printBYTE( '\r' );  printBYTE( '\n' );
      }
      
    } else {
      repeat++;
    }
    
    //  DECODE DATA

  }
}