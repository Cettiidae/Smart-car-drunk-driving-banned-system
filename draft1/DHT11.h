#ifndef __DHT11_H
#define __DHT11_H

#define DHT_DataIn P2IN;
//****************************************************************//
//	   DHT21ʹ�÷��� 
//��Ƭ�� AT89S52 �� STC89C52RC 
//����   ���ڷ�����ʪ������ ���� 11.0592M ������ 9600 
//Ӳ��   P2.0��ΪͨѶ������DHT11,DHT11�ĵ�Դ�͵����ӵ�Ƭ���ĵ�Դ�͵أ���Ƭ�����ڼ�MAX232���ӵ��� 
//��˾  �������    
//****************************************************************//



#define   Data_0_time    4

//----------------------------------------------//
//----------------IO�ڶ�����--------------------//
//----------------------------------------------//
//  P2_0  = P2^0 ;

//----------------------------------------------//
//----------------������--------------------//
//----------------------------------------------//
extern unsigned char  U8FLAG,k;
extern unsigned char  U8count,U8temp;
extern unsigned char  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
extern unsigned char  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
extern unsigned char  U8comdata;
//extern unsigned char  outdata[5];  //���巢�͵��ֽ���	   
extern unsigned char  indata[5];
extern unsigned char  count;//count_r=0
//extern unsigned char  str[5]={"RS232"};
extern unsigned int   U16temp1,U16temp2;
extern unsigned char RH_data_H;

	
void  COM(void);
void RH(void);//-----ʪ�ȶ�ȡ�ӳ��� ------------
              //--------------------------------
              //----���±�����Ϊȫ�ֱ���--------
              //----�¶ȸ�8λ== U8T_data_H------
              //----�¶ȵ�8λ== U8T_data_L------
              //----ʪ�ȸ�8λ== U8RH_data_H-----
              //----ʪ�ȵ�8λ== U8RH_data_L-----
              //----У�� 8λ == U8checkdata-----
              //----��������ӳ�������----------
              //---- Delay();, Delay_10us();,COM(); 
              //--------------------------------
unsigned int my_abs(int difference);

#endif