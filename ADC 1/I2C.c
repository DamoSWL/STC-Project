#include <REG52.H>
#include<intrins.h>
#include<confi.h>
#include<I2C.h>




void Delay()
{
   unsigned char i=4;
   while(i--)
   {
     _nop_();
   }
}
void I2Cstart()
{
   SCL=1;
   SDA=1;
   Delay();
   SDA=0;
   Delay();
   SCL=0;
}

void I2Cstop()
{
  
  SCL=0;
  SDA=0;
  Delay();
  SCL=1;
  Delay();
  SDA=1;
  Delay();

}

bit I2Cwrite(unsigned char cd)
{
  unsigned char mask;
  unsigned char temp;
  bit ack;

  for(mask=0x80;mask!=0x00;mask>>=1)
  {
    temp=mask&cd;
	if(temp==0)
	  SDA=0;
	else
	  SDA=1;
	Delay();
	SCL=1;
	Delay();
	SCL=0;  
  }
  SDA=1;
  Delay();
  SCL=1;
  ack=SDA;
  Delay();
  SCL=0;
  return ack;
}

unsigned char I2CreadNAK()
{
  unsigned char db=0;
  unsigned char mask;

  SDA=1;
  for(mask=0x80;mask!=0;mask>>=1)
  {
    Delay();
	SCL=1;
	if(SDA==1)
	{
	  db|=mask;
	}
	else
	{}
	Delay();
	SCL=0;	  
  }
  SDA=1;
  Delay();
  SCL=1;
  Delay();
  SCL=0;
  return db;
}

unsigned char I2CreadACK()
{
  unsigned char db=0;
  unsigned char mask;

  SDA=1;
  for(mask=0x80;mask!=0;mask>>=1)
  {
    Delay();
	SCL=1;
	if(SDA==1)
	{
	  db|=mask;
	}
	else
	{}
	Delay();
	SCL=0;	  
  }
  SDA=0;
  Delay();
  SCL=1;
  Delay();
  SCL=0;
  return db;
}

