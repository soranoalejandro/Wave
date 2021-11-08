#include "header.h"

void loop() {  
  //cli();
  while ( event_flags ) {
    event_handler = f_events[ event_flags ] ;
    event_flags = 0;
    //sei();
  }
  //  PROFILING
  
}
