#include <REG52.H>

unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};

sbit ENLED=P1^3;
unsigned int i=0;
unsigned char j=0;
//unsigned char LedBuf=0x00;

void configure();

void main()
{
  configure();


  while(1)
  { 
	  P0=LedChar[j];	
  }	
}

void configure()
{
  EA=1;
  ET0=1;
  P1=0x00;
  ENLED=1;
  P0=0x00;
  TMOD=0x01;
  TH0=0xF7;		
  TL0=0x00;
  TR0=1;
}  	 

void InterruptTimer0() interrupt 1
{
  TH0=0xF7;
  TL0=0x00;
  i++;
  if(i>=40)
  {
    i=0;
    j++;
	if(j>=10)
	{
	  j=0;
	}
  }
  //P0=LedBuf;
}
