#pragma once

#include "oscilator.h"
#include "gpr.h"

#include "pf.h"

#include "ac0.h"
#include "adc0.h"
#include "usart0.h"
#include "spi0.h"
#include "tim0.h"
#include "tim1.h"
#include "tim2.h"
#include "twi0.h"

#include "power.h"

void hal_init() {
  adc0_disable();
  ac0_disable();
  TCNT2 = 0;
  tim2_set_prescaler(1);
  tim2_set_waveform_mode(0);
  PRR = 0xff ^ PRR_TIM0 ^ PRR_USART0 ^ PRR_TIM2;
  usart0_init_default();
}
