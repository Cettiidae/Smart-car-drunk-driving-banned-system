#include "lib.h"

void RelayControl_Init(void)
{
  P8DIR = BIT1;
  P8OUT |= BIT1;
}

