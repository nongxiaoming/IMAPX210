/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-23     xiaonong       first version
 */

#include <rtthread.h>
#include "clock.h"

static unsigned int 
imapx200_get_pll(unsigned long pllval, unsigned long baseclk)
{
        unsigned long odiv, ddiv, mdiv;
    
        /*To prevent overflow in calculation*/
        baseclk /= 1000;

        odiv = (pllval & IMAP_PLL_ODIV)>>12;
        ddiv = (pllval & IMAP_PLL_DDIV)>>7;
        mdiv = (pllval & IMAP_PLL_MULTIV);
        return (baseclk*(2*(mdiv + 1))) / ((ddiv + 1)*(1<<(odiv)))*1000;
}

/**
 * @brief System Clock Configuration
 */
void rt_hw_clock_init(void)
{
	unsigned int clk,i;

	    /* PLL时钟选择外部时钟 */ 
	     PLL_CLKSEL=0x00;
	     /**
	     * HCLK  =APLL/12=132Mhz
	     * HCLKX2=APLL/6=264Mhz
	     * PCLK  =HCLK/(1*2)=66Mhz
	     **/
	    DIV_CFG0=(0x01<<16)|(0x06<<8)|(0x0c<<4)|0x02;
	      
	     /**
	      * TIM0_CLK=EPLL/(7+1)=60Mhz
	      * TIM1_CLK=EPLL/(7+1)=60Mhz
	      * TV_CLK = TV_ECLK
	      * CAM_CLK=EPLL/(5+1)=80Mhz
	      * UART_CLK=EPLL/(5+1)=80Mhz
	      **/
	     DIV_CFG1=(0x05<<26)|(0x02<<24)|(0x05<<18)|(2<<16)|(0x03<<10)|(0x07<<7)|(0x02<<5)|(0x07<<2)|(0x02);
        /**
	      * GPU_CLK=External clock=12Mhz
	      * ASYN_CLK=DPLL/1=1200Mhz
	      * USB_CLK = EPLL/(9+1)=48Mhz
	      * IIS_CLK=EPLL/(5+1)=80Mhz
	      **/	
		 	 DIV_CFG2=0x16260102; 
		 /**
	      * SD0_CLK=External clock=12Mhz
	      * SD1_CLK=External clock=12Mhz
	      * SD2_CLK=External clock=12Mhz
	      **/	
		 	 DIV_CFG3=0x00030303; 
		 /**
	      * IDS_CLK=EPLL/(7+1)=60Mhz
	      * IDSTF_CLK=EPLL/(7+1)=60Mhz
	      **/	
       DIV_CFG4=0x001e1e;
      /* DPLL=12Mhz*2*(79+1)/(2*1)=960Mhz */
	    DPLL_CFG=BIT31|(0x01<<12)|79;
	    /* EPLL=12Mhz*2*(39+1)/(2*1)=480Mhz */
	    EPLL_CFG=BIT31|(0x01<<12)|39;
	    /* APLL=12Mhz*2*(65+1)/1=1584Mhz */
	    APLL_CFG=BIT31|65;
	    /* 等待PLL锁定 */
	    	while((PLL_LOCKED&0x07)==0)
		{
     // debug("wait for APLL locked!\r\n");
 			for(i=500;i>0;i--);
         }
	  /* 设置CPU为异步模式，当CPU时钟使用DPLL时，要设为异步模式 */
			CPUSYNC_CFG = 0x01;
		/*切换PLL时钟输出到PLL输出*/
		PLL_OCLKSEL=0x07;
		/*打开GPU,VIDEN,VIDDE,MEMPL电源*/
		NPOW_CFG =0x3f;
   

	clk= imapx200_get_pll(APLL_CFG,12000000);
	// debug("APLL:%dM\r\n",clk/1000000);
	 clk= imapx200_get_pll(DPLL_CFG,12000000);
	// debug("DPLL:%dM\r\n",clk/1000000);
	 clk= imapx200_get_pll(EPLL_CFG,12000000);
	 
	 //debug("EPLL:%dM\r\n",clk/1000000);
	 //debug("PLL_OCLKSEL:0x%x\r\n",PLL_OCLKSEL);
	 //debug("APLL_CFG:0x%x\r\n",APLL_CFG);
	 //debug("DIV_CFG0:0x%x\r\n",DIV_CFG0);
  // debug("DIV_CFG1:0x%x\r\n",DIV_CFG1);
  // debug("DIV_CFG2:0x%x\r\n",DIV_CFG2);
  // debug("DIV_CFG3:0x%x\r\n",DIV_CFG3);
	 //debug("DIV_CFG4:0x%x\r\n",DIV_CFG4);
}

