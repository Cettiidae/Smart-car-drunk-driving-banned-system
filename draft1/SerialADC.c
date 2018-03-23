
#include "lib.h"


//unsigned char time50ms_count=0;
//unsigned char flag=0;

unsigned int AdcValue;
double VolValue;


void SerialADC_Init(void)
{
  SDA_Out;
  SCL_Out;
}

void ADS7991_Init(void)
{
	SDA_1;
	delay_us(1);
	SCL_1;
	delay_us(1);
}

void ADS7991_Start(void)  //开始信号
{	
	SDA_1;
	delay_us(1);
	SCL_1;
	delay_us(1);
	SDA_0;
	delay_us(1);
        SCL_0;
        delay_us(1);
        SCL_1;
        delay_us(1);
        SDA_1;
        delay_us(1);
        SCL_0;
        delay_us(1);
        SCL_1;
        delay_us(1);
        SDA_0;
        delay_us(1);
        SCL_0;
        delay_us(1);
        SCL_1;
        delay_us(1);
        SDA_1;
        delay_us(1);
        SCL_0;
        delay_us(1);
        SCL_1;
        delay_us(1);
        SDA_0;
        delay_us(1);
        SCL_0;
        delay_us(1);
        SCL_1;
        delay_us(1);
        SCL_0;
        delay_us(1);
        SCL_1;
        delay_us(1);
        SDA_1;
        delay_us(1);
        SCL_0;
        delay_us(1);
        SCL_1;
        delay_us(1);
        SCL_0;
        delay_us(1);
}

void ADS7991_Stop(void)   //停止
{
	SDA_0;
	delay_us(1);
	SCL_1;
	delay_us(1);
	SDA_1;
	delay_us(1);
}

void ADS7991_Respons(void)  //应答
{
	unsigned char i=0;

	SCL_1;
	delay_us(1);
        SDA_In;
	while((SDA_Rx)&&(i<250))i++;
        SDA_Out;
	SCL_0;
	delay_us(1);
}

void write_byte(unsigned char date)
{
	unsigned char i,temp;

	temp=date;

	for(i=0;i<8;i++)
	{
		temp=temp<<1;
                
		SCL_0;
	        delay_us(1); //将写入的数据给CY
                if(temp&0x80) SDA_1;
                else SDA_0;//SDA=CY	
		delay_us(1);
		SCL_1;
		delay_us(1);
	}
	SCL_0;
	delay_us(1);
	SDA_1;
	delay_us(1);
}

unsigned char read_byte(void)
{
	unsigned char i,k;

	SCL_0;
	delay_us(1);
	SDA_1;
	delay_us(1);
        SDA_In;
	for(i=0;i<8;i++)
	{
		SCL_1;
		delay_us(1);
		k=(k<<1)|SDA_Rx;
		SCL_0;
		delay_us(1);	
	}
        SDA_Out;
	return k;																					
}

void write_add(unsigned char byte_add,unsigned char byte_cannel)
{
	ADS7991_Start();	  //发送起始信号；
	write_byte(byte_add);  //发送寻址从器件的寻址地址(0x52)；
	ADS7991_Respons();
	write_byte(byte_cannel);  //操作地址；
	ADS7991_Respons();
	ADS7991_Stop();
}
void respons_master(void)						//主机应答信号
{
  SCL_0;
  delay_us(1);
  SDA_0;
  delay_us(1);
  SCL_1;
  delay_us(1);
}

unsigned int read_add(unsigned char byte_add)
{
  unsigned int date_H,date_L;
  unsigned int value;

  ADS7991_Start();
  write_byte(byte_add);
  ADS7991_Respons();
  date_H=read_byte();	//读高8为数据;
  respons_master();						//主机应答信号

  
  date_L=read_byte();//读低8为数据;
  ADS7991_Stop();
  date_H&=0x0f;
  value=date_H<<8|date_L;
  return value;
}

unsigned int ADC7991_GetData(void)
{
  //float result=0.f;
  //unsigned int n;
  unsigned int m;
  
  ADS7991_Init();
  write_add(0x52,0x10);
  m=read_add(0x53);
 // m*=5;
  //result=m/4.096;	 //实际的电压值放大1000倍；
  //n=(unsigned int)result;
  return m;
} 

