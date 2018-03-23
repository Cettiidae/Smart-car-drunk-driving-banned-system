#include "lib.h"


void MP3_Init(void)
{
  //P6REN |= BIT1 +BIT2 + BIT3;
  MP3PortDIR |= BIT1 + BIT2 + BIT3;
  MP3PortOUT |= BIT1  + BIT3;
  MP3PortOUT&=~BIT2;
 // MP3_Play();
}

void MP3_LastSong(void)
{

  MP3LastOFF;
  delay_ms(200);
  MP3LastON;
}

void MP3_NextSong(void)
{

  MP3NextOFF;
  delay_ms(200);
  MP3NextON;
  delay_ms(200);
  MP3NextOFF;
}

void MP3_Play(void)
{
  MP3PlayON;
  delay_ms(100);
  MP3PlayOFF;

}