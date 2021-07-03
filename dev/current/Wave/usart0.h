#pragma once
//#include <stdint.h>

#define PRR_USART0       ( 1<<PRUSART0 )

#define usart0_enable()  { PRR &= ~PRR_USART0; }
#define usart0_disable() { PRR |= PRR_USART0; }

/*
 * UDR0             data i/o register
 * UBRR0H,  UBRR0L  baudrate register   11-8, 7-0 bits
 * UCSR0A   RXC0    TXC0    UDRE0   FE0   DOR0  UEP0    U2X0  MPCM0
 * UCSR0B   RXCIE0  TXCIE0  UDRIE0  RXEN0 TXEN0 UCSZ02  RXB80 TXB80
 * UCSR0C   UMSEL01 UMSEL00 UMP01 UMP00 USBS0 UCSZ01/UDORD0 UCSZ00/UCPHA0 UCPOL0  
 */

//  TRANSMISION STATUS
#define UCSR0A_RXC       ( 1<<RXC0 )
#define usart0_rx_complete()   ( bit_is_set( UCSR0A, RXC0 ) )
#define UCSR0A_TXC       ( 1<<TXC0 )
#define usart0_tx_complete()   ( bit_is_set( UCSR0A, TXC0 ) )
#define UCSR0A_UDRE       ( 1<<UDRE0 )
#define usart0_tx_empty()   ( bit_is_set( UCSR0A, UDRE0 ) )
#define usart0_wait_tx_empty()   { loop_until_bit_is_set( UCSR0A, UDRE0 ); }

//  FRAME ERROR
#define UCSR0A_ERROR      ( ( 1<<FE0 ) | ( 1<<DOR0 ) | ( 1<<PE0 ) )
#define usart0_error()    ( UCSR0A & UCSR0A_ERROR )

//  BAUDRATE x 2
#define UCSR0A_U2X       ( 1<<U2X0 )
#define usart0_x2_enable()      { UCSR0A |= UCSR0A_U2X; }
#define usart0_x2_disable()     { UCSR0A &= ~UCSR0A_U2X; }

//  MULTI PROCESSOR COMMUNICATION BIT
#define UCSR0A_MPCM       ( 1<<MPCM0 )
#define usart0_multiprocessor_status()     ( bit_is_set( UCSR0A, MPCM0 ) )
#define usart0_multiprocessor_enable()      { UCSR0A |= UCSR0A_MPCM; }
#define usart0_multiprocessor_disable()     { UCSR0A &= ~UCSR0A_MPCM; }
uint8_t usart0_multiprocessor_slave_address = 0;
#define usart0_multiprocessor_set_slave_address(a)    ( _usart0_multiprocessor_slave_address = a )

//  INTERRUPTS
#define UCSR0B_RXCIE    ( 1<<RXCIE0 )
#define usart0_rx_int_enable()       { UCSR0B |= UCSR0B_RXCIE; }
#define usart0_rx_int_disable()      { UCSR0B &= ~UCSR0B_RXCIE; }
#define UCSR0B_TXCIE    ( 1<<TXCIE0 )
#define usart0_tx_int_enable()       { UCSR0B |= UCSR0B_TXCIE; }
#define usart0_tx_int_disable()      { UCSR0B &= ~UCSR0B_TXCIE; }
#define UCSR0B_UDRIE    ( 1<<UDRIE0 )
#define usart0_dre_int_enable()      { UCSR0B |= UCSR0B_UDRIE; }
#define usart0_dri_int_disable()     { UCSR0B &= ~UCSR0B_UDRIE; }

//  TRANSMITER/RECEIVER ENABLE
#define UCSR0B_TXEN    ( 1<<TXEN0 )
#define usart0_tx_enable()      { UCSR0B |= UCSR0B_TXEN; }
#define usart0_tx_disable()     { UCSR0B &= ~UCSR0B_TXEN; }
#define UCSR0B_RXEN    ( 1<<RXEN0 )
#define usart0_rx_enable()      { UCSR0B |= UCSR0B_RXEN; }
#define usart0_rx_disable()     { UCSR0B &= ~UCSR0B_RXEN; }

