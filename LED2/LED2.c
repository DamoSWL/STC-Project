#include <reg52.h>

sbit ENLED=P1^2;
 
void main()
{
  unsigned int i=0;
  unsigned char cnt=0;
  ENLED=0;
  while(1)
  {
    P0=~(0x01<<cnt);
	for(i=0;i<50000;i++);
	cnt++;
	if(cnt>=4)
	{
	  P0=0xF0;
	  for(i=0;i<=40000;i++);
	  cnt=0;
	}
  }

}