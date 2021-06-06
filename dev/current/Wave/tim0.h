#pragma once

#define PRR_TIM0       ( 1<<PRTIM0 )

#define tim0_enable()  { PRR &= ~PRR_TIM0; }
#define tim0_disable() { PRR |= PRR_TIM0; }
