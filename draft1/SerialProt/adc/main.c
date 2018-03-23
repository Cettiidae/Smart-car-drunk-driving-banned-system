
#include "msp430f5529.h"




//u16 adc_0[50];
unsigned int adc_sum;
unsigned int adc_num;
unsigned int sum_index;
unsigned int adc_ave[150];
unsigned int adc_value;
double adc;



void main(void)
{
   // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
 P6SEL |= 0x01;               
  ADC12CTL0   = ADC12ON + ADC12SHT0_8 +ADC12MSC;//+ ADC12REFON + ADC12REF2_5V
  ADC12CTL1   = ADC12SHP +ADC12CONSEQ_2 ; //  + ADC12SSEL_2
 // ADC12MCTL0  = ADC12SREF_1;  
  ADC12IE    |= 0X01;             
  ADC12CTL0  |= ADC12ENC;   
  ADC12CTL0 |= ADC12SC;                     // Start conversion  
  _EINT();
  
  LPM0;
  
}



#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  
    while((__even_in_range(ADC12IV,34)) != 6);
    adc_sum +=  ADC12MEM0;
    sum_index++;
    if(sum_index>9) 
    {
      adc_ave[adc_num++]=adc_sum/10;
      sum_index=0;
    }
    
    if( ( adc_ave[adc_num-1]<adc_ave[6]) && (adc_num>11) )
    {
      
      unsigned int k=0;
      
      for(unsigned int i=0;i<adc_num;i++)
      {
        if(adc_ave[k]<adc_ave[i])
           k=i;
      }
      adc_value=adc_ave[k];
     adc=adc_value/4095*3.3;
     
     ADC12CTL0 &= ~ADC12ENC;
     //SendData();
    }
    
    
  // _DINT();
    
}

