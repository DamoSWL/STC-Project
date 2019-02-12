#ifndef _I2C_H
#define _I2C_H

#ifndef  _I2C_C

#endif

void I2C_start();
void I2C_stop();
bit I2C_write(unsigned char dat);
unsigned char I2C_readNAK();
unsigned char I2C_readACK();

#endif
