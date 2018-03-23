
#include "sys.h"




void SetVcoreUp (unsigned int level)
{
  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;              
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}

void Clk_Init(void)
{
 // SetVcoreUp(PMMCOREV_1); 
  //SetVcoreUp(PMMCOREV_2);                     // Set VCore to 1.8MHz for 20MHz
       
  P11DIR =BIT0+ BIT1+BIT2;                       // P11.0-2 to output direction
  P11SEL |=BIT0+ BIT1+BIT2;                      // P11.1-2 to output ACLK,MCLK,SMCLK

  P5SEL |= BIT4|BIT5;
  UCSCTL6 |=XCAP_3;
  UCSCTL6 &= ~XT1OFF;
 
  SetVcoreUp(1);
  SetVcoreUp(2);
  SetVcoreUp(3);
  
  __bis_SR_register(SCG0);
  UCSCTL0 =0;
  UCSCTL1 = DCORSEL_6;
  UCSCTL2 |= FLLD_1 | 380;
  __bis_SR_register(SCG0);
  __delay_cycles(782000);
  /* 
   * 默认状态下：ACLK=FLLREFCLK=XT1 SMCLK=MCLK=DCOCLKDIV XT2关闭 
   * 为了不产生XT1LFOFFG，将ACLK和FLLREFCLK设置为REFOCLK 
   * 并打开XT2OFF，否则XT2将处于无法使用状态 
   * */  
 // UCSCTL6 &= ~(XT2DRIVE0|XT2DRIVE1|XT2OFF);  
  
  while (SFRIFG1 & OFIFG) {                               // Check OFIFG fault flag  
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);         // Clear OSC flaut Flags  
    SFRIFG1 &= ~OFIFG;                                  // Clear OFIFG fault flag  
  }  
  
  UCSCTL4 = UCSCTL4&(~(SELS_7|SELM_7))|SELS_3|SELM_3;  
}


void ClkInit_8M(void)
{
  P11DIR = BIT1+BIT2+BIT0;                       // P11.1-2 to output direction
  P11SEL |= BIT1+BIT2+BIT0;                      // P11.1-2 to output SMCLK,MCLK
  P2DIR |= BIT6;
  P2SEL |= BIT6;

  UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
  UCSCTL2 = FLLD_1 + 249;                   // Set DCO Multiplier for 8MHz
                                            // (N + 1) * FLLRef = Fdco
                                     // (249 + 1) * 32768 = 8MHz
      
  
  

  __bic_SR_register(SCG0);                  // Enable the FLL control loop
  __delay_cycles(250000);

  // Loop until XT1,XT2 & DCO fault flag is cleared
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
} 



void ClkInit_16M(void)
{
  P11DIR =BIT0+ BIT1+BIT2;                       // P11.0-2 to output direction
  P11SEL |=BIT0+ BIT1+BIT2;                      // P11.0-2 to output ACLK,SMCLK,MCLK
  
  P5SEL |= 0x0C;                            // Port select XT2
  UCSCTL6 &= ~XT2OFF;                       // Enable XT2
  UCSCTL3 |= SELREF_2;                      // FLLref = REFO
                                            // Since LFXT1 is not used,
                                            // sourcing FLL with LFXT1 can cause
                                            // XT1OFFG flag to set
   UCSCTL4 |= SELA_2;                        // ACLK=REFO,SMCLK=DCO,MCLK=DCO

  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
 
  UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
  UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2
  UCSCTL5 |= DIVS_1;
    // expected frequency
  __delay_cycles(100);                      // Wait for slave to initialize
}