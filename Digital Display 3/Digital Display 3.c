#include<reg52.h>

unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};
unsigned char code LedChar_Dot[]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,
                                0xFF,0xEF};
unsigned char LedBuff[]={0x00,0x3F,0x3F};

sbit Led1=P1^1;
sbit Led2=P1^2;
sbit Led3=P1^3;

unsigned char cnt=0;
unsigned char i=0;

void main()
{
  unsigned char t1=0;
  unsigned char t2=0;
  unsigned char t3=0;
  Led1=1;
  Led2=1;
  Led3=1;
  TMOD=0x01;	   //Timer1
  TH0=0xF7;		  //2.5ms
  TL0=0x00;
  EA=1;
  ET0=1;
  TR0=1;

  while(1)
  {
    if(cnt>=40)	  //0.1s
	{
	  cnt=0;
	  t1++;
	  if(t1>=10)
	  {
	     t1=0; 
		 t2++;
		 if(t2>=10)
		 {
		   t2=0;
		   t3++;
		   if(t3>=6)
		   {
		     t3=0;
		   }
		   if(t3==0)
		   {
		     LedBuff[0]=0x00;
		   }
		   else
		   {
		     LedBuff[0]=LedChar[t3];
		   }
		 }
		 LedBuff[1]=LedChar_Dot[t2];
	  }
	  LedBuff[2]=LedChar[t1];
	}	
  }
}

void InterruptTimer0() interrupt 1
{
  TH0=0xF7;
  TL0=0x00;
  cnt++;
  P0=0x00;
  switch(i)
  {
    case 0:Led3=1;Led1=0;Led2=0;P0=LedBuff[2];i++;break;
	case 1:Led2=1;Led1=0;Led3=0;P0=LedBuff[1];i++;break;
	case 2:Led1=1;Led2=0;Led3=0;P0=LedBuff[0];i=0;break;
	default:break;
  }
}
