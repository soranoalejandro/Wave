#pragma once

#define pf_size 200
uint8_t pf_array[pf_size];
uint8_t pf_lenght = 0;
uint8_t pf_temp;
#define pf( data ) { if ( pf_lenght < ( pf_size -1 ) ) { pf_temp = TCNT2; pf_array[ pf_lenght++ ] = data; } }

#define PFTIME TCNT2

#define PF_LOG( l )
