#include<reg52.h>

unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};

sbit keyout=P2^0;
sbit key1=P2^4;
sbit key2=P2^5;
sbit key3=P2^6;
sbit key4=P2^7;
sbit ENLED=P1^3;

unsigned char Keysta[]={1,1,1,1};

void configure();	 

void main()
{
  unsigned char backup[]={1,1,1,1};
  unsigned char i=0;

  configure();

  while(1)
  {
     for(i=0;i<=3;i++)
	 {
	   if(Keysta[i]!=backup[i])
	   {
	     if(backup[i]==0)
		 {
		   P0=LedChar[i*2];
		 }
		 backup[i]=Keysta[i]; 
	   }
	 }
  }  
}

void configure()
{
  EA=1;
  ET0=1;
  P1=0x00;
  ENLED=1;
  P0=0x00;
  P2=0xF0;
  TMOD=0x01;
  TH0=0xF8;		//1ms
  TL0=0xCD;
  TR0=1;
}

void InterruptTimer0() interrupt 1
{
  static unsigned char keybuf[]={0xFF,0xFF,0xFF,0xFF};
  unsigned char i=0;

  TH0=0xF8;
  TL0=0xCD;
  keybuf[0]=(keybuf[0]<<1)|key1;
  keybuf[1]=(keybuf[1]<<1)|key2;
  keybuf[2]=(keybuf[2]<<1)|key3;
  keybuf[3]=(keybuf[3]<<1)|key4;
  for(i=0;i<=3;i++)
  {
    if((keybuf[i]&0xFF)==0xFF)
	{
	  Keysta[i]=1;
	}
	else if((keybuf[i]&0xFF)==0x00)
	{
	  Keysta[i]=0;
	}
	else 
	{
	}
  }

}