#ifndef __RELAY_H
#define __RELAY_H

#define RelayOn P8OUT|=BIT1
#define RelayOff  P8OUT&=~BIT1

void RelayControl_Init(void);

#endif