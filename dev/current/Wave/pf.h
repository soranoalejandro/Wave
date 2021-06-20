#pragma once
#include <stdint.h>

#define pf_size 200
uint8_t pf_array[ pf_size ];

uint8_t * pf_pointer = pf_array;
uint8_t pf_available = pf_size - 8;