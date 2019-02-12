#include<reg52.h>

unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};
unsigned char LedBuff[]={0x00,0x00,0x00};

void main()
{
 
  unsigned int cnt=0;
  unsigned int sec=0;
  unsigned char i=0;
 
  P1=0x00;
  TMOD=0x01;
  TH0=0xF8;									
  TL0=0xCD;
  TR0=1;

  while(1)
  {
    
    if(TF0==1)
	{

	  TF0=0;
	  TH0=0xF8;									
      TL0=0xCD;
	  cnt++;
	  
      if(cnt>=500)
	  {
	    cnt=0;
	    sec++;
		
		LedBuff[0]=LedChar[sec%10];
		LedBuff[1]=LedChar[sec/10%10];
		LedBuff[2]=LedChar[sec/100%10];
		if(sec>=1000)
		{
		  sec=0;
		}	    
	  }
	  P0=0x00;
	  switch(i)
	  {
	    case 0:P1=0x08;P0=LedBuff[0];i++;break;
		case 1:P1=0x04;P0=LedBuff[1];i++;break;
		case 2:P1=0x02;P0=LedBuff[2];i=0;break;
		default:break;
	  }	
	}
  }
}