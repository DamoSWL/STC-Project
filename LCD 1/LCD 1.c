#include<LCD_1.h>

void LCD_ready()
{
  unsigned char sta;
  DB=0xFF;
  RS=0;
  RW=1;
  do
  {
    EN=1;
	sta=DB;
	EN=0;
  } while(sta&0x80); 
  DB=0x00;
}

void LCD_writecmd(unsigned char cmd)
{
   LCD_ready();
   RS=0;
   RW=0;
   DB=cmd;
   EN=1;
   EN=0;
}

void LCD_writedat(unsigned char dat)
{
  LCD_ready();
  RS=1;
  RW=0;
  DB=dat;
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
  LCD_writecmd(0x0F);
  LCD_writecmd(0x06);
  LCD_writecmd(0x01);
}






