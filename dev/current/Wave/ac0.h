#pragma once

#define POWER_DIS_AC0   ( 1<<ACD )

#define ac0_enable()   { ACSR &= ~POWER_DIS_AC0; }
#define ac0_disable()  { ACSR |= POWER_DIS_AC0; }
