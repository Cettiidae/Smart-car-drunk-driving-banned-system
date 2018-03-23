#ifndef __WT588D_H
#define __WT588D_H

#include "lib.h"

#define RST_0 P1OUT&=~BIT4
#define RST_1 P1OUT|=BIT4 

#define SDA_0 P1OUT&=~BIT5
#define SDA_1 P1OUT|=BIT5
#define CS_0 P1OUT&=~BIT2
#define CS_1 P1OUT|=BIT2
#define SCL_0 P1OUT&=~BIT3
#define SCL_1 P1OUT|=BIT3

void wt588d_Init(void);
void Send_threelines(unsigned char addr); //三线发码子程序 
void Send_sound(char *s,double x);

#endif