//  CHARACTER SIZE
#define UCSR0C_UCSZ0    ( 1<<UCSZ00 )
#define UCSR0C_UCSZ1    ( 1<<UCSZ01 )
#define UCSR0B_UCSZ2    ( 1<<UCSZ02 )
#define usart0_set_character_size_5() { UCSR0C &= ~( UCSR0C_UCSZ0 | UCSR0C_UCSZ1 ); UCSR0B &= ~UCSR0B_UCSZ2 }
#define usart0_set_character_size_6() { UCSR0C &= ~( UCSR0C_UCSZ0 | UCSR0C_UCSZ1 ); UCSR0B &= ~UCSR0B_UCSZ2 }
#define usart0_set_character_size_7() { UCSR0C &= ~( UCSR0C_UCSZ0 | UCSR0C_UCSZ1 ); UCSR0B &= ~UCSR0B_UCSZ2 }
#define usart0_set_character_size_8() { UCSR0C |= ( UCSR0C_UCSZ0 | UCSR0C_UCSZ1 ); UCSR0B &= ~UCSR0B_UCSZ2 }
#define usart0_set_character_size_9() { UCSR0C |= ( UCSR0C_UCSZ0 | UCSR0C_UCSZ1 ); UCSR0B |= UCSR0B_UCSZ2 }

//  9TH BIT
#define UCSR0B_RXB8    ( 1<<RXB80 )
#define usart0_read_9th_bit()      ( UCSR0B & UCSR0B_RXB8 )    //  read this before UDR0 in 9 bit data frames
#define UCSR0B_TXB8    ( 1<<TXB80 )
#define usart0_set_9th_bit()      { UCSR0B |= UCSR0B_TXB8; }   //  write this before UDR0 in 9 bit data frames
#define usart0_clear_9th_bit()    { UCSR0B &= ~UCSR0B_TXB8; }

//  PARITY MODE
#define UCSR0C_UPM0    ( 1<<UPM00 )
#define UCSR0C_UPM1    ( 1<<UPM01 )
#define usart0_set_parity_none()     { UCSR0B &= ~( UCSR0C_UPM1 | UCSR0C_UPM0 ); }
#define usart0_set_parity_even()     { UCSR0B |= UCSR0C_UPM1; UCSR0B &= ~UCSR0C_UPM0; }
#define usart0_set_parity_odd()      { UCSR0B |= UCSR0C_UPM1; UCSR0B |= UCSR0C_UPM0; }

//  STOP BITS
#define UCSR0C_USBS    ( 1<<USBS0 )
#define usart0_set_stop_one()     { UCSR0B &= ~UCSR0C_USBS; }
#define usart0_set_stop_two()     { UCSR0B |= UCSR0C_USBS; }


//  DATA REGISTERS
#define usart0_write_8(data)    { UDR0 = data; }
#define usart0_write_8_sync(data)    { usart0_wait_tx_empty();  usart0_write_8(data); }
//  #define usart0_write_8_sync(data)    { while ( !usart0_tx_empty() );  usart0_write_8(data); }

//  write 9th bit first
#define usart0_write_9(data)    { \
if ( data > 255 ) { usart0_set_9th_bit(); } else { usart0_clear_9th_bit(); } \ usart0_write_8(data); }
#define usart0_write_9_sync(data)    { usart0_wait_tx_empty();  usart0_write_9(data); }

#define usart0_read_8()    ( UDR0 )
//  read 9th bit first
#define usart0_read_9()    ( ( 255 * usart0_read_9th_bit() ) + usart0_read_8() )


