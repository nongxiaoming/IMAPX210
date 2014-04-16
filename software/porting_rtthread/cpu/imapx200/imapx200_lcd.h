#ifndef __IMAP_LCD_H
#define __IMAP_LCD_H
#define LCDCON1		(*(volatile unsigned *)(0x20CD0000))	/* LCD Control 1 Register */
#define LCDCON2		(*(volatile unsigned *)(0x20CD0004))	/* LCD Control 2 Register */
#define LCDCON3		(*(volatile unsigned *)(0x20CD0008))	/* LCD Control 3 Register */
#define LCDCON4		(*(volatile unsigned *)(0x20CD000C))	/* LCD Control 4 Register */
#define LCDCON5		(*(volatile unsigned *)(0x20CD0010))	/* LCD Control 5 Register */

#define LCDVCLKFSR	(*(volatile unsigned *)(0x20CD0030))	/* LCD VCLK Frequency Status Register */

#define IDSINTPND		(*(volatile unsigned *)(0x20CD0054))	/* IDS Interrupt Pending Register */
#define IDSSRCPND		(*(volatile unsigned *)(0x20CD0058))	/* IDS Source Pending Register */
#define IDSINTMSK		(*(volatile unsigned *)(0x20CD005C))	/* IDS Interrupt Mask Register */

#define OVCDCR			(*(volatile unsigned *)(0x20CD1000))	/* Overlay Controller Display Control Register */
#define OVCPCR			(*(volatile unsigned *)(0x20CD1004))	/* Overlay Controller Palette Control Register */
#define OVCBKCOLOR	(*(volatile unsigned *)(0x20CD1008))	/* Overlay Controller Background Color Register */

#define OVCW0CR		  (*(volatile unsigned *)(0x20CD1080))	/* Overlay Controller Window 0 Control Register */
#define OVCW0PCAR		(*(volatile unsigned *)(0x20CD1084))	/* Overlay Controller Window 0 Position Control A Register */
#define OVCW0PCBR		(*(volatile unsigned *)(0x20CD1088))	/* Overlay Controller Window 0 Position Control B Register */
#define OVCW0B0SAR	(*(volatile unsigned *)(0x20CD108C))	/* Overlay Controller Window 0 Buffer 0 Start Address Register */
#define OVCW0B1SAR	(*(volatile unsigned *)(0x20CD1090))	/* Overlay Controller Window 0 Buffer 1 Start Address Register */
#define OVCW0VSSR		(*(volatile unsigned *)(0x20CD1094))	/* Overlay Controller Window 0 Virtual Screen Size Register */
#define OVCW0CMR		(*(volatile unsigned *)(0x20CD1098))	/* Overlay Controller Window 0 Color Map Register */
#define OVCW0B2SAR	(*(volatile unsigned *)(0x20CD109C))/* Overlay Controller Window 0 Buffer 2 Start Address Register */
#define OVCW0B3SAR	(*(volatile unsigned *)(0x20CD10A0))	/* Overlay Controller Window 0 Buffer 3 Start Address Register */

#define OVCW1CR		  (*(volatile unsigned *)(0x20CD1100))	/* Overlay Controller Window 1 Control Register */
#define OVCW1PCAR		(*(volatile unsigned *)(0x20CD1104))	/* Overlay Controller Window 1 Position Control A Register */
#define OVCW1PCBR		(*(volatile unsigned *)(0x20CD1108))	/* Overlay Controller Window 1 Position Control B Register */
#define OVCW1PCCR		(*(volatile unsigned *)(0x20CD110C))	/* Overlay Controller Window 1 Position Control C Register */
#define OVCW1B0SAR  (*(volatile unsigned *)(0x20CD1110))	/* Overlay Controller Window 1 Buffer 0 Start Address Register */
#define OVCW1B1SAR  (*(volatile unsigned *)(0x20CD1114))	/* Overlay Controller Window 1 Buffer 1 Start Address Register */
#define OVCW1VSSR		(*(volatile unsigned *)(0x20CD1118))/* Overlay Controller Window 1 Virtual Screen Size Register */
#define OVCW1CKCR		(*(volatile unsigned *)(0x20CD111C))/* Overlay Controller Window 1 Color Key Control Register */
#define OVCW1CKR		(*(volatile unsigned *)(0x20CD1120))	/* Overlay Controller Window 1 Color Key Register */
#define OVCW1CMR	   (*(volatile unsigned *)(0x20CD1124))/* Overlay Controller Window 1 Color Map Register */
#define OVCW1B2SAR	(*(volatile unsigned *)(0x20CD1128))	/* Overlay Controller Window 1 Buffer 2 Start Address Register */
#define OVCW1B3SAR	(*(volatile unsigned *)(0x20CD112C))	/* Overlay Controller Window 1 Buffer 3 Start Address Register */
	
