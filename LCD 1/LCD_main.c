#include<LCD_main.h>

bit flag=0;
unsigned char i=0;
unsigned char txt[9];

void main()
{
  P1=0x00;
  DB=0x00;
  txt[8]='\0';
  LCD_initial();
  configure_UART(9600);
  while(1)
  {
    if(flag)
	{
	  flag=~flag;
	  LCD_showstr(0,0,txt);
	}
  }
}


void configure_UART(unsigned int baud)
{
  SCON=0x50;
  TMOD=0x20;
  TH1=256-(11059200/12/32)/baud;
  TL1=TH1;
  ET1=0;
  ES=1;
  TR1=0;
}

void interrupt_UART() interrupt 4
{
  if(RI)
  {
    RI=0;
	txt[i]=SBUF;
	SBUF=txt[i];
	i++;
	if(i>=8)
	{
	   i=0;
	   flag=1;
	}
	
  }
   if(TI)
     TI=0;
}
