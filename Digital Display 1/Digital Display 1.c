#include<reg52.h>

sbit EN=P1^3;
unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};

void main()
{
  unsigned char cnt=0;
  unsigned int i=0;

  TMOD=0x01;
  TH0=0x4C;
  TL0=0x00;
  TR0=1;
  EN=1;

  while(1)
  {
    if(TF0==1)
	{
	  TF0=0;
	  TH0=0x4C;
	  TL0=0x00;
	  cnt++;
	  if(cnt>=20)
	  {
	    P0=LedChar[i];
		i++;
		cnt=0;
		if(i>=10)
		{
		  i=0;
		}
	  }
	}
  }


}