#define OVCW2CR		(*(volatile unsigned *)(0x20CD1180))	/* Overlay Controller Window 2 Control Register */
#define OVCW2PCAR		(*(volatile unsigned *)(0x20CD1184))	/* Overlay Controller Window 2 Position Control A Register */
#define OVCW2PCBR		(*(volatile unsigned *)(0x20CD1188))	/* Overlay Controller Window 2 Position Control B Register */
#define OVCW2PCCR		(*(volatile unsigned *)(0x20CD118C))	/* Overlay Controller Window 2 Position Control C Register */
#define OVCW2B0SAR	(*(volatile unsigned *)(0x20CD1190))	/* Overlay Controller Window 2 Buffer 0 Start Address Register */
#define OVCW2B1SAR	(*(volatile unsigned *)(0x20CD1194))	/* Overlay Controller Window 2 Buffer 1 Start Address Register */
#define OVCW2VSSR		(*(volatile unsigned *)(0x20CD1198))	/* Overlay Controller Window 2 Virtual Screen Size Register */
#define OVCW2CKCR		(*(volatile unsigned *)(0x20CD119C))	/* Overlay Controller Window 2 Color Key Control Register */
#define OVCW2CKR		(*(volatile unsigned *)(0x20CD11A0))/* Overlay Controller Window 2 Color Key Register */
#define OVCW2CMR	   (*(volatile unsigned *)(0x20CD11A4))	/* Overlay Controller Window 2 Color Map Register */
#define OVCW2B2SAR	(*(volatile unsigned *)(0x20CD11A8))	/* Overlay Controller Window 2 Buffer 2 Start Address Register */
#define OVCW2B3SAR	(*(volatile unsigned *)(0x20CD11AC))	/* Overlay Controller Window 2 Buffer 3 Start Address Register */

#define OVCW3CR		  (*(volatile unsigned *)(0x20CD1200))	/* Overlay Controller Window 3 Control Register */
#define OVCW3PCAR		(*(volatile unsigned *)(0x20CD1204))	/* Overlay Controller Window 3 Position Control A Register */
#define OVCW3PCBR		(*(volatile unsigned *)(0x20CD1208))	/* Overlay Controller Window 3 Position Control B Register */
#define OVCW3PCCR		(*(volatile unsigned *)(0x20CD120C))	/* Overlay Controller Window 3 Position Control C Register */
#define OVCW3BSAR		(*(volatile unsigned *)(0x20CD1210))	/* Overlay Controller Window 3 Buffer Start Address Register */
#define OVCW3VSSR		(*(volatile unsigned *)(0x20CD1214))	/* Overlay Controller Window 3 Virtual Screen Size Register */
#define OVCW3CKCR		(*(volatile unsigned *)(0x20CD1218))	/* Overlay Controller Window 3 Color Key Control Register */
#define OVCW3CKR		(*(volatile unsigned *)(0x20CD121C))/* Overlay Controller Window 3 Color Key Register */
#define OVCW3CMR	   (*(volatile unsigned *)(0x20CD1220))	/* Overlay Controller Window 3 Color Map Register */
#define OVCW3SABSAR	(*(volatile unsigned *)(0x20CD1224))	/* Overlay Controller Window 3 Cursor And Bitmap Buffer Start Address Register */

