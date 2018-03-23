#ifndef __DHT11_H
#define __DHT11_H

#define DHT_DataIn P2IN;
//****************************************************************//
//	   DHT21使用范例 
//单片机 AT89S52 或 STC89C52RC 
//功能   串口发送温湿度数据 晶振 11.0592M 波特率 9600 
//硬件   P2.0口为通讯口连接DHT11,DHT11的电源和地连接单片机的电源和地，单片机串口加MAX232连接电脑 
//公司  雁凌电子    
//****************************************************************//



#define   Data_0_time    4

//----------------------------------------------//
//----------------IO口定义区--------------------//
//----------------------------------------------//
//  P2_0  = P2^0 ;

//----------------------------------------------//
//----------------定义区--------------------//
//----------------------------------------------//
extern unsigned char  U8FLAG,k;
extern unsigned char  U8count,U8temp;
extern unsigned char  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
extern unsigned char  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
extern unsigned char  U8comdata;
//extern unsigned char  outdata[5];  //定义发送的字节数	   
extern unsigned char  indata[5];
extern unsigned char  count;//count_r=0
//extern unsigned char  str[5]={"RS232"};
extern unsigned int   U16temp1,U16temp2;
extern unsigned char RH_data_H;

	
void  COM(void);
void RH(void);//-----湿度读取子程序 ------------
              //--------------------------------
              //----以下变量均为全局变量--------
              //----温度高8位== U8T_data_H------
              //----温度低8位== U8T_data_L------
              //----湿度高8位== U8RH_data_H-----
              //----湿度低8位== U8RH_data_L-----
              //----校验 8位 == U8checkdata-----
              //----调用相关子程序如下----------
              //---- Delay();, Delay_10us();,COM(); 
              //--------------------------------
unsigned int my_abs(int difference);

#endif