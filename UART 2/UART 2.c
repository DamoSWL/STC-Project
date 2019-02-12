#include <REG52.H>

unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};
unsigned char code LedChar_Dot[]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,
                                0xFF,0xEF};
unsigned char LedBuff[]={0x00,0x00,0x00};

void configure_uart(int baud);
void configure_timer0(int t); //input 2ms

unsigned char num_decimal=0;
unsigned char num_integer=0;
unsigned char rxt;
unsigned char Thigh;
unsigned char Tlow;
bit running=1;
bit flag=0;


void main()
{
  EA=1;
  configure_timer0(2);
  configure_uart(9600);
  while(1)
  {
    if(flag)
	{
	 TI=1;
	}
  } 
}

void configure_timer0(int t)
{
  unsigned long temp;

  temp=11059200/12;
  temp=(temp*t)/1000;
  temp=65536-temp;
  temp=temp+12;
  Thigh=(unsigned char)(temp>>8);
  Tlow=(unsigned char)temp;
  TH0=Thigh;
  TL0=Tlow;
  TMOD&=0xF0;
  TMOD|=0x01;
  ET0=1;
  TR0=1;
}

void configure_uart(int baud)
{
  unsigned long temp;

  SCON=0x50;
  TMOD&=0x0F;
  TMOD|=0x20;
  temp=11059200/(24*16);
  temp=temp/baud;
  TH1=256-(unsigned char)temp;
  TL1=TH1;
  ET1=0;
  ES=1;
  TR1=1;
}

void counting()
{
  if(running)
  {
    num_decimal++;
    if(num_decimal>=100)
    {
      num_decimal=0;
	  num_integer++;
	  if(num_integer>=10)
      {
	    num_integer=0;
		flag=1;
	  }
    }
	 LedBuff[2]=LedChar[num_decimal%10];
     LedBuff[1]=LedChar[(num_decimal/10)%10];
     LedBuff[0]=LedChar_Dot[num_integer];
	
  }
  else
  {}
}

void LedScan()
{
  static unsigned char i=3;
						
  P0=0x00;
  P1&=0xF0;
  P1|=0x01;
  P1=P1<<i;
  P0=LedBuff[i-1];
  i--;
  if(i<=0)
    i=3;
}


void interrupt_timer0() interrupt 1
{
    static unsigned char i=0;    

  	TH0=Thigh;
	TL0=Tlow;
	LedScan();
	i++;
	if(i>=5)
	{
	  i=0;
	  counting();	  
	}
}

void interrupt_uart() interrupt 4
{
  if(RI)
  {
    RI=0;
    rxt=SBUF;
	if(rxt=='s')
	  {
	    running=1;
		SBUF=0x31;
	   }
	else if(rxt=='r')
	  {
	    running=0;
		SBUF=0x30;
	  }
	else
	{}
   }
  if(TI)
  {
    TI=0;
	if(flag)
	{
	  flag=0;
	  SBUF=0x77;
	}
  }
}








