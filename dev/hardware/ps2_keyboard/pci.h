#pragma once
#include <stdint.h>
/*  PIN CHANGE INTERRUPTS  */
/*  PCIFR : PCIFn   = Interrupt flag
    PCICR : PCIEn   = Interrupt enable
    PCMSKn  = Pin mask  */

//#define set_bit( s, b) ( s |= _BV( b ) )
//#define clear_bit( s, b) ( s &= ~_BV( b ) )



#define pci0_interrupt_enable()   { set_bit( PCICR, PCIE0 ); }
#define pci1_interrupt_enable()   { set_bit( PCICR, PCIE1 ); }
#define pci2_interrupt_enable()   { set_bit( PCICR, PCIE2 ); }
#define pci0_interrupt_disable()  { clear_bit( PCICR, PCIE0 ); }
#define pci1_interrupt_disable()  { clear_bit( PCICR, PCIE1 ); }
#define pci2_interrupt_disable()  { clear_bit( PCICR, PCIE2 ); }
#define pci0_interrupt_clear()    { set_bit( PCIFR, PCIF0 ); }
#define pci1_interrupt_clear()    { set_bit( PCIFR, PCIF1 ); }
#define pci2_interrupt_clear()    { set_bit( PCIFR, PCIF2 ); }

void  pci_init() {
  PCMSK0 = 0; PCMSK1 = 0; PCMSK2 = 0;
  PCICR = 7;
  pci0_interrupt_clear();
  pci1_interrupt_clear();
  pci2_interrupt_clear();
}

#define pci0_mask_set_pin( pin )    { set_bit( PCMSK0, pin ); }
#define pci1_mask_set_pin( pin )    { set_bit( PCMSK1, pin ); }
#define pci2_mask_set_pin( pin )    { set_bit( PCMSK2, pin ); }
#define pci0_mask_clear_pin( pin )  { clear_bit( PCMSK0, pin ); }
#define pci1_mask_clear_pin( pin )  { clear_bit( PCMSK1, pin ); }
#define pci2_mask_clear_pin( pin )  { clear_bit( PCMSK2, pin ); }

//  uint8_t pci0_last_state = 0;  uint8_t pci1_last_state = 0;  

volatile uint8_t pci0_filter = 0,  pci1_filter = 0,  pci2_filter = 0;
volatile uint8_t pci0_filter_state = 0,  pci1_filter_state = 0,  pci2_filter_state = 0;
volatile uint8_t pci0_auto_off = 0,  pci1_auto_off = 0,  pci2_auto_off = 0;

uint8_t pci0_notify[ 8 ];
uint8_t pci1_notify[ 8 ];
uint8_t pci2_notify[ 8 ];
bool pci0_event = false,  pci1_event = false,  pci2_event = false;


ISR( PCINT2_vect )  {    // PORT D PIN CHANGE
  uint8_t current = PIND;
  static uint8_t pci2_last_state = 0;
  uint8_t changed = ( pci2_last_state ^ current ) & PCMSK2;
  pci2_last_state = current;
  if ( changed == 0 ) return;
  
  
  //  FILTER RISING OR FALLING EDGE
  uint8_t filter = pci2_filter & changed;
  if ( pci2_filter ) {
    uint8_t filter_state = pci2_filter_state;

    uint8_t different = (current ^ filter_state) & filter ;
    changed ^= different; //  remove the changed flag for bits different to the filter
  }
  if ( changed == 0 ) return;

  //  AUTO OFF PINS
  //changed ^= ( pci2_auto_off & changed );
  pci2_event = true;
}

