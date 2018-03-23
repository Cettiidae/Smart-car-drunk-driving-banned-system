#ifndef __LIB_H
#define __LIB_H

#include "msp430f5529.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define CPU_F ((double)1000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))




#include "UART.h"
#include "key.h"
#include "DHT11.h"
#include "ds1302.h"
#include "ADC.h"
#include "wt588d.h"


#endif