#include<reg52.h>

unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};

sbit key4=P2^7;
sbit ENLED=P1^3;

unsigned char Keysta=1;


void configure();	 

void main()
{
  unsigned char backup=1;
  unsigned char num=7;

  configure();

  while(1)
  {	  
      
      if(Keysta!=backup)
	   {
	     if(backup==0)
		 {
		   P0=LedChar[num];
		 }
		 if(backup==1)
		 {
		   P0=LedChar[num-3];
		 }
		 backup=Keysta;
	   }  
  }
}  


void configure()
{
  EA=1;
  ET1=1;
  P1=0x00;
  ENLED=1;
  P0=0x00;
  P2=0xF0;
  TMOD=0x10;
  TH1=0xF7;		//1ms
  TL1=0x00;
  TR1=1;
}

void InterruptTimer1() interrupt 3
{
  static unsigned char keybuf=0x00;
  TH1=0xF7;
  TL1=0x00;
  
  keybuf=(keybuf<<1)|key4;
	switch(keybuf)
	{
	  case 0xFF:Keysta=1;break;
	  case 0x00:Keysta=0;break;
	  default:break;
	}
}