#define OVCBRB0SAR	 (*(volatile unsigned *)(0x20CD1300))	/* Overlay Controller CbCr Buffer 0 Start Address Register */
#define OVCBRB1SAR	(*(volatile unsigned *)(0x20CD1304))	/* Overlay Controller CbCr Buffer 1 Start Address Register */
#define OVCOEF11		(*(volatile unsigned *)(0x20CD1308))	/* Overlay Controller Color Matrix Coefficient11 Register */
#define OVCOEF12		(*(volatile unsigned *)(0x20CD130C))	/* Overlay Controller Color Matrix Coefficient12 Register */
#define OVCOEF13		(*(volatile unsigned *)(0x20CD1310))	/* Overlay Controller Color Matrix Coefficient13 Register */
#define OVCOEF21		(*(volatile unsigned *)(0x20CD1314))	/* Overlay Controller Color Matrix Coefficient21 Register */
#define OVCOEF22		(*(volatile unsigned *)(0x20CD1318))	/* Overlay Controller Color Matrix Coefficient22 Register */
#define OVCOEF23		(*(volatile unsigned *)(0x20CD131C))	/* Overlay Controller Color Matrix Coefficient23 Register */
#define OVCOEF31		(*(volatile unsigned *)(0x20CD1320))	/* Overlay Controller Color Matrix Coefficient31 Register */
#define OVCOEF32		(*(volatile unsigned *)(0x20CD1324))/* Overlay Controller Color Matrix Coefficient32 Register */
#define OVCOEF33		(*(volatile unsigned *)(0x20CD1328))	/* Overlay Controller Color Matrix Coefficient33 Register */
#define OVCOMC		(*(volatile unsigned *)(0x20CD132C))	/* Overlay Controller Color Matrix Configure Register */
#define OVCBRB2SAR	(*(volatile unsigned *)(0x20CD1330))/* Overlay Controller CbCr Buffer 2 Start Address Register */
#define OVCBRB3SAR	(*(volatile unsigned *)(0x20CD1334))	/* Overlay Controller CbCr Buffer 3 Start Address Register */

#define OVCW0PAL		(*(volatile unsigned *)(0x20CD1400))	/* Overlay Controller Window 0 Palette RAM, 256 entries */
#define OVCW1PAL		(*(volatile unsigned *)(0x20CD1800))	/* Overlay Controller Window 1 Palette RAM, 256 entries */
#define OVCW2PAL		(*(volatile unsigned *)(0x20CD1C00))	/* Overlay Controller Window 2 Palette Register, 16 entries */
#define OVCW3PAL		(*(volatile unsigned *)(0x20CD1E00))	/* Overlay Controller Window 3 Palette Register, 16 entries */

