//**************************************************//
//          |     P3.4/UCA0TXD|------------>        //
//          |                 | 9600 - 8N1          //
//          |     P3.5/UCA0RXD|<------------        //
//**************************************************//

#include "msp430f5438a.h"
#include "stdio.h"
#include "stdlib.h"
#define CPU_F ((double)1000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

int length;                       //需发送的字符串长度
char TxCharString[30];                     //储存发送的字符串
char something[20];
char index;
unsigned char number;
unsigned char year=15;
unsigned char month=5;
unsigned char day=10;
unsigned char hour=17;
unsigned char minute=39;
char rx_data[20];
unsigned char rx_index;
unsigned char first_flag;
unsigned char second_flag;
double counter;
void PortTxData(char *s,unsigned int len)
{
  for(int i=0;i<len;i++)
  {
    UCA0TXBUF = s[i];
   // while(!(UCA0IFG & UCTXIFG));
     delay_us(3000);
  }
  UCA0TXBUF = 126;
  delay_us(3000);

}



void SendData(void)
{
/*
  length = sprintf( TxCharString,"%s%d","pN",number++);//序号    
  PortTxData(TxCharString,length);  
  
  length = sprintf( TxCharString,"%s%.3f","pC",0.218);//浓度    
  PortTxData(TxCharString,length);
  
  length = sprintf( TxCharString,"%s%d","pT",28);//温度     U8T_data_H
  PortTxData(TxCharString,length);
  
  delay_ms(1000);
  
  length = sprintf( TxCharString,"%s%d","pH",54);//湿度      U8RH_data_H
  PortTxData(TxCharString,length);
  */
  length = sprintf( TxCharString,"%s%d","dY20",year);//年
  PortTxData(TxCharString,length);
  length = sprintf( TxCharString,"%s%d","dM",month);//月
  PortTxData(TxCharString,length);
  length = sprintf( TxCharString,"%s%d","dD",day);//日
  PortTxData(TxCharString,length);
  length = sprintf( TxCharString,"%s%d","tH",hour);//时
  PortTxData(TxCharString,length);
  length = sprintf( TxCharString,"%s%d","tM",minute);//分
  PortTxData(TxCharString,length);
  
  if(number>100) number=0;
}

void main(void)
{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL = 0x30;                              // P3.4,5 = USCI_A0 TXD/RXD
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32kHz/9600=3.41 (see User's Guide)
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = UCBRS_3+UCBRF_0;               // Modulation UCBRSx=3, UCBRFx=0
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE ;                         // Enable USCI_A0 RX interrupt
  

  SendData();
  
  _EINT();
  //LPM0;
  while(1);

}


#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    rx_data[rx_index++] = UCA0RXBUF ;        //把接收的数据存入缓存数组 
         if(UCA0RXBUF=='d')      first_flag='d';
    else if(UCA0RXBUF=='t')      first_flag='t';
    else if(UCA0RXBUF=='~')       first_flag=13; 
    break;
  case 4:
       
  break;                             // Vector 4 - TXIFG
  default: break;
  }
  
  
  
  
  //在判断出第一个字母后，
  if( (first_flag=='d') && (UCA0RXBUF=='Y') ) 
  {
    second_flag=1;                                    //
   // num_index=0;
    first_flag=0;
    rx_index=0;
  }
  
  else if( (first_flag=='d') && (UCA0RXBUF=='M') ) 
  {
    second_flag=2;                                    //
  //  num_index=0;
    first_flag=0;
    rx_index=0;
  }
  
  else if( (first_flag=='d') && (UCA0RXBUF=='D') ) 
  {
    second_flag=3;                                    //
 //   num_index=0;
    first_flag=0;
    rx_index=0;
  }
  
  else if( (first_flag=='t') && (UCA0RXBUF=='H') ) 
  {
    second_flag=4;                                    //
 //   num_index=0;
    first_flag=0;
    rx_index=0;
  }
  
  else if( (first_flag=='t') && (UCA0RXBUF=='M') ) 
  {
    second_flag=5;                                    //
 //   num_index=0;
    first_flag=0;
    rx_index=0;
  }

  while(first_flag==13)
  {
    counter = atof(rx_data);//把字符串转换为double型数据
    switch(second_flag)
    {
    case 1:year=counter+1;break;
    case 2:month=counter+1;break;
    case 3:day=counter+1;break;
    case 4:hour=counter+1;break;
    case 5:minute=counter+1;
           SendData();break;
    default:break;
    }
    second_flag=0;//add
    first_flag=0;
  
  }
  if(rx_index>19) rx_index=0;

}