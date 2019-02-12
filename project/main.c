#define _MAIN_C
#include <confi.h>
#include <LCD.h>
#include <I2C.h>
#include <main.h>

unsigned char code LedChar[]={0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x09};
unsigned char code LedChar_Dot[]={0x02,0x9E,0x24,0x0C,0x98,0x48,0x40,0x1E,0x00,0x08};
unsigned char LedBuff[2]={0x02,0x03};
unsigned char Key_Down[2]={0,0};
unsigned char Keybuff[2]={0,0};
unsigned char T0RH,T0RL;
unsigned char Keyflag=0;
unsigned char volt;
unsigned long cnt=0;
unsigned long cap=0;
unsigned char str[6];

	   
void main()
{
  T2TRIG=1;
  T2EX=1;
  RST_555=0;
  LCD_EN=0;
  DIG1=0;
  DIG2=0;
  KEY1=1;
  KEY2=1;
  EA=1;

  configure_timer0(2);
  configure_timer2();
  configure_ADC();
  LCD_initial();
  

  while(1)
  {
    Is_Key_Down();
	if(Keyflag)
	{
	  Key_Action();
	}
  }
}


void Is_Key_Down()
{
   unsigned char i=0;
   for(i=0;i<2;i++)
   {
     if(Keybuff[i]!=Key_Down[i])
	 {
	   if(Keybuff[i]!=0)
	   {
	     Keyflag=i+1;
	   }
	  Keybuff[i]=Key_Down[i];
	 }
   }  
}


void Key_Action()
{
  if(Keyflag==2)
  {
     LedBuff[0]=0x02;
	 LedBuff[1]=0x03;
	 LCD_clear();	 
  }
  else if(Keyflag==1)
  {
    do
	{
	  I2C_start();
	  if(I2C_write(0x91))
	    break;
	  I2C_stop();
	}while(1);
    RST_555=1;
	do
	{
	  T2TRIG=0;
	  T2TRIG=1;
	}while(~T2EX);
	EXEN2=1;
	TR2=1;
	do
	{
	  volt=I2C_readACK();
	  volt=(volt*40)/255;
      LedBuff[0]=LedChar_Dot[volt/10];
      LedBuff[1]=LedChar[volt%10];
	}while(T2EX);
	I2C_readNAK();
	I2C_stop();
  }	  
  else
  {} 
  Keyflag=0;
}


void LED_Scan()
{
  static unsigned char i=1;
  P2=0xFF;
  switch(i)
  {
    case 1: 
	  DIG1=0;
	  DIG2=1;
	  P2=LedBuff[0];
	  i++;
	  break;
	case 2:
	  DIG2=0;
	  DIG1=1;
	  P2=LedBuff[1];
	  i--;
	  break;
	default:break;	  
  }
}

void Key_Scan()
{
  unsigned char i=0;
  static unsigned char keybuf[2]={0xFF,0xFF};
  
  keybuf[0]=(keybuf[0]<<1)|KEY1;
  keybuf[1]=(keybuf[1]<<1)|KEY2;
  for(i=0;i<2;i++)
  {
    if(keybuf[i]==0x00)
	  Key_Down[i]=1;
	else if(keybuf[i]==0xFF)
	  Key_Down[i]=0;
	else
	{}
  }
}

void configure_ADC()
{
   do
	{
	  I2C_start();
	  if(I2C_write(0x90))
	    break;
	  I2C_stop();
	}while(1);
	I2C_write(0x00);
	I2C_stop();	
}
   
void configure_timer0(int t)
{
  unsigned int temp;

  TMOD=0x01;
  temp=(11059200/12*t)/1000;
  temp=65536-temp;
  temp+=10;
  T0RH=(unsigned char)(temp>>8);
  T0RL=(unsigned char)temp;
  TH0=T0RH;
  TL0=T0RL;
  ET0=1;
  TR0=1;
}

void configure_timer2()
{
  RCLK=0;
  TCLK=0;
  EXEN2=0;
  TR2=0;
  C_T2=0;
  CP_RL2=1;
  ET2=1;
  TH2=0;
  TL2=0;
  RCAP2H=0;
  RCAP2L=0;
}

void interrupt_timer0() interrupt 1
{
  TH0=T0RH;
  TL0=T0RL;
  LED_Scan();
  Key_Scan();
}

void interrupt_timer2() interrupt 5
{
  unsigned int temp=0;

  if(TF2)
  {
    TF2=0;
	cnt=cnt+65536;
  }
  if(EXF2)
  {
    EXF2=0;
    RST_555=0;
    EXEN2=0;
    TR2=0;
	TH2=0;
    TL2=0;
	temp=RCAP2H;
	temp<<=8;
	temp+=RCAP2L;
	cnt+=temp;
	Convert(cnt);
	cnt=0;
	LCD_showstr(0,0,"the capacitance");
	LCD_showstr(0,1,"is: ");
	LCD_showstr(4,1,str);   
  }
}

void Convert(unsigned long cnt)
{
  if(cnt<34)
  {
     cap=30*cnt;
	 str[0]=cap/100+'0';
	 str[1]=(cap/10)%10+'0';
	 str[2]=cap%10+'0';
	 str[3]='p';
	 str[4]='F';
	 str[5]='\0';
  }
  else if(cnt>=34&&cnt<33334)
  {
     cap=(3*cnt)/100;
     str[0]=cap/100+'0';
	 str[1]=(cap/10)%10+'0';
	 str[2]=cap%10+'0';
	 str[3]='n';
	 str[4]='F';
	 str[5]='\0';
  }
  else if(cnt>=33334&&cnt<33333333)
  {
     cap=(cnt*3)/100000;
	 str[0]=cap/100+'0';
	 str[1]=(cap/10)%10+'0';
	 str[2]=cap%10+'0';
	 str[3]='u';
	 str[4]='F';
	 str[5]='\0';
  }
  else
  {}
}
