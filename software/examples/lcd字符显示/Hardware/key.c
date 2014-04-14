#include "key.h"
#include "s3c6410.h"
#include "delay.h"
#include "uart.h"

void key_init(void)
{
 GPNCON&=~0x00ffffff;
 GPNPUD|=0x02aa;
 GPNDAT|=0x3f;
 GPLCON1&=~0x000ff000;
 GPLPUD|=2<<22|2<<24;
 GPLDAT|=0x1800;
}
int key_scanf(void)
{ 

	//debug("key_scanf\n");
  if ((GPNDAT&0x3f)!=0x3f)
  {   
	  delay_ms(5);
	  if ((GPNDAT&KEY1)==0)
	  {  
		  debug("K1 pressed!\n");
		  return KEY1;
	  }
	    if ((GPNDAT&KEY2)==0)
	  {   
		  debug("K2 pressed!\n");
		  return KEY2;
	  }
	    if ((GPNDAT&KEY3)==0)
	  {   
		  debug("K3 pressed!\n");
		  return KEY3;
	  }
	    if ((GPNDAT&KEY4)==0)
	  {   
		  debug("K4 pressed!\n");
		  return KEY4;
	  }
	    if ((GPNDAT&KEY5)==0)
	  {   
		  debug("K5 pressed!\n");
		  return KEY5;
	  }  if ((GPNDAT&KEY6)==0)
	  {   
		  debug("K6 pressed!\n");
		  return KEY6;
	  }
  }
    if ((GPLDAT&0x1800)!=0x1800)
  {
	  delay_ms(5);
	  if ((GPLDAT&KEY7)==0)
	  {  
		  debug("K7 pressed!\n");
		  return KEY7;
	  }
	    if ((GPLDAT&KEY8)==0)
	  {   
		  debug("K8 pressed!\n");
		  return KEY8;
	  }
	 
  }
  return 0;
}


