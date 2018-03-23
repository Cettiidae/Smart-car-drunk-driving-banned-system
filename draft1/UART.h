 //MSP430F552x Demo - USCI_A0, 115200 UART Echo ISR, DCO SMCLK
//
//   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
//   USCI_A0 RX interrupt triggers TX Echo.
//   Baud rate divider with 1048576hz = 1048576/115200 = ~9.1 (009h|01h)
//   ACLK = REFO = ~32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   See User Guide for baud rate divider table
//
//                 MSP430F552x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |     P3.3/UCA0TXD|------------>
//            |                 | 115200 - 8N1
//            |     P3.4/UCA0RXD|<------------
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#ifndef __UART_H
#define __UART_H


extern char buffer[];
extern unsigned int length;
extern double Concentration;
extern double BAC;
extern char TxCharString[20];
extern char ConString[15];
extern char rx_data[40];                 //串口就收数据伪缓存数组
extern double counter;                   //计录数据
extern unsigned char rx_index;          //每收到一次'\n'置一次1开始存储数据，数据存储后置0
extern unsigned char num_index;         //参数计数
extern unsigned char first_flag;        //第一个字母
extern unsigned char second_flag;       //第二个字母
extern unsigned char debug_flag;

extern unsigned char last_humi;
extern unsigned char humi;
extern unsigned char last_temp;
extern unsigned char temp;
extern unsigned char acquire;

void UART_Init(void);
void PortTxData(char *s,unsigned int len);//发送字符串 s[]中的字符，len为字符串长度

void SendData(void);

#endif