/*TVIF*/
#define TVCCR		(*(volatile unsigned *)(0x20CD2000))	/* TVIF Clock Configuration Register */
#define TVICR		(*(volatile unsigned *)(0x20CD2004))	/* TVIF Configuration Register */
#define TVCMCR		(*(volatile unsigned *)(0x20CD202C))	/* TVIF Color Matrix Configure Register */
#define TVUBA1		(*(volatile unsigned *)(0x20CD2030))	/* TVIF Upper Blanking Area 1 Line Register */
#define ITVUNBA		(*(volatile unsigned *)(0x20CD2034))	/* TVIF Upper Non-blanking Area Line Register */
#define TVUBA2		(*(volatile unsigned *)(0x20CD2038))/* TVIF Upper Blanking Area 2 Line Register */
#define TVLBA1		(*(volatile unsigned *)(0x20CD203C))	/* TVIF Lower Blanking Area 1 Line Register */
#define TVLNBA		(*(volatile unsigned *)(0x20CD2040))	/* TVIF Lower Non-blanking Area Line Register */
#define TVLBA2		(*(volatile unsigned *)(0x20CD2044))	/* TVIF Lower Blanking Area 2 Line Register */
#define TVBLEN		(*(volatile unsigned *)(0x20CD2048))	/* TVIF Line Blanking Length Register */
#define TVVLEN		(*(volatile unsigned *)(0x20CD204C))	/* TVIF Line Video Length Register */
#define ITVHSCR		(*(volatile unsigned *)(0x20CD2050))	/* TVIF Hsync Configure Register */
#define ITVVSHCR	(*(volatile unsigned *)(0x20CD2054))	/* TVIF Vsync Upper Configure Register */
#define TVVSLCR		(*(volatile unsigned *)(0x20CD2058))	/* TVIF Vsync lower Configure Register */
#define TVXSIZE		(*(volatile unsigned *)(0x20CD205C))	/* TVIF Display Horizontal Size Register */
#define TVYSIZE		(*(volatile unsigned *)(0x20CD2060))	/* TVIF Display Vertical Size Register */

