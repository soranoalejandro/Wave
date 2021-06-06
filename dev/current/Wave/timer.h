#pragma once
#include <stdint.h>

#define CYCLE_H GPIOR2
#define CYCLE_L TCNT2

uint16_t timer_us() {
  return 0;
}