#include "delay.h"
/************************************************************************************
*文件名  ：delay.c																	                                  *
*文件作用：延时函数源文件													                                    *
*作者    ：农晓明																	                                  *
*作者QQ  ：382421307																                                  *
*文件创建时间：2013/05/9			  												                              *	
*************************************************************************************/
void delay_ms(uint32_t n)
{
  uint32_t a,b;
  for (a=0;a<n;a++)
	  for (b=0;b<7000;b++);
}
