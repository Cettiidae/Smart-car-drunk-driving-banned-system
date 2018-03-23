
#include <msp430f5529.h>
#include "lib.h"
#include "string.h"

unsigned char start=0;
unsigned char open=0;
void main(void)
{
  WDTCTL=WDT_ADLY_1000;              //定时器模式，250ms中断一次
  SFRIE1|=WDTIE;
  //WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  MP3_Init();
  UART_Init();
  RelayControl_Init();
  KeyInit();
  wt588d_Init();
//  SerialADC_Init();
  ADC12_Init();
  DS1302_INIT();//初始化DS1302
  //timeset(Time,Date);
 // timeset(year,month,day,hour,minute);;//读取一次时间
  RH();
  last_humi=U8RH_data_H;

  //Send_threelines(0xE7);
  Send_threelines(11);
  //Send_sound("0.12",0.3);
  __bis_SR_register(LPM0_bits +GIE);       // Enter LPM0, interrupts enabled
  

}

#pragma vector=WDT_VECTOR
__interrupt void wdt_time(void)
{
 _DINT();
  
 if(start<6) start++;
 if(start==5) 
 {
   Send_threelines(12);
   open=1;
 }
 
  RH();
  
  if((open)&&( (U8RH_data_H-last_humi)>2 ))
  {
    ADC12CTL0 |= ADC12ENC;                    // Enable conversions
    ADC12CTL0 |= ADC12SC;                     // Start conversion
    acquire=1;
  }
  if((acquire)&&(U8RH_data_H>last_humi))
  {
    humi=U8RH_data_H;
    temp=U8T_data_H;
  }
  
  else if(acquire)
  {
    temp=last_temp;
    humi=last_humi; 
  }
  last_temp=U8T_data_H;
  last_humi=U8RH_data_H;
 _EINT();
}

