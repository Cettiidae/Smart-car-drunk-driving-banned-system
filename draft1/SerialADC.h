#ifndef __SERIALADC_H
#define __SERIALADC_H

/*********************************
	ADS7991引脚设置；
*********************************/ 
#define SDA_Rx ((P1IN&0x08)>>3)
#define SDA_In P1DIR &=~BIT3
#define SDA_Out P1OUT |= BIT3
#define SDA_0 P1OUT &=~BIT3
#define SDA_1 P1OUT |= BIT3
#define SCL_Out P1OUT |= BIT2
#define SCL_0 P1OUT &=~BIT2
#define SCL_1 P1OUT |= BIT2


extern unsigned int AdcValue;
extern double VolValue;


void SerialADC_Init(void);
void ADS7991_Init(void);
void ADS7991_Start(void);  //开始信号
void ADS7991_Stop(void);   //停止
void ADS7991_Respons(void);  //应答
void write_byte(unsigned char date);
unsigned char read_byte(void);
void write_add(unsigned char byte_add,unsigned char byte_cannel);
void respons_master(void);						//主机应答信号
unsigned int read_add(unsigned char byte_add);
unsigned int ADC7991_GetData(void);

#endif