#include<reg52.h>

sbit ENLED=P1^2;

void main()
{
  unsigned int i=0;
  unsigned char cnt=0;
  bit dir=0;
  ENLED=0;
  TMOD=0x01;
  TH0=0xDC;
  TL0=0x00;
  TR0=1;

  while(1)
  {
    if(TF0==1)
	{
	  TF0=0;
	  TH0=0xDC;
	  TL0=0x00;
	  cnt++;
	  if(cnt>=100)
	  {
	    cnt=0;
	    if(dir==0)
		{
          P0=~(0x01d<<i);
		  i++;
		  if(i>=4)
		  {
		    dir=1;
			i=0;
		  }
		 }
		  else
		  {
		    P0=~(0x08>>i);
			i++;
			if(i>=4)
			{
			  dir=0;
			  i=0;
			}
		  }
	   }
	 }
   }
}


		    

