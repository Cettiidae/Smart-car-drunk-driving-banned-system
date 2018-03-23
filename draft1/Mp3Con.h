#ifndef __MP3CON_H
#define __MP3CON_H

#define MP3PortDIR P6DIR
#define MP3PortOUT P6OUT
#define MP3NextON  P6OUT&=~BIT1
#define MP3NextOFF P6OUT|=BIT1
#define MP3PlayOFF P6OUT&=~BIT2 //置0
#define MP3PlayON P6OUT|=BIT2 //置1 （你用这个脚控制继电器）0开1断
#define MP3LastON P6OUT&=~BIT3
#define MP3LastOFF P6OUT|=BIT3


void MP3_Init(void);
void MP3_LastSong(void);
void MP3_NextSong(void);
void MP3_Play(void);


#endif