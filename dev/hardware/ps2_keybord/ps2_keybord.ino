
void led_toggle() {
  digitalWrite( LED_BUILTIN, !digitalRead( LED_BUILTIN ) );
}

void led_on() {
  digitalWrite( LED_BUILTIN, true );
}

void led_off() {
  digitalWrite( LED_BUILTIN, false );
}

#include "PS2.h"
#include "pci.h"

#define PS2_CK 2
#define PS2_DA 3

ps2_frame frame;

void setup() {
  ps2_frame_init( frame );
  //  PCI
  cli();
  pinMode( LED_BUILTIN, OUTPUT );
  pinMode( PS2_CK, INPUT_PULLUP );   pinMode( PS2_DA, INPUT_PULLUP );
  pci_init();
  pci2_interrupt_clear();
  pci2_mask_set_pin( PS2_CK );
  set_bit( pci2_filter, PS2_CK );
  set_bit( pci2_filter_state, PS2_CK );
  sei();
  Serial.begin(115200);
}



//  SLEEPY LOOP
void loop() {
  if ( pci2_event ) {
    pci2_event = false;
    bool state = digitalRead( PS2_DA );
    //PS2_shift_in( &frame, state );
    if ( PS2_shift_in( &frame, state ) ) {
      led_toggle();
      Serial.print( frame.frame, HEX ); Serial.println( " " );
    }
    
  }
  //  SLEEP
  //led_off();
}
