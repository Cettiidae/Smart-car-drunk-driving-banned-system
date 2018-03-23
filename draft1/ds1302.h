#ifndef __DS1302_H
#define __DS1302_H


#define  DS_SCLK_H   P3OUT|=BIT5
#define  DS_IO_H     P3OUT|=BIT6
#define  DS_RST_H    P3OUT|=BIT7
#define  DS_SCLK_L   P3OUT&=~BIT5
#define  DS_IO_L     P3OUT&=~BIT6
#define  DS_RST_L    P3OUT&=~BIT7
#define  DS_SCLK_O   P3DIR|=BIT5
#define  DS_IO_O     P3DIR|=BIT6
#define  DS_RST_O    P3DIR|=BIT7
#define  DS_SCLK_I   P3DIR&=~BIT5
#define  DS_IO_I     P3DIR&=~BIT6
#define  DS_RST_I    P3DIR&=~BIT7
#define  DS_IO_Q     P3IN & 0x40

#define  WRITE_SECOND    0X80
#define  READ_SECOND     0x81
#define  WRITE_MINUTE    0x82
#define  READ_MINUTE     0x83
#define  WRITE_HOUR      0x84
#define  READ_HOUR       0x85
#define  WRITE_DAY       0x86
#define  READ_DAY        0x87
#define  WRITE_MONTH     0x88
#define  READ_MONTH      0x89
#define  WRITE_YEAR      0x8c
#define  READ_YEAR       0x8d
#define  WRITE_WEEK      0x8a
#define  READ_WEEK       0x8b
#define  WRITE_PROTECT   0x8e
#define  READ_PROTECT    0x8f

extern unsigned char Time[4];
extern unsigned char Date[6];
extern unsigned char second,minute,hour;
extern unsigned char day,month,year;

extern unsigned char ping[12];
extern unsigned char rn[12];
extern unsigned char yue[2];
extern unsigned int year2,month2,day2;
extern unsigned int yy1,mm1,dd1;
extern unsigned char sj;


void WRITE_DS1302(unsigned char add,unsigned char dat);
unsigned char READ_DS1302(unsigned char add);
void DS1302_INIT(void);
void GET_TIME(void);
void timeset(unsigned char ye,unsigned char mo,unsigned char da,unsigned char ho,unsigned char mu);//将设置后的时间日期写入DS1302
//void SetTime(void);


#endif