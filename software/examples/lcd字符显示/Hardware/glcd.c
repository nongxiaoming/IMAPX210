#include "glcd.h"
/************************************************************************************
*文件名  ：glcd.c																	                                  *
*文件作用：lcd驱动源文件													                                    *
*作者    ：农晓明																	                                  *
*作者QQ  ：382421307																                                  *
*文件创建时间：2013/05/9			  												                              *	
*************************************************************************************/

/*LCD配置参数*/
#define  LCD_HFP		134		   /*LCD水平同步前端 */
#define  LCD_HSW		32		   /* LCD水平同步脉冲宽度 */
#define  LCD_HBP		250		   /*LCD水平同步后端*/
#define  LCD_VFP		10		   /*LCD垂直同步前端 */
#define  LCD_VSW		4		     /*LCD垂直同步脉冲宽度*/
#define  LCD_VBP		14		   /*LCD垂直同步后端*/
#define  LCD_HRES		1024	   /*LCD水平像素点*/
#define  LCD_VRES		600		   /*LCD垂直像素点*/
#define  LCD_RGB		0x6		   /* RGB输出 */
//#define  LCD_PIXEL_CLOCK	18519 /* 1000,000,000,000 / vclk */
//#define  LCD_IDS_CFG	0x1e1e	/* this value will be put in DIV_CFG4 */
#define  LCD_CLK_DIV	0	/* this value will be put in DIV_CFG4 */


#define  LCD_VFRAME_FREQ	60		  /*刷新频率*/
#define  LCD_HRES_OSD	 LCD_HRES		/* 水平像素点*/
#define  LCD_VRES_OSD	 LCD_VRES		/*垂直像素点*/
#define  LCD_HRES_OSD_VIRTUAL	LCD_HRES	/*虚拟水平像素点*/
#define  LCD_VRES_OSD_VIRTUAL	LCD_VRES		/* 虚拟垂直像素点*/


#define LCD_XSIZE   LCD_HRES
#define LCD_YSIZE   LCD_HRES

unsigned long *glcd_index;

  /*液晶屏的字体*/
static sFONT *LCD_Currentfonts;

  /*液晶屏的前景色和背景色*/
static uint32_t TextColor = 0xFFFFFF, BackColor = 0x000000;

#define CONFIG_FB_IMAP_BPP24

/**************************************************************************************************************
 * 函数名：glcd_gpio_config()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD管脚配置函数
 * 调用  ：初始化时调用        
 *****************************************************************************************************************/
static void glcd_gpio_config(void)
{
 /*配置GPM0~GPM15连接都VD0到VD15*/
 GPMCON=0xaaaaaaaa;
	GPMPUD=0x00000000;
 /*配置GPN连接到LCD*/
 GPNCON=0x2aaaaaa;
	GPNPUD=0x00000000;
	//配置背光线为输出
  GPACON&=~(0x3<<12);
  GPACON|=(0x01<<12);
	//打开LCD电源
  GPADAT|=(0x01<<6);
 
} 
/**************************************************************************************************************
 * 函数名：glcd_init()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD初始化函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_init(void )
{
   
	glcd_gpio_config();
	/* 2. 初始化display controller 
	 * 2.1 hsync,vsync,vclk,vden的极性和时间参数
	 * 2.2 行数、列数(分辨率),象素颜色的格式
	 * 2.3 分配显存(frame buffer),写入display controller
	 */

	LCDCON1 = IMAP_LCDCON1_PNRMODE_TFTLCD | IMAP_LCDCON1_ENVID_DISABLE |IMAP_LCDCON1_CLKVAL(LCD_CLK_DIV);
	LCDCON2 = IMAP_LCDCON2_VBPD(LCD_VBP - 1) | IMAP_LCDCON2_LINEVAL(LCD_VRES - 1) | IMAP_LCDCON2_VFPD(LCD_VFP - 1) | IMAP_LCDCON2_VSPW(LCD_VSW - 1);
	LCDCON3 = IMAP_LCDCON3_HBPD(LCD_HBP - 1) | IMAP_LCDCON3_HOZVAL(LCD_HRES - 1) | IMAP_LCDCON3_HFPD(LCD_HFP - 1);
	LCDCON4 = IMAP_LCDCON4_HSPW(LCD_HSW - 1);
	LCDCON5 = (LCD_RGB << 24) | IMAP_LCDCON5_INVVCLK_FALLING_EDGE | IMAP_LCDCON5_INVVLINE_INVERTED | IMAP_LCDCON5_INVVFRAME_INVERTED | IMAP_LCDCON5_INVVD_NORMAL| IMAP_LCDCON5_INVVDEN_NORMAL | IMAP_LCDCON5_INVPWREN_NORMAL | IMAP_LCDCON5_PWREN_ENABLE;
  
	OVCDCR = IMAP_OVCDCR_IFTYPE_RGB,

