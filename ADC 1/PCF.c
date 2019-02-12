#include <REG52.H>
#include<confi.h>
#include<I2C.h>
#include<PCF.h>

unsigned char ADCread()
{
  unsigned char dat;
  while(1)
  {
    I2Cstart();
    if(!I2Cwrite(0x90))
	  break;
	I2Cstop();
  }
  I2Cwrite(0x00);
  I2Cstart();
  I2Cwrite(0x91);
  I2CreadACK();
  dat=I2CreadNAK();
  I2Cstop();

  return dat;

}