#define _LCD_C
#include <confi.h>
#include <LCD.h>

 void LCD_ready()
{
  unsigned char sta;

  LCD_DB=0xFF;
  RS=0;
  RW=1;
  do
  {
    LCD_EN=1;
	sta=LCD_DB;
	LCD_EN=0;
  } while(sta&0x80);  
}

void LCD_writecmd(unsigned char cmd)
{
   LCD_ready();
   RS=0;
   RW=0;
   LCD_DB=cmd;
   LCD_EN=1;
   LCD_EN=0;
}

void LCD_writedat(unsigned char dat)
{
  LCD_ready();
  RS=1;
  RW=0;
  LCD_DB=dat;
  LCD_EN=1;
  LCD_EN=0;
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

void LCD_clear()
{
 LCD_writecmd(0x01);
}

void LCD_initial()
{
  LCD_writecmd(0x38);
  LCD_writecmd(0x0C);
  LCD_writecmd(0x06);
  LCD_writecmd(0x01);
}