#if defined (CONFIG_LCD_BPP8)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_8BPP_ARGB232 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_8BPP_ARGB232 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_8BPP_ARGB232 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_8BPP_ARGB232 | IMAP_OVCWxCR_ENWIN_DISABLE;

#elif defined (CONFIG_LCD_BPP16)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_16BPP_RGB565 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_16BPP_RGB565 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_16BPP_RGB565 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_16BPP_RGB565 | IMAP_OVCWxCR_ENWIN_DISABLE;

	
#elif defined (CONFIG_LCD_BPP18)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_18BPP_RGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_18BPP_RGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_18BPP_RGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_18BPP_RGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;


#elif defined (CONFIG_LCD_BPP19)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_19BPP_ARGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_19BPP_ARGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_19BPP_ARGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_19BPP_ARGB666 | IMAP_OVCWxCR_ENWIN_DISABLE;

#elif defined (CONFIG_LCD_BPP24)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_24BPP_RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_24BPP_RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_24BPP_RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_24BPP_RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;


#elif defined (CONFIG_LCD_BPP25)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_25BPP_ARGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_25BPP_ARGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_25BPP_ARGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_25BPP_ARGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;

#elif defined (CONFIG_LCD_BPP28)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_28BPP_A4RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_28BPP_A4RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_28BPP_A4RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_28BPP_A4RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;


#elif defined (CONFIG_LCD_BPP32)
	OVCW0CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE
		| IMAP_OVCWxCR_BPPMODE_32BPP_A8RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW1CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_32BPP_A8RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW2CR = IMAP_OVCWxCR_BUFSEL_BUF0 | IMAP_OVCWxCR_BUFAUTOEN_DISABLE | IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE
		| IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE | IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 
		| IMAP_OVCWxCR_BLD_PIX_PLANE | IMAP_OVCWxCR_BPPMODE_32BPP_A8RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;
	OVCW3CR = IMAP_OVCWxCR_BITSWP_DISABLE | IMAP_OVCWxCR_BIT2SWP_DISABLE | IMAP_OVCWxCR_BIT4SWP_DISABLE | IMAP_OVCWxCR_BYTSWP_DISABLE
		| IMAP_OVCWxCR_HAWSWP_DISABLE | IMAP_OVCWxCR_ALPHA_SEL_1 | IMAP_OVCWxCR_BLD_PIX_PLANE
		| IMAP_OVCWxCR_BPPMODE_32BPP_A8RGB888 | IMAP_OVCWxCR_ENWIN_DISABLE;

#endif

	OVCW0PCAR = IMAP_OVCWxPCAR_LEFTTOPX(0) | IMAP_OVCWxPCAR_LEFTTOPY(0),
	
	OVCW0PCBR = IMAP_OVCWxPCBR_RIGHTBOTX(LCD_HRES_OSD - 1) | IMAP_OVCWxPCBR_RIGHTBOTY(LCD_VRES_OSD - 1),
	OVCW0CMR = IMAP_OVCWxCMR_MAPCOLEN_DISABLE,

