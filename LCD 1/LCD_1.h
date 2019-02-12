#include <REG52.H>
#include <intrins.h>
#define DB P0
sbit EN=P1^2;
sbit RS=P1^1;
sbit RW=P1^0;

void LCD_initial();
void LCD_showstr(unsigned char x,unsigned char y,unsigned char *str);
void Delay();
