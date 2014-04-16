#ifndef __IMAP_RTC_H
#define __IMAP_RTC_H

#define RTC_BASE 0x20dc0000
#define RTCCON			(*(volatile unsigned *)(RTC_BASE+0x40))
#define TICNT			  (*(volatile unsigned *)(RTC_BASE+0x44))
#define RTCALM			(*(volatile unsigned *)(RTC_BASE+0x50))
#define ALMSEC			(*(volatile unsigned *)(RTC_BASE+0x54))
#define ALMMIN			(*(volatile unsigned *)(RTC_BASE+0x58))
#define ALMHOUR		  (*(volatile unsigned *)(RTC_BASE+0x5c))
#define ALMDATE		  (*(volatile unsigned *)(RTC_BASE+0x60))
#define ALMMON			(*(volatile unsigned *)(RTC_BASE+0x64))
#define ALMYEAR		  (*(volatile unsigned *)(RTC_BASE+0x68))
#define RTCRST			(*(volatile unsigned *)(RTC_BASE+0x6c))
#define BCDSEC			(*(volatile unsigned *)(RTC_BASE+0x70))
#define BCDMIN			(*(volatile unsigned *)(RTC_BASE+0x74))
#define BCDHOUR		  (*(volatile unsigned *)(RTC_BASE+0x78))
#define BCDDATE		  (*(volatile unsigned *)(RTC_BASE+0x7c))
#define BCDDAY			(*(volatile unsigned *)(RTC_BASE+0x80))
#define BCDMON			(*(volatile unsigned *)(RTC_BASE+0x84))
#define BCDYEAR		  (*(volatile unsigned *)(RTC_BASE+0x88))
#define ALMDAY			(*(volatile unsigned *)(RTC_BASE+0x8c))
#define RTCSET			(*(volatile unsigned *)(RTC_BASE+0x90))


#endif
