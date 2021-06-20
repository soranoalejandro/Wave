#pragma once

#define PRR_TIM2       ( 1<<PRTIM2 )

#define tim2_enable()  { PRR &= ~PRR_TIM2; }
#define tim2_disable() { PRR |= PRR_TIM2; }


/* 
  OCR2A   Timer 2 set value A
  OCR2B   Timer 2 set value B
  TCNT2   Timer 2 current value
  TCCR2B  FOC2A   FOC2A   -   -   WGM22   CS22  CS21  CS20
  TCCR2A  COM2A1  COM2A0  COM2B1  COM2B0  -   - WGM21   WGM20

  TIMSK2  -   -   -   -   -   OCIE2B  OCIE2A  TOIE2
  TIFR2   -   -   -   -   -   OCF2B   OCF2A   TOV2
  */

/*    WAVEFORM GENERATOR MODES
  MODE  WGM   MODE                TOP   OCR UPDATE    TOV FLAG
  0     000   normal              0xFF  inmediate     MAX
  1     001   PWM, phase corr.    0xFF  TOP           BOTTOM
  2     010   CTC                 ORCA  inmediate     MAX
  3     011   PWM, fast           0xFF  BOTTOM        MAX
  4     100   --                  ----  ----          ---
  5     101   PWM, phase corr.    ORCA  TOP           BOTTOM
  6     110   --                  ----  ----          ---
  7     111   PWM, fast           ORCA  BOTTOM        MAX
  */

/*    CLOCK SELECT
  0   No clock source,  STOP
  1   Div 0       125nS / 62.5nS /    16uS
  2   Div 8       1uS  /  0.5uS      128uS
  3   Div 32      4uS  /  2uS        512uS
  4   Div 64      8uS  /  4uS      1.024mS
  5   Div 128     16uS /  8uS      2.048mS
  6   Div 256     32uS /  16uS     4.096mS
  7   Div 1024    128uS / 64uS    16.384mS
  */


//  PRESCALER
//  TCCR2B  FOC2A   FOC2A   -   -   WGM22   CS22  CS21  CS20
#define tim2_set_prescaler(p)   { TCCR2B = ( TCCR2B & 0b11111000 ) | ( p & 0b00000111 ); }

//  OUTPUT MODE A and B
//  TCCR2A  COM2A1  COM2A0  COM2B1  COM2B0  -   - WGM21   WGM20
#define tim2_set_outmode_a(m)   { TCCR2A = ( TCCR2A & 0b00111111 ) | ( m << 6); }
#define tim2_set_outmode_b(m)   { TCCR2A = ( TCCR2A & 0b11001111 ) | ( ( m & 0b00000011) << 4); }
#define tim2_set_waveform_mode(w)   { TCCR2A = ( TCCR2A & 0b11111100 ) | ( w & 0b00000011 ); }

ISR (TIMER2_OVF_vect)
{
  PF( TICK );
}