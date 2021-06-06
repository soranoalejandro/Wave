#pragma once

//#include "avr_sleep"


#define power_disable_all()   { adc0_disable();   ac0_disable();  PRR = 0xff; }
