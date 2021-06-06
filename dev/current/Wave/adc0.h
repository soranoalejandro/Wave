#pragma once

#define PRR_ADC0       ( 1<<PRADC )
#define POWER_EN_ADC0  ( 1<<ADEN )

#define adc0_enable()  { PRR &= ~PRR_ADC0;  ADCSRA |= POWER_EN_ADC0; }
#define adc0_disable() { ADCSRA &= ~POWER_EN_ADC0;  PRR |= PRR_ADC0; }
