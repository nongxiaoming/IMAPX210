#include "s3c6410.h"
#include "clock.h"



void clock_init(void)
{ 
    /*设置APLL,MPLL,EPLL的锁定时间，这里设置的是默认值，可以去掉*/
    APLL_LOCK = 0x0000ffff;
	MPLL_LOCK = 0x0000ffff;
	EPLL_LOCK = 0x0000ffff;

	/*设置CPU为异步模式，当CPU时钟 != HCLK时，要设为异步模式 */
	OTHERS &= ~0xc0;
	/*等待CPU进入异步模式*/
	while ((OTHERS & 0xf00) != 0);
    /*配置ARMCLK=667Mhz，HCLKX2=266Mhz，HCLK=133Mhz，
    PCLK=66Mhz，CLKSECUR=66Mhz，CLKJPEG=66Mhz*/
	CLK_DIV0 = CLK_DIV0_VAL;
	/*APLL_FOUT=12*333/(3*2)=667Mhz*/
	APLL_CON = APLL_CON_VAL; 
	/*MPLL_FOUT=12*266/(3*2^2)=266Mhz*/
	MPLL_CON = MPLL_CON_VAL;  
	/*EPLL_FOUT=12*(32+0)/(1*2^2)=96Mhz*/
	EPLL_CON0=EPLL_CON0_VAL;
	EPLL_CON1=EPLL_CON1_VAL;
	/*选择时钟，ALCK，MLCK，ELCK都选用PLL时钟*/
	CLK_SRC =  CLK_SRC_VAL;
}
