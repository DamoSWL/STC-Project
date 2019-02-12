#include <REG52.H>

#define LCD_DB P0
sbit EN=P1^2;
sbit RS=P1^1;
sbit RW=P1^0;

void LCD_initial();
void LCD_showstr(unsigned char x,unsigned char y,unsigned char *str);



void main()
{
  unsigned char *str1="Capacitance is";
  unsigned char *str2="       uF";
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                                                                                                                                          
  EN=0;
  LCD_initial();
  
  LCD_showstr(0,0,str1);
  LCD_showstr(0,1,str2);
  while(1);
  
  
}

void LCD_ready()
{
  unsigned char sta;

  LCD_DB=0xFF;
  RS=0;
  RW=1;
  do
  {
    EN=1;
	sta=LCD_DB;
	EN=0;
  } while(sta&0x80);  
}

void LCD_writecmd(unsigned char cmd)
{
   LCD_ready();
   RS=0;
   RW=0;
   LCD_DB=cmd;
   EN=1;
   EN=0;
}

void LCD_writedat(unsigned char dat)
{
  LCD_ready();
  RS=1;
  RW=0;
  LCD_DB=dat;
  EN=1;
  EN=0;
}

void LCD_writeadd(unsigned char x,unsigned char y)
{
  unsigned char add;
  if(y==0)
    add=0x00+x;
  else
    add=0x40+x;
  LCD_writecmd(add|0x80);
}

void LCD_showstr(unsigned char x,unsigned char y,unsigned char *str)
{
   LCD_writeadd(x,y);
   while(*str!='\0')
   {
     LCD_writedat(*str++);
   }
}

void LCD_initial()
{
  LCD_writecmd(0x38);
  LCD_writecmd(0x0C);
  LCD_writecmd(0x06);
  LCD_writecmd(0x01);
}











