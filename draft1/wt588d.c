
#include "lib.h"


void wt588d_Init(void)
{
  P1DIR |= BIT2 + BIT3 + BIT4 +BIT5;
  
}


void Send_threelines(unsigned char addr) //三线发码子程序 
    {
      unsigned char i;
      RST_0;
      delay_ms(8);
      RST_1;
      delay_ms(20);
      CS_0;  
      delay_ms(5); 
      for(i=0;i<8;i++)  
       {
         SCL_0;  
         if(addr & 1)SDA_1;  
         else SDA_0;  

         addr>>=1;  
         delay_us(400);  /* 300us */  
         SCL_1;  
         delay_us(400);   
         }  
        CS_1; 
     } 
 
 void Send_sound(char *s,double x)
 {  
   unsigned char i;
    __delay_cycles(1000000);
    Send_threelines(13);
    __delay_cycles(3000000);
    for(i=0;i<5;i++)
    {
      if( (s[i]>47)&&(s[i]<58) )
      {
        Send_threelines(s[i]-48);
         __delay_cycles(500000);
      }
      else if(s[i]==46)
      {
        Send_threelines(10);
         __delay_cycles(500000);
      }
        
    }
     Send_threelines(14);
      __delay_cycles(1000000);
       if(x<0.2)Send_threelines(15); 
      else if(x>=0.8)Send_threelines(17);   
      else Send_threelines(16);
      //__delay_cycles(10000000);
    
 }
   