//LCDCON1
#define IMAP_LCDCON1_CLKVAL_MSK		(~(0x3ff<<8))
#define IMAP_LCDCON1_CLKVAL(x)			(((x)&0x3ff)<<8)
#define IMAP_LCDCON1_PNRMODE_MSK		(~(0x3<<5))
#define IMAP_LCDCON1_PNRMODE_TFTLCD	(0x3<<5)
#define IMAP_LCDCON1_ENVID_DISABLE	(0x0<<0)
#define IMAP_LCDCON1_ENVID_ENABLE	(0x1<<0)
//LCDCON2
#define IMAP_LCDCON2_VBPD_MSK		(~(0xff<<24))
#define IMAP_LCDCON2_VBPD(x)		(((x)&0xff)<<24)
#define IMAP_LCDCON2_LINEVAL_MSK	(~(0x3ff<<14))
#define IMAP_LCDCON2_LINEVAL(x)	(((x)&0x3ff)<<14)
#define IMAP_LCDCON2_VFPD_MSK		(~(0xff<<6))
#define IMAP_LCDCON2_VFPD(x)		(((x)&0xff)<<6)
#define IMAP_LCDCON2_VSPW_MSK	(	~(0x3f<<0))
#define IMAP_LCDCON2_VSPW(x)		(((x)&0x3f)<<0)
//LCDCON3
#define IMAP_LCDCON3_HBPD_MSK		(~(0x7f<<19))
#define IMAP_LCDCON3_HBPD(x)		(((x)&0x7f)<<19)
#define IMAP_LCDCON3_HOZVAL_MSK	(~(0x3ff<<8))
#define IMAP_LCDCON3_HOZVAL(x)		(((x)&0x3ff)<<8)
#define IMAP_LCDCON3_HFPD_MSK		(~(0xff<<0))
#define IMAP_LCDCON3_HFPD(x)		(((x)&0xff)<<0)
//LCDCON4
#define IMAP_LCDCON4_HSPW_MSK	(~(0xff<<0))
#define IMAP_LCDCON4_HSPW(x)		(((x)&0xff)<<0)
//LCDCON5
#define IMAP_LCDCON5_INVVCLK_FALLING_EDGE	(0x0<<10)
#define IMAP_LCDCON5_INVVCLK_RISING_EDGE		(0x1<<10)
#define IMAP_LCDCON5_INVVLINE_NORMAL			(0x0<<9)
#define IMAP_LCDCON5_INVVLINE_INVERTED		(0x1<<9)
#define IMAP_LCDCON5_INVVFRAME_NORMAL		(0x0<<8)
#define IMAP_LCDCON5_INVVFRAME_INVERTED		(0x1<<8)
#define IMAP_LCDCON5_INVVD_NORMAL			(0x0<<7)
#define IMAP_LCDCON5_INVVD_INVERTED			(0x1<<7)
#define IMAP_LCDCON5_INVVDEN_NORMAL			(0x0<<6)
#define IMAP_LCDCON5_INVVDEN_INVERTED		(0x1<<6)
#define IMAP_LCDCON5_INVPWREN_NORMAL		(0x0<<5)
#define IMAP_LCDCON5_INVPWREN_INVERTED		(0x1<<5)
#define IMAP_LCDCON5_PWREN_DISABLE			(0x0<<3)
#define IMAP_LCDCON5_PWREN_ENABLE			(0x1<<3)
#define IMAP_LCDCON5_BSWP_DISABLE			(0x0<<1)
#define IMAP_LCDCON5_BSWP_ENABLE				(0x1<<1)
#define IMAP_LCDCON5_HWSWP_DISABLE			(0x0<<0)
#define IMAP_LCDCON5_HWSWP_ENABLE			(0x1<<0)
//OVCDCR
#define IMAP_OVCDCR_ENREFETCH_DISABLE	(0x0<<9)
#define IMAP_OVCDCR_ENREFETCH_ENABLE		(0x1<<9)
#define IMAP_OVCDCR_ENRELAX_DISABLE		(0x0<<8)
#define IMAP_OVCDCR_ENRELAX_ENABLE		(0x1<<8)
#define IMAP_OVCDCR_WAIT_TIME_MSK		(~(0xf<<4))
#define IMAP_OVCDCR_WAIT_TIME(x)			(((x)&0xf)<<4)
#define IMAP_OVCDCR_SAFEBAND_DISABLE		(0x0<<3)
#define IMAP_OVCDCR_SAFEBAND_ENABLE		(0x1<<3)
#define IMAP_OVCDCR_ALLFETCH_DISABLE		(0x0<<2)
#define IMAP_OVCDCR_ALLFETCH_ENABLE		(0x1<<2)
#define IMAP_OVCDCR_IFTYPE_RGB			(0x0<<1)
#define IMAP_OVCDCR_IFTYPE_BT601			(0x1<<1)
#define IMAP_OVCDCR_TVIF_PROGRESSIVE		(0x0<<0)
#define IMAP_OVCDCR_TVIF_INTERLACE		(0x1<<0)
//OVCPCR
#define IMAP_OVCPCR_UPDATEPAL_NORMAL	(0x0<<15)
#define IMAP_OVCPCR_UPDATEPAL_ENABLE		(0x1<<15)
#define IMAP_OVCPCR_W3PALFM_MSK			(~(0x7<<9))
#define IMAP_OVCPCR_W3PALFM_ARGB555		(0x5<<9)
#define IMAP_OVCPCR_W3PALFM_RGB565		(0x6<<9)
#define IMAP_OVCPCR_W2PALFM_MSK			(~(0x7<<6))
#define IMAP_OVCPCR_W2PALFM_ARGB555		(0x5<<6)
#define IMAP_OVCPCR_W2PALFM_RGB565		(0x6<<6)
#define IMAP_OVCPCR_W1PALFM_MSK			(~(0x7<<3))
#define IMAP_OVCPCR_W1PALFM_ARGB888		(0x0<<3)
#define IMAP_OVCPCR_W1PALFM_RGB888		(0x1<<3)
#define IMAP_OVCPCR_W1PALFM_ARGB666		(0x2<<3)
#define IMAP_OVCPCR_W1PALFM_ARGB665		(0x3<<3)
#define IMAP_OVCPCR_W1PALFM_RGB666		(0x4<<3)
#define IMAP_OVCPCR_W1PALFM_ARGB555		(0x5<<3)
#define IMAP_OVCPCR_W1PALFM_RGB565		(0x6<<3)
#define IMAP_OVCPCR_W0PALFM_MSK			(~(0x7<<0))
#define IMAP_OVCPCR_W0PALFM_ARGB888		(0x0<<0)
#define IMAP_OVCPCR_W0PALFM_RGB888		(0x1<<0)
#define IMAP_OVCPCR_W0PALFM_ARGB666		(0x2<<0)
#define IMAP_OVCPCR_W0PALFM_ARGB665		(0x3<<0)
#define IMAP_OVCPCR_W0PALFM_RGB666		(0x4<<0)
#define IMAP_OVCPCR_W0PALFM_ARGB555		(0x5<<0)
#define IMAP_OVCPCR_W0PALFM_RGB565		(0x6<<0)
//OVCBKCOLOR
#define IMAP_OVCBKCOLOR_BKCOLOR_MSK		(~(0xffffff<<0))
#define IMAP_OVCBKCOLOR_BKCOLOR(x)		(((x)&0xffffff)<<0)
//OVCWxCR
#define IMAP_OVCW3CR_OPSEL_MSK					(~(0x7<<19))
#define IMAP_OVCW3CR_OPSEL_INVFT_XOR_BKCOL		(0x1<<19)
#define IMAP_OVCW3CR_OPSEL_FT_OR_BKCOL			(0x2<<19)
#define IMAP_OVCW3CR_OPSEL_FT_XOR_INVBKCOL		(0x3<<19)
#define IMAP_OVCW3CR_OPSEL_FT_AND_BKCOL			(0x4<<19)
#define IMAP_OVCW3CR_PALSEL_RAMPALETTE0			(0x0<<18)
#define IMAP_OVCW3CR_PALSEL_RAMPALETTE1			(0x1<<18)
#define IMAP_OVCW3CR_RAMPAL_NOTUSE				(0x0<<17)
#define IMAP_OVCW3CR_RAMPAL_USE					(0x1<<17)
#define IMAP_OVCW3CR_CURAND_DISABLE				(0x0<<16)
#define IMAP_OVCW3CR_CURAND_ENABLE				(0x1<<16)
#define IMAP_OVCWxCR_BUFSEL_MSK					(~(0x3<<17))
#define IMAP_OVCWxCR_BUFSEL_BUF0					(0x0<<17)
#define IMAP_OVCWxCR_BUFSEL_BUF1					(0x1<<17)
#define IMAP_OVCWxCR_BUFSEL_BUF2					(0x2<<17)
#define IMAP_OVCWxCR_BUFSEL_BUF3					(0x3<<17)
#define IMAP_OVCWxCR_BUFAUTOEN_DISABLE			(0x0<<16)
#define IMAP_OVCWxCR_BUFAUTOEN_ENABLE			(0x1<<16)
#define IMAP_OVCWxCR_BUFNUM_MSK					(~(0x3<<14))
#define IMAP_OVCWxCR_BUFNUM_2BUFS				(0x0<<14)
#define IMAP_OVCWxCR_BUFNUM_3BUFS				(0x2<<14)
#define IMAP_OVCWxCR_BUFNUM_4BUFS				(0x3<<14)
#define IMAP_OVCWxCR_BITSWP_DISABLE				(0x0<<12)
#define IMAP_OVCWxCR_BITSWP_ENABLE				(0x1<<12)
#define IMAP_OVCWxCR_BIT2SWP_DISABLE				(0x0<<11)
#define IMAP_OVCWxCR_BIT2SWP_ENABLE				(0x1<<11)
#define IMAP_OVCWxCR_BIT4SWP_DISABLE				(0x0<<10)
#define IMAP_OVCWxCR_BIT4SWP_ENABLE				(0x1<<10)
#define IMAP_OVCWxCR_BYTSWP_DISABLE				(0x0<<9)
#define IMAP_OVCWxCR_BYTSWP_ENABLE				(0x1<<9)
#define IMAP_OVCWxCR_HAWSWP_DISABLE				(0x0<<8)
#define IMAP_OVCWxCR_HAWSWP_ENABLE				(0x1<<8)
#define IMAP_OVCWxCR_ALPHA_SEL_0					(0x0<<7)
#define IMAP_OVCWxCR_ALPHA_SEL_1					(0x1<<7)
#define IMAP_OVCWxCR_BLD_PIX_PLANE				(0x0<<6)
#define IMAP_OVCWxCR_BLD_PIX_PIXEL				(0x1<<6)
#define IMAP_OVCWxCR_BPPMODE_MSK				(~(0x1f<<1))
#define IMAP_OVCWxCR_BPPMODE_1BPP				(0x0<<1)
#define IMAP_OVCWxCR_BPPMODE_2BPP				(0x1<<1)
#define IMAP_OVCWxCR_BPPMODE_4BPP				(0x2<<1)
#define IMAP_OVCWxCR_BPPMODE_8BPP				(0x3<<1)
#define IMAP_OVCWxCR_BPPMODE_8BPP_ARGB232		(0x4<<1)
#define IMAP_OVCWxCR_BPPMODE_16BPP_RGB565		(0x5<<1)
#define IMAP_OVCWxCR_BPPMODE_16BPP_ARGB555		(0x6<<1)
#define IMAP_OVCWxCR_BPPMODE_16BPP_IRGB555		(0x7<<1)
#define IMAP_OVCWxCR_BPPMODE_18BPP_RGB666		(0x8<<1)
#define IMAP_OVCWxCR_BPPMODE_18BPP_ARGB665		(0x9<<1)
#define IMAP_OVCWxCR_BPPMODE_19BPP_ARGB666		(0xa<<1)
#define IMAP_OVCWxCR_BPPMODE_24BPP_RGB888		(0xb<<1)
#define IMAP_OVCWxCR_BPPMODE_24BPP_ARGB887		(0xc<<1)
#define IMAP_OVCWxCR_BPPMODE_25BPP_ARGB888		(0xd<<1)
#define IMAP_OVCWxCR_BPPMODE_28BPP_A4RGB888	(0xe<<1)
#define IMAP_OVCWxCR_BPPMODE_16BPP_A4RGB444	(0xf<<1)
#define IMAP_OVCWxCR_BPPMODE_32BPP_A8RGB888	(0x10<<1)
#define IMAP_OVCWxCR_BPPMODE_YCBCR				(0x11<<1)
#define IMAP_OVCWxCR_ENWIN_DISABLE				(0x0<<0)
#define IMAP_OVCWxCR_ENWIN_ENABLE				(0x1<<0)
//OVCWxPCAR
#define IMAP_OVCWxPCAR_LEFTTOPX_MSK		(~(0x7ff<<16))
#define IMAP_OVCWxPCAR_LEFTTOPX(x)		(((x)&0x7ff)<<16)
#define IMAP_OVCWxPCAR_LEFTTOPY_MSK		(~(0x7ff<<0))
#define IMAP_OVCWxPCAR_LEFTTOPY(x)		(((x)&0x7ff)<<0)
//OVCWxPCBR
#define IMAP_OVCWxPCBR_RIGHTBOTX_MSK	(~(0x7ff<<16))
#define IMAP_OVCWxPCBR_RIGHTBOTX(x)		(((x)&0x7ff)<<16)
#define IMAP_OVCWxPCBR_RIGHTBOTY_MSK	(~(0x7ff<<0))
#define IMAP_OVCWxPCBR_RIGHTBOTY(x)		(((x)&0x7ff)<<0)
//OVCWxPCCR
#define IMAP_OVCWxPCCR_ALPHA0_R_MSK		(~(0xf<<20))
#define IMAP_OVCWxPCCR_ALPHA0_R(x)		(((x)&0xf)<<20)
#define IMAP_OVCWxPCCR_ALPHA0_G_MSK		(~(0xf<<16))
#define IMAP_OVCWxPCCR_ALPHA0_G(x)		(((x)&0xf)<<16)
#define IMAP_OVCWxPCCR_ALPHA0_B_MSK		(~(0xf<<12))
#define IMAP_OVCWxPCCR_ALPHA0_B(x)		(((x)&0xf)<<12)
#define IMAP_OVCWxPCCR_ALPHA1_R_MSK		(~(0xf<<8))
#define IMAP_OVCWxPCCR_ALPHA1_R(x)		(((x)&0xf)<<8)
#define IMAP_OVCWxPCCR_ALPHA1_G_MSK		(~(0xf<<4))
#define IMAP_OVCWxPCCR_ALPHA1_G(x)		(((x)&0xf)<<4)
#define IMAP_OVCWxPCCR_ALPHA1_B_MSK		(~(0xf<<0))
#define IMAP_OVCWxPCCR_ALPHA1_B(x)		(((x)&0xf)<<0)
//OVCWxB0SAR
#define IMAP_OVCWxB0SAR_BUFADDR0_MSK	(~0xffffffff)
#define IMAP_OVCWxB0SAR_BUFADDR0(x)		((x)&0xffffffff)
//OVCWxB1SAR
#define IMAP_OVCWxB1SAR_BUFADDR1_MSK	(~0xffffffff)
#define IMAP_OVCWxB1SAR_BUFADDR1(x)		((x)&0xffffffff)
//OVCWxVSSR
#define IMAP_OVCWxVSSR_BUF3_BITADR_MSK	(~(0x7<<28))
#define IMAP_OVCWxVSSR_BUF3_BITADR(x)	(((x)&0x7)<<28)
#define IMAP_OVCWxVSSR_BUF2_BITADR_MSK	(~(0x7<<24))
#define IMAP_OVCWxVSSR_BUF2_BITADR(x)	(((x)&0x7)<<24)
#define IMAP_OVCWxVSSR_BUF1_BITADR_MSK	(~(0xf<<20))
#define IMAP_OVCWxVSSR_BUF1_BITADR(x)	(((x)&0xf)<<20)
#define IMAP_OVCWxVSSR_BUF0_BITADR_MSK	(~(0xf<<16))
#define IMAP_OVCWxVSSR_BUF0_BITADR(x)	(((x)&0xf)<<16)
#define IMAP_OVCWxVSSR_VW_WIDTH_MSK	(~(0xffff<<0))
#define IMAP_OVCWxVSSR_VW_WIDTH(x)		(((x)&0xffff)<<0)
//OVCWxCMR
#define IMAP_OVCWxCMR_MAPCOLEN_DISABLE	(0x0<<24)
#define IMAP_OVCWxCMR_MAPCOLEN_ENABLE	(0x1<<24)
#define IMAP_OVCWxCMR_MAPCOLOR_MSK		(~(0xffffff<<0))
#define IMAP_OVCWxCMR_MAPCOLOR(x)		(((x)&0xffffff)<<0)
//OVCWxCKCR
#define IMAP_OVCWxCKCR_KEYBLEN_DISABLE		(0x0<<26)
#define IMAP_OVCWxCKCR_KEYBLEN_ENABLE		(0x1<<26)
#define IMAP_OVCWxCKCR_KEYEN_DISABLE			(0x0<<25)
#define IMAP_OVCWxCKCR_KEYEN_ENABLE			(0x1<<25)
#define IMAP_OVCWxCKCR_DIRCON_FOREGROUND	(0x0<<24)
#define IMAP_OVCWxCKCR_DIRCON_BACKGROUND	(0x1<<24)
#define IMAP_OVCWxCKCR_COMPKEY_MSK			(~(0xffffff<<0))
#define IMAP_OVCWxCKCR_COMPKEY(x)				(((x)&0xffffff)<<0)
//OVCWxB2SAR
#define IMAP_OVCWxB0SAR_BUFADDR2_MSK	(~0xffffffff)
#define IMAP_OVCWxB0SAR_BUFADDR2(x)		((x)&0xffffffff)
//OVCWxB3SAR
#define IMAP_OVCWxB0SAR_BUFADDR3_MSK	(~0xffffffff)
#define IMAP_OVCWxB0SAR_BUFADDR3(x)		((x)&0xffffffff)
#endif