#define usart0_set_budrate_default()  { UBRR0H = 0; UBRR0L = (OSC_FREQUENCY / 8 / 115200 - 1); usart0_x2_enable(); }
#define usart0_begin()  { UCSR0B |= 0b00011000; }
#define usart0_init_default() { UCSR0B = 0; UCSR0A = 0; UCSR0C = 0b00000110; usart0_set_budrate_default(); usart0_begin(); }
#define usart0_init( baud ) { UCSR0B = 0; UCSR0A = 0; UCSR0C = 0b00000110; usart0_set_baudrate( baud ); usart0_begin(); }

//  MULTI PROCESSOR COMUNICATION
/* usart0_set_character_size_9()
usart0_set_9th_bit()
usart0_clear_9th_bit() */

//  SLAVE MODE
#define usart0_set_multiprocessor_slave_mode(address) { \
  usart0_set_character_size_9();  usart0_multiprocessor_set_slave_address(address); usart0_multiprocessor_enable(); }
//  MASTER MODE
#define usart0_multiprocessor_master_mode()           { usart0_set_character_size_9(); }
#define usart0_multiprocessor_master_select_slave(a)  { usart0_set_9th_bit();  usart0_write_8(a); }



void usart0_set_baudrate ( uint32_t baud ) {
  uint32_t brr = ( OSC_FREQUENCY >> 3 );
  brr = brr / baud - 1;
  uint16_t UBRR0HL = (uint16_t)brr;
  UBRR0H = (uint8_t)( UBRR0HL>>8 );
  UBRR0L = (uint8_t)( UBRR0HL );
  usart0_x2_enable();
}

#define printBYTE usart0_write_8_sync

void printBIN(uint8_t b) {
  uint8_t x = 0;
  uint8_t mask = 0b10000000;
  while ( x < 8 ) {
    //  wair for DRE
    while ( !usart0_tx_empty() );
    //  send byte
    if ( b & mask ) {
      usart0_write_8_sync('1');
    } else {
      usart0_write_8_sync('0');
    }
    mask = mask >> 1;
    ++x;
  }
  usart0_write_8_sync(' ');
}

void printHEX(uint8_t b) {
  uint8_t l = b & 0x0f;
  uint8_t h = b & 0xf0;
  //h = swap(h);
  //if ( h == 0) { usart0_write_8_sync(' '); }
  //else {usart0_write_8_sync( DIGIT_TO_ASCII(h) ); }
  usart0_write_8_sync( DIGIT_TO_ASCII( upper_nible(b) ) );
  usart0_write_8_sync( DIGIT_TO_ASCII( lower_nible(b) ) );
  usart0_write_8_sync('h');
  //usart0_write_8_sync(' ');
}

void printDEC(uint8_t b) {
  uint8_t ch = ' ';
  if ( b > 199) { b -= 200; ch = '2'; }
  else if ( b > 99) { b -= 100; ch = '1'; }
  usart0_write_8_sync( ch );  ch = ' ';
  if ( b > 9 ) {    //  10
    if ( b > 49 ) { b -= 50; ch = 5; } else { ch = 0; }
    while ( b > 9 ) { b -= 10; ++ch; }
    ch = DIGIT_TO_ASCII( ch );
  }   //  1
  usart0_write_8_sync( ch );
  ch = DIGIT_TO_ASCII( b );
  usart0_write_8_sync( ch );
  //usart0_write_8_sync(' ');
}

ISR(USART_RX_vect) {
  uint8_t time = TCNT2;
  uint8_t data;

  trace( USART_R );

  if ( usart0_read_9th_bit() ) {
    data = usart0_read_8();
    //  MULTI PROCESSOR COMMUNICATION MODE
    if ( usart0_multiprocessor_status() ) {
      if ( data == usart0_multiprocessor_slave_address ) {
        usart0_multiprocessor_disable();
      } else {
        usart0_multiprocessor_enable();
      }
    } else {
      // Normal 9 bits data reception,  NOT IMPLEMENTED      
    }
  } else {
    data = usart0_read_8();
    trace( data );
    trace( time );
    //  DATA RECEIVED, 8 bits or MPCM 9 bits ( 1 address and 8 data )
    
  }
}


