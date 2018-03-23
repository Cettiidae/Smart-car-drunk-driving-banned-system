#include"lib.h"

unsigned char Time[4]={1,7,1,7};
unsigned char Date[6]={1,5,0,5,1,0};
unsigned char second,minute=14,hour=13;
unsigned char day=10,month=5,year=15;
unsigned char sj=0x00;
/* *************************************************************************
*                    ����������ϵ�ṹ��ص�һЩ����
**************************************************************************/

unsigned char ping[12]={31,28,31,30,31,30,31,31,30,31,30,31};
unsigned char rn[12]={31,29,31,30,31,30,31,31,30,31,30,31};
unsigned char yue[2]={30,29};
unsigned int year2,month2,day2;
unsigned int yy1,mm1,dd1;

void WRITE_DS1302(unsigned char add,unsigned char dat)
{
  unsigned char i;
  DS_IO_O;
  DS_RST_L;
  DS_SCLK_L;
  DS_RST_H;
  for(i=0;i<8;i++)
  {
    DS_SCLK_L;
    if(add & 0x01) DS_IO_H;
    else DS_IO_L;
    add=add>>1;
    DS_SCLK_H;
  }
  for(i=0;i<8;i++)
  {
    DS_SCLK_L;
    if(dat & 0x01) DS_IO_H;
    else  DS_IO_L;
    dat=dat>>1;
    DS_SCLK_H;
  }
  DS_RST_L;
}
unsigned char READ_DS1302(unsigned char add)
{
  unsigned char i;
  unsigned char dat;
  unsigned char temp;
  DS_IO_O;
  DS_RST_L;
  DS_SCLK_L;
  DS_RST_H;
  for(i=0;i<8;i++)
  {
    DS_SCLK_L;
    if(add & 0x01) DS_IO_H;
    else  DS_IO_L;
    add=add>>1;
    DS_SCLK_H;
  }
  DS_IO_I;
  for(i=0;i<8;i++)
  {
    dat=dat>>1;
    DS_SCLK_L;
    if(DS_IO_Q) dat|=0x80;
    DS_SCLK_H;   
  }
  DS_IO_O;
  DS_RST_L;
  temp=dat/16;
  dat=dat%16+temp*10;
  return dat;
}
void DS1302_INIT(void)
{
  DS_RST_O;
  DS_SCLK_O;
  DS_IO_O;
  DS_RST_L;
  DS_SCLK_L;
  DS_RST_H;
  DS_RST_L;
  
}
/**********������ǰ��ʱ�����ڳ�ʼ�������µı���************/
void timeread(unsigned char *TIME,unsigned char *DAT)
{
  TIME[0]=hour/10;
  TIME[1]=hour%10;
  TIME[2]=minute/10;
  TIME[3]=minute%10;
 // TIME[4]=week;
  DAT[0]=year/10;
  DAT[1]=year%10;
  DAT[2]=month/10;
  DAT[3]=month%10;
  DAT[4]=day/10;
  DAT[5]=day%10;
}
/**********�����ú��ʱ������д��DS1302***********/
void timeset(unsigned char ye,unsigned char mo,unsigned char da,unsigned char ho,unsigned char mu)
{
 /* unsigned char mu,ho,da,mo,ye,we;
  ho=TIME[0]*16+TIME[1];
  mu=TIME[2]*16+TIME[3];
  ye=DAT[0]*16+DAT[1];
  mo=DAT[2]*16+DAT[3];
  da=DAT[4]*16+DAT[5];*/
 // we=TIME[4];
  DS_RST_O;
  DS_SCLK_O;
  DS_IO_O;
  DS_RST_L;
  DS_SCLK_L;
  DS_RST_H;
  WRITE_DS1302(WRITE_PROTECT,0x00);
  WRITE_DS1302(WRITE_SECOND,0x80);
  WRITE_DS1302(WRITE_MINUTE,mu);
  WRITE_DS1302(WRITE_HOUR,ho);
  WRITE_DS1302(WRITE_DAY,da);
  WRITE_DS1302(WRITE_MONTH,mo);
  WRITE_DS1302(WRITE_YEAR,ye);
 // WRITE_DS1302(WRITE_WEEK,we);
  WRITE_DS1302(WRITE_SECOND,0x00);
  WRITE_DS1302(WRITE_PROTECT,0x80);
  DS_RST_L;
}




/* *************************************************************************
*    ������������ת�����Ĺ�ϵ��,����μ�������
*     <<��Ƭ���γ����ʵ�����>>(���ɵȱ���,2004����µ�һ��)
**************************************************************************/ 


