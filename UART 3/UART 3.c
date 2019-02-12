#include <REG52.H>

unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};
unsigned char LedBuff[]={0x3F,0x3F,0x3F};

bit flag=0;
bit display=0;
unsigned char mov=1;
signed char i=2;
unsigned char rxd;
unsigned char T0RH;
unsigned char T0RL;

void configure_timer0(int t);
void configure_uart(int baud);
void command1();
void command2();

void main()
{
  EA=1;
  configure_uart(9600);
  configure_timer0(2);
  P1=0x08;
  P0=LedBuff[i];
  while(1)
  {
    if(flag)
	{
	  flag=0;
	  command2();
	  if(display!=1)
	  {
       command1();
	  }
	  else
	  {}
	}
  }
}


void configure_timer0(int t)
{
  unsigned long temp;

  temp=11059200/12;
  temp=(temp*t)/1000;
  temp-=12;
  temp=65536-temp;
  T0RH=(unsigned char)(temp>>8);
  T0RL=(unsigned char)temp;
  TMOD&=0xF0;
  TMOD|=0x01;
  TH0=T0RH;
  TL0=T0RL;
  TR0=0;
  ET0=0;
}

void configure_uart(int baud)
{
  SCON=0x50;
  TMOD&=0x0F;
  TMOD|=0x20;
  TH1=256-(11059200/32/12)/baud;
  TL1=TH1;
  ET1=0;
  ES=1;
  TR1=1;
}

void right_mov()
{
    unsigned char temp;     
  
    P0=0x00;
  	P1=P1<<mov;
	temp=(P1<<4);
	if((temp&0xFF)==0x00)
    {
	  P1=0x02;
	}
	i++;
	if(i>=3)
	{
	  i=0;
	}
	P0=LedBuff[i];
}

void left_mov()
{
  unsigned char temp;

  P0=0x00;
  P1=P1>>mov;
  temp=P1&0x0E;
  if((temp&0xFF)==0x00)
  {
    P1=0x08;
  }
  i--;
  if(i<0)		  
  {
    i=2;
  }
  P0=LedBuff[i];
}


void command1()
{
  switch(rxd)
  {
    case 0x30:LedBuff[i]=LedChar[0];P0=LedBuff[i];break;
	case 0x31:LedBuff[i]=LedChar[1];P0=LedBuff[i];break;
	case 0x32:LedBuff[i]=LedChar[2];P0=LedBuff[i];break;
	case 0x33:LedBuff[i]=LedChar[3];P0=LedBuff[i];break;
	case 0x34:LedBuff[i]=LedChar[4];P0=LedBuff[i];break;
	case 0x35:LedBuff[i]=LedChar[5];P0=LedBuff[i];break;
	case 0x36:LedBuff[i]=LedChar[6];P0=LedBuff[i];break;
	case 0x37:LedBuff[i]=LedChar[7];P0=LedBuff[i];break;
	case 0x38:LedBuff[i]=LedChar[8];P0=LedBuff[i];break;
	case 0x39:LedBuff[i]=LedChar[9];P0=LedBuff[i];break;
	case 'a':left_mov();break; 
	case 's':right_mov();break;
	default:break;
  } 
}

void command2()
{
  switch(rxd)
  {
    case 'd':TR0=1;ET0=1;display=1;break;
	case 'f':TR0=0;ET0=0;display=0;P0=0x00;P1=0x08;P0=LedBuff[2];i=2;break;
	default:break;
  }
}

void LedScan()
{ 
  static unsigned char j=0;

  P0=0x00;
  P1=0x08>>j;
  P0=LedBuff[2-j];
  j++;
  if(j>=3)
    j=0;
  
}

void interrupt_timer0() interrupt 1
{
  TH0=T0RH;
  TL0=T0RL;
  LedScan();
}

void interruptUART() interrupt 4
{
  if(RI)
  {
    RI=0;
	flag=1;
    rxd=SBUF;
	SBUF=rxd;
  }
  if(TI)
    TI=0;
}