#if (CONFIG_FB_IMAP_NUM > 1)
	OVCW1PCAR = IMAP_OVCWxPCAR_LEFTTOPX(0) | IMAP_OVCWxPCAR_LEFTTOPY(0),
	OVCW1PCBR = IMAP_OVCWxPCBR_RIGHTBOTX(IMAPFB_HRES_OSD - 1) | IMAP_OVCWxPCBR_RIGHTBOTY(IMAPFB_VRES_OSD - 1),
	OVCW1PCCR = IMAP_OVCWxPCCR_ALPHA0_R(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA0_G(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA0_B(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_R(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA1_G(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_B(IMAPFB_MAX_ALPHA_LEVEL),
	OVCW1CMR = IMAP_OVCWxCMR_MAPCOLEN_DISABLE,
#endif

#if (CONFIG_FB_IMAP_NUM > 2)	
	OVCW2PCAR = IMAP_OVCWxPCAR_LEFTTOPX(0) | IMAP_OVCWxPCAR_LEFTTOPY(0),
	OVCW2PCBR = IMAP_OVCWxPCBR_RIGHTBOTX(IMAPFB_HRES_OSD - 1) | IMAP_OVCWxPCBR_RIGHTBOTY(IMAPFB_VRES_OSD - 1),
	OVCW2PCCR = IMAP_OVCWxPCCR_ALPHA0_R(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA0_G(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA0_B(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_R(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA1_G(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_B(IMAPFB_MAX_ALPHA_LEVEL),
	OVCW2CMR = IMAP_OVCWxCMR_MAPCOLEN_DISABLE,
#endif

#if (CONFIG_FB_IMAP_NUM > 3)
	OVCW3PCAR = IMAP_OVCWxPCAR_LEFTTOPX(0) | IMAP_OVCWxPCAR_LEFTTOPY(0),
	OVCW3PCBR = IMAP_OVCWxPCBR_RIGHTBOTX(IMAPFB_HRES_OSD - 1) | IMAP_OVCWxPCBR_RIGHTBOTY(IMAPFB_VRES_OSD - 1),
	OVCW3PCCR = IMAP_OVCWxPCCR_ALPHA0_R(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA0_G(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA0_B(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_R(IMAPFB_MAX_ALPHA_LEVEL)
		| IMAP_OVCWxPCCR_ALPHA1_G(IMAPFB_MAX_ALPHA_LEVEL) | IMAP_OVCWxPCCR_ALPHA1_B(IMAPFB_MAX_ALPHA_LEVEL),
	OVCW3CMR = IMAP_OVCWxCMR_MAPCOLEN_DISABLE,
#endif	
 //选择window0的BUF0，使用两个BUF，使用24BPP_RGB888模式
 OVCW0CR=IMAP_OVCWxCR_BUFSEL_BUF0|IMAP_OVCWxCR_BUFNUM_2BUFS	|IMAP_OVCWxCR_BPPMODE_24BPP_RGB888;
 //设置window0的BUF0的framebuffer地址
 OVCW0B0SAR =FRAME_BUFFER;
	glcd_index=(unsigned long*)FRAME_BUFFER;
	glcd_clear(BLUE);
	glcd_display_on();
	glcd_set_font(&Font8x16);
}

/**************************************************************************************************************
 * 函数名：backlight_enable()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD背光使能
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void backlight_enable(void)
{
	//打开背光
	GPFDAT |= (1<<6);
}
/**************************************************************************************************************
 * 函数名：backlight_disable()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD背光失能函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void backlight_disable(void)
{
	//关闭背光
	GPFDAT &= ~(1<<6);
}

/**************************************************************************************************************
 * 函数名：lcd_power_on()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD电源使能
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void lcd_power_on(void)
{
	//使能LCD的PWR
uint32_t tmp;
	backlight_enable();
	tmp = LCDCON5;
	LCDCON5=tmp|IMAP_LCDCON5_PWREN_ENABLE;
}
/**************************************************************************************************************
 * 函数名：lcd_power_off()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD电源关闭
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void lcd_power_off(void)
{ 
	//失能能LCD的PWR
   uint32_t tmp;
	backlight_disable();
	tmp = LCDCON5;
	LCDCON5=tmp&~IMAP_LCDCON5_PWREN_ENABLE;
}
/**************************************************************************************************************
 * 函数名：glcd_display_on()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD开启显示
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_display_on(void)
{
uint32_t tmp;
	tmp = LCDCON1;
	LCDCON1=tmp|IMAP_LCDCON1_ENVID_ENABLE;
 //显示window0
	tmp=OVCW0CR;
	OVCW0CR=tmp| IMAP_OVCWxCR_ENWIN_ENABLE;
}
/**************************************************************************************************************
 * 函数名：glcd_display_off()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD关闭显示
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_display_off(void)
{
	uint32_t tmp;
	tmp = LCDCON1;
  LCDCON1=tmp & ~IMAP_LCDCON1_ENVID_ENABLE;
	//不显示window0
	tmp=OVCW0CR;
	OVCW0CR=tmp&~IMAP_OVCWxCR_ENWIN_ENABLE;
}

/**************************************************************************************************************
 * 函数名：glcd_clear()
 * 输入  ：uint32_t color 刷屏颜色
 * 输出  ：void
 * 描述  ：LCD清屏函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_clear(uint32_t color)
{
	volatile unsigned long *p = (volatile unsigned long*)FRAME_BUFFER;
	int x, y;
	
	for (y = 0; y < LCD_YSIZE; y++)
	{
		for (x = 0; x < LCD_XSIZE; x++)
		{
			*p++ =color;  /* red */
		}
	}
}
/**************************************************************************************************************
 * 函数名：glcd_set_cursor()
 * 输入  ：uint16_t x, uint16_t y 设定的屏幕的X值和Y值
 * 输出  ：void
 * 描述  ：LCD设置光标位置函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_set_cursor(uint16_t x, uint16_t y)
{
 glcd_index = ((unsigned long*)FRAME_BUFFER) + x + y*LCD_XSIZE;
}
/**************************************************************************************************************
 * 函数名：glcd_set_window()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width 区域的起点，宽和高
 * 输出  ：void
 * 描述  ：设置某个特定的填充区域
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_set_window(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height)
{
  /*设置水平方向X开始坐标*/
  glcd_index = ((unsigned long*)FRAME_BUFFER) + Xpos + (Ypos*LCD_XSIZE);
  // WindX_Size = Width;
  // WindY_Size = Height;
  // CurrX_Size = CurrY_Size = 0;
}
/**************************************************************************************************************
 * 函数名：glcd_set_colors()
 * 输入  ：_TextColor 前景色,_BackColor 背景色
 * 输出  ：void
 * 描述  ：设置LCD的前景色和背景色
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_set_colors(uint32_t _TextColor,uint32_t _BackColor)
{
  TextColor = _TextColor; 
  BackColor = _BackColor;
}
/**************************************************************************************************************
 * 函数名：glcd_get_colors()
 * 输入  ：*_TextColor 前景色的指针,*_BackColor 背景色的指针
 * 输出  ：void
 * 描述  ：获取LCD的前景色和背景色
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_get_colors(uint32_t *_TextColor,uint32_t *_BackColor)
{
  *_TextColor = TextColor; *_BackColor = BackColor;
}
/**************************************************************************************************************
 * 函数名：glcd_set_textcolor()
 * 输入  ：uint16_t Color 前景色
 * 输出  ：void
 * 描述  ：设置LCD的前景色
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_set_textcolor(uint32_t Color)
{
  TextColor = Color;
}


/**************************************************************************************************************
 * 函数名：glcd_set_backcolor()
 * 输入  ：uint16_t Color 背景色
 * 输出  ：void
 * 描述  ：设置LCD的背景色
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_set_backcolor(uint32_t Color)
{
  BackColor = Color;
}
/**************************************************************************************************************
 * 函数名：glcd_set_font()
 * 输入  ：sFONT *fonts 要设置的字体
 * 输出  ：void
 * 描述  ：设置LCD的字体
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_set_font(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}
/**************************************************************************************************************
 * 函数名：glcd_get_font()
 * 输入  ：void
 * 输出  ：sFONT * 获取字体
 * 描述  ：设置LCD的字体
 * 调用  ：外部调用        
 *****************************************************************************************************************/
sFONT* glcd_get_font(void)
{
  return LCD_Currentfonts;
}
/**************************************************************************************************************
 * 函数名：glcd_draw_hline()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Length 起点X和Y坐标及长度
 * 输出  ：void
 * 描述  ：画水平线
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_draw_hline(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t i = 0;
   glcd_set_cursor(Xpos, Ypos);
    for(i = 0; i < Length; i++)
    {
      *glcd_index=TextColor;
	  glcd_index++;
    }
}
/**************************************************************************************************************
 * 函数名：glcd_draw_vline()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Length 起点X和Y坐标及长度
 * 输出  ：void
 * 描述  ：画垂直线
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_draw_vline(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t i = 0;
    for(i = 0; i < Length; i++)
    { 
	  glcd_set_cursor(Xpos, Ypos);
      *glcd_index=TextColor;
      Ypos++; 
    }
}
/**************************************************************************************************************
 * 函数名：glcd_draw_rect()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height 矩形左上角点的坐标及宽和高
 * 输出  ：void
 * 描述  ：画矩形函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_draw_rect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height)
{
  glcd_draw_hline(Xpos, Ypos, Width);
  glcd_draw_hline(Xpos, Ypos+ Height, Width); 
  glcd_draw_vline(Xpos, Ypos, Height);
  glcd_draw_vline(Xpos+ Width,Ypos, Height);
}
/**************************************************************************************************************
 * 函数名：glcd_draw_circle()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Radius 圆心坐标点及半径
 * 输出  ：void
 * 描述  ：画圆函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_draw_circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;/* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    glcd_set_cursor(Xpos + CurX, Ypos + CurY);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos + CurX, Ypos - CurY);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos - CurX, Ypos + CurY);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos - CurX, Ypos - CurY);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos + CurY, Ypos + CurX);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos + CurY, Ypos - CurX);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos - CurY, Ypos + CurX);
    *glcd_index=TextColor;
    glcd_set_cursor(Xpos - CurY, Ypos - CurX);
    *glcd_index=TextColor;
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}
/**************************************************************************************************************
 * 函数名：glcd_draw_monobmp()
 * 输入  ：const uint32_t *Pict 画一个全屏单色的取膜数据
 * 输出  ：void
 * 描述  ：画一个单色的全屏图片函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_draw_monobmp(const uint32_t *Pict)
{
  uint32_t index = 0, i = 0;
  glcd_set_cursor(0, 0); 
  for(index = 0; index < (LCD_XSIZE*LCD_YSIZE)/32; index++)
  {
    for(i = 0; i < 32; i++)
    {
      if((Pict[index] & (1 << i)) == 0x00)
      {
        *glcd_index++=BackColor;
      }
      else
      {
        *glcd_index++=TextColor;
      }
    }
  }
}
/**************************************************************************************************************
 * 函数名：glcd_fill_rect()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height 填充矩形左上角点、宽和高
 * 输出  ：void
 * 描述  ：画一个填充的矩形
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_fill_rect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{ 
	uint32_t tempcolor;
  glcd_set_textcolor(TextColor);
  glcd_draw_hline(Xpos, Ypos, Width);
  glcd_draw_hline(Xpos, Ypos+ Height, Width);
  
  glcd_draw_vline(Xpos, Ypos, Height);
  glcd_draw_vline(Xpos+Width, Ypos, Height);

  Width --;
  Height--;
  Xpos++;
  tempcolor=TextColor;
  glcd_set_textcolor(BackColor);

  while(Height--)
  {
    glcd_draw_hline(Xpos, ++Ypos, Width);    
  }

  glcd_set_textcolor(tempcolor);
}
/**************************************************************************************************************
 * 函数名：glcd_fill_circle()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Radius 填充圆的圆心和半径
 * 输出  ：void
 * 描述  ：画一个填充圆
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_fill_circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;    /* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  uint32_t tempcolor;
  D = 3 - (Radius << 1);

  CurX = 0;
  CurY = Radius;
  tempcolor=TextColor;
  glcd_set_textcolor(BackColor);

  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      glcd_draw_hline(Xpos - CurY, Ypos - CurX, 2*CurY);
      glcd_draw_hline(Xpos - CurY, Ypos + CurX, 2*CurY);
    }

    if(CurX > 0) 
    {
      glcd_draw_hline(Xpos - CurX, Ypos -CurY, 2*CurX);
      glcd_draw_hline(Xpos - CurX, Ypos + CurY, 2*CurX);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }

  glcd_set_textcolor(tempcolor);
  glcd_draw_circle(Xpos, Ypos, Radius);
}
/**************************************************************************************************************
 * 函数名：glcd_draw_uniline()
 * 输入  ：uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 起始点坐标和终点坐标
 * 输出  ：void
 * 描述  ：画任意方向的直线
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_draw_uniline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    glcd_draw_pixel(x, y);             /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}
/**************************************************************************************************************
 * 函数名：glcd_draw_pixel()
 * 输入  ：int16_t x, int16_t y  点的坐标
 * 输出  ：void
 * 描述  ：画一个象素点
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_draw_pixel(uint16_t x, uint16_t y)
{ 
  if( x > LCD_XSIZE ||  y > LCD_YSIZE)
  {
    return;  
  }
  glcd_draw_hline(x, y, 1);
}
/**************************************************************************************************************
 * 函数名：glcd_draw_char()
 * 输入  ：const uint16_t *c   字符编码
 * 输出  ：void
 * 描述  ：LCD画一个字符
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_draw_char(uint16_t Xpos, uint16_t Ypos, const uint16_t *c)
{
  uint32_t index = 0, i = 0;
  uint16_t  x = 0,y=0;
  y = Ypos;
  
  for(index = 0; index < LCD_Currentfonts->Height; index++)
  { 
	 x=Xpos;
    for(i = 0; i < LCD_Currentfonts->Width; i++)
    {
  
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> i)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
        (((c[index] & (0x1 << i)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))

      {
				glcd_set_cursor(x++,y);
				*glcd_index=BackColor;
      }
      else
      {
        glcd_set_cursor(x++,y);
				*glcd_index=TextColor;
      } 
    }
    y++;
   
  }

}
/**************************************************************************************************************
 * 函数名：glcd_display_char()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint8_t Ascii 显示的位置和字符
 * 输出  ：void
 * 描述  ：LCD显示一个字符
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_display_char(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
  Ascii -= 32;
  glcd_draw_char(Xpos, Ypos, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
}
/**************************************************************************************************************
 * 函数名：glcd_draw_string()
 * 输入  ：u16 xpos, u16 ypos, u8 *ptr 显示的位置和字符串
 * 输出  ：void
 * 描述  ：LCD显示一串字符
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void glcd_draw_string(uint16_t xpos, uint16_t ypos, uint8_t *ptr)
{
  	uint16_t refypos=xpos;
  	while(*ptr!=0)
  	{
    	glcd_display_char(refypos,ypos,*ptr);
    	refypos+=LCD_Currentfonts->Width;
    	ptr++;
  	}
}

//m^n函数
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}			 
/**************************************************************************************************************
 * 函数名：glcd_draw_num()
 * 输入  ：u16 x, u16 y, s32 num, u8 len   显示的位置，数字及长度
 * 输出  ：void
 * 描述  ：LCD显示一个数字
 * 调用  ：外部调用        
 *****************************************************************************************************************/	 
void glcd_draw_num(uint16_t x, uint16_t y, int32_t num, uint8_t len)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	t=0;
	if(num<0)
	{
		glcd_display_char(x+(LCD_Currentfonts->Width)*t,y,'-');
		num=-num;
		t++;
	}						   
	for(;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				glcd_display_char(x+(LCD_Currentfonts->Width)*t,y,' ');
				continue;
			}else enshow=1; 		 	 
		}
	 	glcd_display_char(x+(LCD_Currentfonts->Width)*t,y,temp+'0'); 
	}
} 


/**************************************************************************************************************
 * 函数名：glcd_clear_aera()
 * 输入  ：uint16_t x,uint16_t y,uint16_t w,uint16_t h   清除的位置，长度和宽度
 * 输出  ：void
 * 描述  ：LCD清除某个区域
 * 调用  ：外部调用        
 *****************************************************************************************************************/	
void glcd_clear_aera(uint16_t x,uint16_t y,uint16_t w,uint16_t h)
{
	uint32_t tempcolor;
  tempcolor=TextColor;
  glcd_set_textcolor(BackColor);
  while(h--)
  {
    glcd_draw_hline(x, y++, w);    
  }
  glcd_set_textcolor(tempcolor);
}
void glcd_debug(char* fmt, ...)
{  
	 static uint16_t debug_x=0,debug_y=0;
    char* pArg= (void*)0;//等价于原来的va_list
    char c;
	  char buf[64];
    pArg = (char*) &fmt;//注意不要写成 p=fmt !! 因为这里要对参数取址，而不是取值
    pArg += sizeof(fmt);//等价于原来的va_start        
    TextColor = 0xFFFFFF; BackColor = 0x000000;
    do
    {
        c =*fmt;
        if (c != '%')
        {   
					  if(c=='\r')
							{
               debug_y+=12;
              }
						 else	if(c=='\n')
						{
							debug_x=0;
							debug_y+=12;
							if(debug_y>(LCD_YSIZE-12))
									{
                   glcd_clear(BLACK);
										debug_x=0;
                    debug_y=0;
                  }
            }else {
            glcd_display_char(debug_x,debug_y,c);//照原样输出字符
					  debug_x+=8;
					  if(debug_x>(LCD_XSIZE-8))
							{
								debug_x=0;
               debug_y+=12;
								if(debug_y>(LCD_YSIZE-12))
									{
                   glcd_clear(BLACK);
										debug_x=0;
                    debug_y=0;
                  }
              }
						}
							
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
           glcd_draw_string(debug_x,debug_y,(uint8_t *)buf);
					 debug_x+=strlen(buf)*8;
        }
        ++fmt;
    }while (*fmt != '\0');
    pArg = (void*)0; //等价于va_end
    return;
}
