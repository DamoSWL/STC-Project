#include <REG52.H>

void configure(int baud);
void confiLED();

unsigned char s=0;
unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};

void main()
{
  configure(9600);
  confiLED();
  while(1)
  {
    if(s>9)
	{
	  s=0;
	}
    P0=LedChar[s];
  }
}
 
void confiLED()
{
  P1=0x08;
  P0=0x00;  
}

void configure(int baud)
{
  SCON=0x50;
  TMOD=0x20;
  TH1=256-(11059200/12/32)/baud;
  TL1=TH1;
  EA=1;
  ET1=0;
  ES=1;
  TR1=1;
}

void interruptUART() interrupt 4
{
  if(RI)
  {
    RI=0;
	s++;
	SBUF=SBUF;
  }	
  if(TI)
    TI=0;
}

