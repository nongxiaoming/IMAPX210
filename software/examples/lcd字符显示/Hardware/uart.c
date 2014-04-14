#include "uart.h"
#include "clock.h"
/************************************************************************************
*文件名  ：uart.c																	                                  *
*文件作用：uart驱动源文件													                                    *
*作者    ：农晓明																	                                  *
*作者QQ  ：382421307																                                  *
*文件创建时间：2013/05/9			  												                              *	
*************************************************************************************/
void uart0_init(uint32_t baudrate)
{
  /*清空GPA0，GPA1配置*/
  GPACON&=0x00;
  /*配置GPA0连接到RXD0，GPA1连接到TXD0*/
  GPACON|=0x22;
  /*配置位普通模式，奇偶校验为None，数据位为8，停止位为1*/
 // ULCON0=0x03;
  //UBRDIV0=(PCLK/(baudrate*16)-1);
}
//串口发送
void uart0_send_byte(uint8_t data)
{   
     while((LSR0&(0x01<<5))==0);
		 THR0=data;
}
//串口接收
void uart0_send_string(const  uint8_t *pt)
{
    while(*pt)
	{
    uart0_send_byte(*pt);
	pt++;
	}
}
//串口3发送一个字节
void uart3_send_byte(uint8_t data)
{   
     while((LSR3&(0x01<<5))==0);
		 THR3=data;
}
//串口3发送一串字符
void uart3_send_string(const  uint8_t *pt)
{
    while(*pt)
	{
    uart3_send_byte(*pt);
	pt++;
	}
}

//类似printf的调试函数
void debug(char* fmt, ...)
{
    char* pArg= (void*)0;//等价于原来的va_list
    char c;
	  char buf[64];
    pArg = (char*) &fmt;//注意不要写成 p=fmt !! 因为这里要对参数取址，而不是取值
    pArg += sizeof(fmt);//等价于原来的va_start        
    
    do
    {
        c =*fmt;
        if (c != '%')
        {
            uart3_send_byte(c);//照原样输出字符
        }
        else
        {
            //按格式字符输出数据
            switch(*++fmt)
            {
                case 'd':
                    sprintf(buf,"%d",*((int*)pArg));  
                    pArg += sizeof(int); //等价于原来的va_arg								
                    break;
                case 'x':
                    sprintf(buf,"%x",*((int*)pArg));
								    pArg += sizeof(int); //等价于原来的va_arg
                    break;
				case 'f':
					sprintf(buf,"%f",*((float*)pArg));
					pArg += sizeof(float); //等价于原来的va_arg
                default:
                    break;
            }
           uart3_send_string((const uint8_t *)buf);
        }
        ++fmt;
    }while (*fmt != '\0');
    pArg = (void*)0; //等价于va_end
    return;
}
