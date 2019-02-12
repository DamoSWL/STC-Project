#include<LCD_main.h>

bit flag=0;

unsigned char i=0;
unsigned char txt[30];




void main()
{
 
  EN=0;
  EA=1;
  configure_UART(9600);	
  LCD_initial();


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
  TR1=1;
}

void interrupt_UART() interrupt 4
{
  if(RI)
  {
    RI=0;
	txt[i]=SBUF;
	SBUF=txt[i];
	i++;
	if(txt[i-1]=='.')
	{
	  flag=1;
	  i=0;
	}
	
  }
   if(TI)
     TI=0;
}



