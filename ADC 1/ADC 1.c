#include <REG52.H>
#include<confi.h>
#include<I2C.h>
#include<PCF.h>

void configure(unsigned int t);
void Tostring(unsigned char dat);

unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};
unsigned char code LedChar_Dot[]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,
                                0xFF,0xEF};
unsigned char LedBuff[]={0x00,0x00,0x00};

unsigned char T0H;
unsigned char T0L;
unsigned char dat;
bit flag=0;



void main()
{
  P0=0x00;
  P1=0x00;
  EA=1;
  configure(2);
  while(1)
  {
    if(flag)
	{
	  flag=0;
	  dat=ADCread();
	  Tostring(dat);
	}
  }
}


void configure(unsigned int t)
{
  unsigned long temp;


  temp=11059200/12;
  temp=(temp*t)/1000;
  temp=65536-temp;
  temp=temp+12;
  T0H=(unsigned char)(temp>>8);
  T0L=(unsigned char)temp;
  TMOD=0x01;
  TH0=T0H;
  TL0=T0L;
  ET0=1;
  TR0=1;
}

void Tostring(unsigned char dat)
{
  unsigned char one;
  unsigned char two;
  unsigned char thr;

  dat=(dat*250)/255;
  thr=dat%10;
  two=(dat/10)%10;
  one=dat/100;
  LedBuff[0]=LedChar_Dot[one];
  LedBuff[1]=LedChar[two];
  LedBuff[2]=LedChar[thr];
}

void LedScan()
{
  static unsigned char i=3;

  P0=0x00;
  switch(i)
  {
    case 3:Led3=1;Led2=0;Led1=0;P0=LedBuff[2];i--;break;
	case 2:Led2=1;Led1=0;Led3=0;P0=LedBuff[1];i--;break;
	case 1:Led1=1;Led2=0;Led3=0;P0=LedBuff[0];i=3;break;
	default:break;
  }
}

void interrupt_Timer0() interrupt 1
{
   static unsigned char cnt=0;

   TH0=T0H;
   TL0=T0L;
   LedScan();
   cnt++;
   if(cnt>=50)
   {
     cnt=0;
	 flag=1;
   }

}
  
  








  
