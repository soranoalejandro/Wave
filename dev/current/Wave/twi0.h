#pragma once

#define PRR_TWI0       ( 1<<PRTWI )

#define twi0_enable()  { PRR &= ~PRR_TWI0; }
#define twi0_disable() { PRR |= PRR_TWI0; }
