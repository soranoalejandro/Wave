#pragma once

#define PRR_TIM1       ( 1<<PRTIM1 )

#define tim1_enable()  { PRR &= ~PRR_TIM1; }
#define tim1_disable() { PRR |= PRR_TIM1; }
