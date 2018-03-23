#ifndef __CLOCK_H
#define __CLOCK_H

#define CPU_F ((double)16000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

void SetVcoreUp (unsigned int level);

void Clk_Init(void);

void ClkInit_8M(void);
void ClkInit_16M(void);

#endif