#include <REG52.H>

unsigned char code LedChar[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                              0x7F,0x6F};

sbit ENLED=P1^3;
sbit key=P2^7;

void main()
{  
   unsigned char i=0x00;

   P0=0x00;
   P1=0x00;
   ENLED=1;
   P2=0xFF;

   while(1)
   { 
     i=(i<<1)|~key;
	 if(i==0xFF)
	 {
	  ENLED=1;
	  P0=LedChar[8];
	 }
	 else if(i==0x00)
	 {
	   //ENLED=0; 
	   ENLED=1;
	   P0=LedChar[3];
	 }
	 else
	 {
	   ENLED=0;
	 }	 
   }
}
