#include "lib.h"


char buffer[]="Hello!You are so smart!";
unsigned int length;
double Concentration;
double BAC;
char TxCharString[20];
char ConString[15];

char rx_data[30];                 //串口就收数据伪缓存数组
double counter;                   //计录数据
unsigned char rx_index;          //每收到一次'\n'置一次1开始存储数据，数据存储后置0
unsigned char num_index;         //参数计数
unsigned char first_flag;        //第一个字母
unsigned char second_flag;       //第二个字母

unsigned char last_humi;
unsigned char humi;
unsigned char last_temp;
unsigned char temp;
unsigned char acquire;

void UART_Init(void)
{
  P3SEL |= BIT3+BIT4;                       // P3.3,4 = USCI_A0 TXD/RXD
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 9;                              // 1MHz 115200 (see User's Guide)
  UCA0BR1 = 0;                              // 1MHz 115200
  UCA0MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

void PortTxData(char *s,unsigned int len)
{
  for(int i=0;i<len;i++)
  {
    UCA0TXBUF = s[i];
   // while(!(UCA0IFG & UCTXIFG));
     delay_us(3000);
  }
  UCA0TXBUF = '~';
  delay_ms(10);

}

void SendData(void)
{
 // AdcValue=ADC7991_GetData();
 // RH();//读取温度湿度
  
  GET_TIME();//读取时间
  
  
  
  length = sprintf( TxCharString,"%s%d","pN",number++);//序号    
  PortTxData(TxCharString,length);  
  
  length = sprintf( TxCharString,"%s%.3f","pC",Concentration);//浓度    
  PortTxData(TxCharString,length);
  
  length = sprintf( TxCharString,"%s%d","pT",temp);//温度     U8T_data_H
  PortTxData(TxCharString,length);
  
  delay_ms(1000);
  
  length = sprintf( TxCharString,"%s%d","pH",humi);//湿度      U8RH_data_H
  PortTxData(TxCharString,length);
  
  length = sprintf( TxCharString,"%s%d","dY",year);//年
  PortTxData(TxCharString,length);
  length = sprintf( TxCharString,"%s%d","dM",month);//月
  PortTxData(TxCharString,length);
  length = sprintf( TxCharString,"%s%d","dD",day);//日
  PortTxData(TxCharString,length);
  length = sprintf( TxCharString,"%s%d","tH",minute);//时
  PortTxData(TxCharString,length);
  length = sprintf( TxCharString,"%s%d","tM",hour);//分
  PortTxData(TxCharString,length);
  
  /*
  length = sprintf(TxCharString,"%s%d","ADC:",AdcValue);
  PortTxData(TxCharString,length);                                             //"ADC:xxxxd"
  
  length = sprintf( TxCharString,"%s%.2f","Consistence:",Consistence);
  PortTxData(TxCharString,length);                                       //"Consisrence:xxx.xxf"
  
  length = sprintf( TxCharString,"%s%d%s%d%s%d%s%d","Wet",U8RH_data_H,".",U8RH_data_L," Tem",U8T_data_H,".",U8T_data_L);
  PortTxData(TxCharString,length); 
  
  length = sprintf( TxCharString,"%s%d%s%d%s%d%s%d%s%d","Date:",year,"-",month,"-",day," ",hour,":",minute);
  PortTxData(TxCharString,length);
  
  PortTxData(TxCharString,0);
  */
  if(number>100) number=0;
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
    num_index=0;
    first_flag=0;
    rx_index=0;
  }
  
  else if( (first_flag=='d') && (UCA0RXBUF=='M') ) 
  {
    second_flag=2;                                    //
    num_index=0;
    first_flag=0;
    rx_index=0;
  }
  
  else if( (first_flag=='d') && (UCA0RXBUF=='D') ) 
  {
    second_flag=3;                                    //
    num_index=0;
    first_flag=0;
    rx_index=0;
  }
  
  else if( (first_flag=='t') && (UCA0RXBUF=='H') ) 
  {
    second_flag=4;                                    //
    num_index=0;
    first_flag=0;
    rx_index=0;
  }
  
  else if( (first_flag=='t') && (UCA0RXBUF=='M') ) 
  {
    second_flag=5;                                    //
    num_index=0;
    first_flag=0;
    rx_index=0;
  }

  while(first_flag==13)
  {
    counter = atoi(rx_data);//把字符串转换为double型数据
    switch(second_flag)
    {
    case 1:year=counter;break;
    case 2:month=counter;break;
    case 3:day=counter;break;
    case 4:hour=counter;break;
    case 5:minute=counter;SetTime();break;
    default:break;
    }
    
    
  
  }

}