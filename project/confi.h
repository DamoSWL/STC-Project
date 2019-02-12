#include <reg52.h>
#include <intrins.h>

#define LCD_DB P0

sbit RS=P1^3;
sbit RW=P1^4;
sbit LCD_EN=P1^5;
sbit SCL=P3^7;
sbit SDA=P3^6;
sbit DIG1=P1^7;
sbit DIG2=P1^6;
sbit KEY1=P3^4;
sbit KEY2=P3^5;
sbit T2TRIG=P1^0;
sbit RST_555=P1^2;