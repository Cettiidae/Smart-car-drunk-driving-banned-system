
#include "lib.h"

//u16 adc_0[50];
unsigned int adc_sum;
unsigned int adc_num;
unsigned int sum_index;
unsigned int adc_ave[201];
unsigned int adc_value;
double adc;


void ADC12_Init(void)
{
  P6SEL |= 0x01;                            // Enable A/D channel A0
  
  /* Initialize ADC12_A */ 
  ADC12CTL0 = ADC12ON+ADC12SHT0_8+ADC12MSC;// // Turn on ADC12, set sampling time
                                            // set multiple sample conversion
  ADC12CTL1 = ADC12SHP+ADC12CONSEQ_2 +ADC12SSEL_1;       // Use sampling timer, set mode  +ADC12SSEL_3
  ADC12MCTL0  =  ADC12SREF_0;               //0~3V
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  
 
  
}



#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  _DINT();
    while((__even_in_range(ADC12IV,34)) != 6);
    /*
    adc_sum +=  ADC12MEM0;
    sum_index++;
    if(sum_index>2) 
    {
      adc_ave[adc_num++]=adc_sum/3;
      sum_index=0;
      adc_sum=0;
    }
    */
    adc_ave[adc_num++]=ADC12MEM0;
    if( adc_num>200) 
    {
      adc_num=0;
      
      unsigned int k=0;
      
      for(unsigned int i=0;i<200;i++)
      {
        if(adc_ave[k]<adc_ave[i])
           k=i;
      }
      adc_value=adc_ave[k];
     adc=adc_value/4095.0*3.3;
     if(adc>0.4)
     {
       Concentration=1.771e-11*exp(10.79*adc) + 10.02*exp(1.127*adc);
       Concentration=Concentration*2.2;
     }
     else 
       Concentration=0.0;
     ADC12CTL0 &= ~ADC12ENC;
     SendData();
     BAC=Concentration*0.00420947;
     sprintf(ConString,"%.3f",BAC);
     
     if(BAC>0.4) RelayOff;
     else RelayOn;
     Send_sound(ConString,BAC);
     
     acquire=0;
    }
    
    
   _EINT();
    
}
