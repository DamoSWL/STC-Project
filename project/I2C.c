#define _I2C_C
#include <confi.h>
#include <I2C.h>

void Delay()
{
   unsigned char i=4;
   while(i--)
   {
     _nop_();
   }
}
void I2C_start()
{
   SCL=1;
   SDA=1;
   Delay();
   SDA=0;
   Delay();
   SCL=0;
}

void I2C_stop()
{
  
  SCL=0;
  SDA=0;
  Delay();
  SCL=1;
  Delay();
  SDA=1;
  Delay();

}

bit I2C_write(unsigned char dat)
{
  unsigned char mask;
  unsigned char temp;
  bit ack;

  for(mask=0x80;mask!=0x00;mask>>=1)
  {
    temp=mask&dat;
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
  return (~ack);
}

unsigned char I2C_readNAK()
{
  unsigned char dat=0;
  unsigned char mask;

  SDA=1;
  for(mask=0x80;mask!=0;mask>>=1)
  {
    Delay();
	SCL=1;
	if(SDA==1)
	{
	  dat|=mask;
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
  return dat;
}

unsigned char I2C_readACK()
{
  unsigned char dat=0;
  unsigned char mask;

  SDA=1;
  for(mask=0x80;mask!=0;mask>>=1)
  {
    Delay();
	SCL=1;
	if(SDA==1)
	{
	  dat|=mask;
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
  return dat;
}
