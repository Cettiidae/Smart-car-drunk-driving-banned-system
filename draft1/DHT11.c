//****************************************************************//
//	   DHT21使用范例 
//单片机 AT89S52 或 STC89C52RC 
//功能   串口发送温湿度数据 晶振 11.0592M 波特率 9600 
//硬件   P2.0口为通讯口连接DHT11,DHT11的电源和地连接单片机的电源和地，单片机串口加MAX232连接电脑 
//公司  雁凌电子    
//****************************************************************//

#include "lib.h"




//----------------------------------------------//
//----------------定义区--------------------//
//----------------------------------------------//
unsigned char  U8FLAG,k;
unsigned char  U8count,U8temp;
unsigned char  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
unsigned char  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
unsigned char  U8comdata;
//unsigned char  outdata[5];  //定义发送的字节数	   
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
    	  
    if(U8FLAG==1)break; //超时则跳出for循环	
    //判断数据位是0还是1	 
                       
    // 如果高电平高过预定0高电平值则数据位为 1 
                     
     U8comdata<<=1;
     U8comdata|=U8temp;        //0
    }//rof
	   
}

	//--------------------------------
	//-----湿度读取子程序 ------------
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

void RH(void)
{
  P2DIR |= BIT0;
  P2OUT=0x00;//主机拉低18ms 
  delay_ms(18);
  P2OUT=0x01;
  //总线由上拉电阻拉高 主机延时20us
  delay_us(30);
  //主机设为输入 判断从机响应信号 
  P2OUT=0x01;
  //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
  P2DIR &= 0xfe;
  if(!(P2IN&0x01))		 //T !	  
  {
    U8FLAG=2;
    //判断从机是否发出 80us 的低电平响应信号是否结束	 
    while((!(P2IN&0x01))&&U8FLAG++);
    U8FLAG=2;
    //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
    while(((P2IN&0x01))&&U8FLAG++);
    //数据接收状态		 
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
    //数据校验 
             
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
//main()功能描述:  AT89C51  11.0592MHz 	串口发 
//送温湿度数据,波特率 9600 
//----------------------------------------------
        //延时100US（12M晶振)
	while(1)
	{  

	   //------------------------
	   //调用温湿度读取子程序 
	   RH();
	   //串口显示程序 
	   //--------------------------

	   str[0]=U8RH_data_H;
	   str[1]=U8RH_data_L;
	   str[2]=U8T_data_H;
	   str[3]=U8T_data_L;
	   str[4]=U8checkdata;
	   SendData(str) ;  //发送到串口  
	   //读取模块数据周期不易小于 2S 
	   Delay(20000);
	}//elihw
	
}// main

void RSINTR() interrupt 4 using 2
{
	unsigned char InPut3;
	if(TI==1) //发送中断	  
	{
		TI=0;
		if(count!=5) //发送完5位数据	 
		{
			SBUF= outdata[count];
			count++;
		}
	}

	if(RI==1)	 //接收中断		  
	{	
		InPut3=SBUF;
		indata[count_r]=InPut3;
		count_r++;
		RI=0;								 
		if (count_r==5)//接收完4位数据 
		{
		//数据接收完毕处理。
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
