#pragma once

/*  PINn  -   PORT INPUT REGISTER, CAN WRITE TO 1 FOR OUTPUT TOGGLE TOO
    DDRn  -   DATA DIRECTION REGISTER:  0 = input, 1 = output
    PORTn -   PORT OUTPUT REGISTER, SERVES AS PULL-UP STATE IN INPUT MODE...
              ... 0 = LOW or PULL-UP DISABLE, 1 = HIGH or PULL-UP ENABLED   */

/*  PIN MODES AND OPERATIONS:
    - INPUT READ
    - INPUT ( HI-Z )
    - INPUT PULL UP
    - INPUT PULL DOWN (not supported in AVR)
    - INPUT ONLY (DOES NOT CHANGE PULL-UP/ PIN STATE in PORTn)
    - OUTPUT WRITE
    - OUTPUT HIGH
    - OUTPUT LOW
    - OUTPUT TOGGLE
    - OUTPUT ONLY (DOES NOT CHANGE PULL-UP/ PIN STATE in PORTn)   */

#define pin_read_b 0
#define pin_direction_b 0
#define pin_state_b 0
#define pin_toggle_b 0
