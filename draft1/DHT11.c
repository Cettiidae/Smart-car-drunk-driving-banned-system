//****************************************************************//
//	   DHT21ʹ�÷��� 
//��Ƭ�� AT89S52 �� STC89C52RC 
//����   ���ڷ�����ʪ������ ���� 11.0592M ������ 9600 
//Ӳ��   P2.0��ΪͨѶ������DHT11,DHT11�ĵ�Դ�͵����ӵ�Ƭ���ĵ�Դ�͵أ���Ƭ�����ڼ�MAX232���ӵ��� 
//��˾  �������    
//****************************************************************//

#include "lib.h"




//----------------------------------------------//
//----------------������--------------------//
//----------------------------------------------//
unsigned char  U8FLAG,k;
unsigned char  U8count,U8temp;
unsigned char  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
unsigned char  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
unsigned char  U8comdata;
//unsigned char  outdata[5];  //���巢�͵��ֽ���	   
unsigned char  indata[5];
unsigned char  count ;//count_r=0
//unsigned char  str[5]={"RS232"};
unsigned int U16temp1,U16temp2; 
unsigned char RH_data_H;

/*
SendData(unsigned char *a)
{
	outdata[0] = a[0]; 
	outdata[1] = a[1];
	outdata[2] = a[2];
	outdata[3] = a[3];
	outdata[4] = a[4];
	count = 1;
	SBUF=outdata[0];
}
*/


	
void  COM(void)
{
  unsigned char i;
  for(i=0;i<8;i++)	   
  {
    U8FLAG=2;	
    while((!(P2IN & 0x01))&&U8FLAG++);
    delay_us(30);
    U8temp=0;
    if(P2IN&0x01)U8temp=1;
    U8FLAG=2;
    while((P2IN&0x01)&&U8FLAG++);
    	  
    if(U8FLAG==1)break; //��ʱ������forѭ��	
    //�ж�����λ��0����1	 
                       
    // ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
                     
     U8comdata<<=1;
     U8comdata|=U8temp;        //0
    }//rof
	   
}

	//--------------------------------
	//-----ʪ�ȶ�ȡ�ӳ��� ------------
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

void RH(void)
{
  P2DIR |= BIT0;
  P2OUT=0x00;//��������18ms 
  delay_ms(18);
  P2OUT=0x01;
  //������������������ ������ʱ20us
  delay_us(30);
  //������Ϊ���� �жϴӻ���Ӧ�ź� 
  P2OUT=0x01;
  //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
  P2DIR &= 0xfe;
  if(!(P2IN&0x01))		 //T !	  
  {
    U8FLAG=2;
    //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
    while((!(P2IN&0x01))&&U8FLAG++);
    U8FLAG=2;
    //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
    while(((P2IN&0x01))&&U8FLAG++);
    //���ݽ���״̬		 
    COM();
    U8RH_data_H_temp=U8comdata;
    COM();
    U8RH_data_L_temp=U8comdata;
    COM();
    U8T_data_H_temp=U8comdata;
    COM();
    U8T_data_L_temp=U8comdata;
    COM();
    U8checkdata_temp=U8comdata;
    
    P2DIR |= BIT0;
    P2OUT|=0x01;
    //����У�� 
             
    U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
    if(U8temp==U8checkdata_temp)
    {
    U8RH_data_H=U8RH_data_H_temp;
    U8RH_data_L=U8RH_data_L_temp;
    U8T_data_H=U8T_data_H_temp;
    U8T_data_L=U8T_data_L_temp;
    U8checkdata=U8checkdata_temp;
    }
  }
}


unsigned int my_abs(int difference)
{
  unsigned int result;
  if(difference>0) result= difference;
  else result = -difference;
  return result;
}
/*	
//----------------------------------------------
//main()��������:  AT89C51  11.0592MHz 	���ڷ� 
//����ʪ������,������ 9600 
//----------------------------------------------
        //��ʱ100US��12M����)
	while(1)
	{  

	   //------------------------
	   //������ʪ�ȶ�ȡ�ӳ��� 
	   RH();
	   //������ʾ���� 
	   //--------------------------

	   str[0]=U8RH_data_H;
	   str[1]=U8RH_data_L;
	   str[2]=U8T_data_H;
	   str[3]=U8T_data_L;
	   str[4]=U8checkdata;
	   SendData(str) ;  //���͵�����  
	   //��ȡģ���������ڲ���С�� 2S 
	   Delay(20000);
	}//elihw
	
}// main

void RSINTR() interrupt 4 using 2
{
	unsigned char InPut3;
	if(TI==1) //�����ж�	  
	{
		TI=0;
		if(count!=5) //������5λ����	 
		{
			SBUF= outdata[count];
			count++;
		}
	}

	if(RI==1)	 //�����ж�		  
	{	
		InPut3=SBUF;
		indata[count_r]=InPut3;
		count_r++;
		RI=0;								 
		if (count_r==5)//������4λ���� 
		{
		//���ݽ�����ϴ���
			count_r=0;
		str[0]=indata[0];
		 str[1]=indata[1];
		   str[2]=indata[2];
			 str[3]=indata[3];
				 str[4]=indata[4];
				 P0=0;
		}
	}
}
*/