/*

const unsigned int table[101] = {0x4693,
0xDA9B, 0x052B, 0x2A5B, 0xDAAE, 0x756A, 0xDDD5, 0x0BA4, 0x5B49, 0xDD53, 0x0A95,
0x452D, 0xD55D, 0x9AB5, 0xDBAA, 0x05D2, 0x6DA5, 0xEE8A, 0x0D4A, 0x4C95, 0xDA9E,
0x0556, 0x2AB5, 0xDADA, 0x66D2, 0xD765, 0x0725, 0x564B, 0xD657, 0x0CAB, 0x355A,
0xD56E, 0xBB69, 0xDF52, 0x0B52, 0x5B25, 0xDD2B, 0x0A4B, 0x54AB, 0xD2BB, 0x05AD,
0x2B6A, 0xDDAA, 0x7D92, 0xDEA5, 0x0D25, 0x5A55, 0xEA4D, 0x04B6, 0x35B5, 0xE6D2,
0x8EC9, 0xDF92, 0x0E92, 0x6D26, 0xE516, 0x0A57, 0x44D6, 0xE365, 0x0755, 0x3749,
0xD74B, 0x7693, 0xDAAB, 0x052B, 0x5A5B, 0xDABA, 0x056A, 0x4B65, 0xDBAA, 0x8B4A,
0xDD95, 0x0A95, 0x652D, 0xD56D, 0x0AB5, 0x55AA, 0xE5C5, 0x0DA5, 0x3D4A, 0xDE4D,
0x7C96, 0xDCCE, 0x0556, 0x5AB5, 0xEAD2, 0x06D2, 0x5EA5, 0xD72A, 0x868B, 0xD697,
0x04AB, 0x655B, 0xE556, 0x0B6A, 0x4752, 0xDB95, 0x0B25, 0x2A8B, 0xDA4F, 0x04AB};




void lunar_calendar(unsigned char yy,unsigned char mm,unsigned char dd)
{

  unsigned char leap;
  unsigned int  i,j,days1,days2,x;

   days1 = (yy) * 365 + ((yy+2000-1997)>>2) + (mm-1)*30 + dd;
   if ((mm >2) && ((yy & 3) == 0) && ((yy+2000) != 2100))
       days1 ++;
   switch(mm)
    {
     case 3:  days1--;
       break;
     case 11:
     case 12: days1 ++;
     case 9:
     case 10: days1 ++;
     case 8:  days1 ++;
     case 2:
     case 6:
     case 7:  days1 ++;
       break;
    }   //------days from 1999-12-31

   days1 -=35;
   days2=0;
   leap=0xFF;
   for (i=0; i<=2100; i++)
    {
      x=table[i];
      for (j=0; j<12; j++)
      {
        days2 += 29 + (x & 1);
        if (days2 >= days1)    break;
        if (j==leap)
        {
          days2 = days2 + 16 + (table[i] >> 12);
          if (days2 >= days1)
          {  
            j |= 0x80;
            break;
          }
        }  
        x >>= 1;
      }

      if (days2 >= days1)
          break;
     
      leap = x-1;
    }

   x = 29 + (x & 1) -(days2-days1);
   
   year2=i+2000;  //output result
   month2=j+1;
   day2=x;
}

unsigned char ZellerWeek(unsigned char DAT[]) //���գ�Zeller����ʽ
 {

     int y = DAT[0]*10+DAT[1];
     int m = DAT[2]*10+DAT[3];
     int d = DAT[4]*10+DAT[5];
 
     if(m <= 2) //��С��2���·ݽ�������
     {
         year--;
         m = m + 12;
     }
 
     
     int w = (y + y / 4 + 20 / 4 - 2 * 20 + (13 * (m + 1) / 5) + d - 1) % 7;
     if(w < 0) //�����������Ǹ��������
         w += 7;
     unsigned char ww=0;
     while(w--) ww++;
     
       DS_RST_O;//д��ds1302
       DS_SCLK_O;
       DS_IO_O;
       DS_RST_L;
       DS_SCLK_L;
       DS_RST_H;
       WRITE_DS1302(WRITE_PROTECT,0x00);
       WRITE_DS1302(WRITE_WEEK,ww); 
       WRITE_DS1302(WRITE_PROTECT,0x80);
       DS_RST_L;
     return ww;
 }

*/


/************************************************************************
*                            End Of File
************************************************************************/
/*******��ȡ��ǰʱ�������*******/
void GET_TIME(void)
{
 // unsigned char day_last;
 // day_last=day;
  second=READ_DS1302(READ_SECOND);
  minute=READ_DS1302(READ_MINUTE);
  hour=READ_DS1302(READ_HOUR);
  day=READ_DS1302(READ_DAY);
  month=READ_DS1302(READ_MONTH);
  year=READ_DS1302(READ_YEAR);
  //week=READ_DS1302(READ_WEEK);
  //if(day_last!=day)  lunar_calendar(year,month,day);
  
 


}

