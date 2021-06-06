#pragma once

#define PRR_SPI0       ( 1<<PRSPI )

#define spi0_enable()  { PRR &= ~PRR_SPI0; }
#define spi0_disable() { PRR |= PRR_SPI0; }
