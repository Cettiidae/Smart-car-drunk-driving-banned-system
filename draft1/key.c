#include "lib.h"
#include "string.h"
#include "stdio.h"

unsigned int number=1;
void KeyInit(void)
{

  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1REN |= BIT1;                            // Enable P1.4 internal resistance
  P1OUT |= BIT1;                            // Set P1.4 as pull-Up resistance
  P1IES |= BIT1;                            // P1.4 Hi/Lo edge
  P1IFG &= ~BIT1;                           // P1.4 IFG cleared
  P1IE |= BIT1;                             // P1.4 interrupt enabled
  
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  _DINT();
  delay_ms(100);
  P1OUT ^= BIT0;                            // P1.0 = toggle
  P1IFG &= ~BIT1;                          // P1.4 IFG cleared
  
 // if(number==1) number=2;
 // else number=1;
  
  if(debug_flag)
  {
    SendData();
    BAC=Concentration*0.00420947;
    sprintf(ConString,"%.2f",BAC);
    Send_sound(ConString,BAC);
  }
 _EINT();
}
