#include <string.h>
#include <time.h>
#include <rtthread.h>
#include <board.h>
#include "drv_rtc.h"

#ifdef RT_USING_RTC
#define FIRST_DATA          0x32F2

#define BCD2BIN(x) ((x>>4)*10+(x&0x0f))
#define BIN2BCD(x) (((x/10)<<4)|(x%10))

static struct rt_device rtc;
static rt_err_t rt_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    if (dev->rx_indicate != RT_NULL)
    {
        /* Open Interrupt */
    }

    return RT_EOK;
}

static rt_size_t rt_rtc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    return 0;
}

static rt_err_t rt_rtc_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    time_t *time;

    struct tm time_temp;

    RT_ASSERT(dev != RT_NULL);
    memset(&time_temp, 0, sizeof(struct tm));

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        time = (time_t *)args;

        /* Years since 1900 : 0-99 range */
		time_temp.tm_year = BCD2BIN(IMAP_RTC->BCDYEAR)+100;
        /* Months *since* january 0-11 : RTC_Month_Date_Definitions 1 - 12 */
		time_temp.tm_mon = BCD2BIN(IMAP_RTC->BCDMON) - 1;
        /* Day of the month 1-31 : 1-31 range */
		time_temp.tm_mday = BCD2BIN(IMAP_RTC->BCDDATE);
		/* 0 - 6 : Days since Sunday (0-6) */
		time_temp.tm_wday = BCD2BIN(IMAP_RTC->BCDDAY);
        /* Hours since midnight 0-23 : 0-23 range */
		time_temp.tm_hour = BCD2BIN(IMAP_RTC->BCDHOUR);
        /* Minutes 0-59 : the 0-59 range */
		time_temp.tm_min = BCD2BIN(IMAP_RTC->BCDMIN);
        /* Seconds 0-59 : the 0-59 range */
		time_temp.tm_sec = BCD2BIN(IMAP_RTC->BCDSEC);

        *time = mktime(&time_temp);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        const struct tm *time_new;
        time = (time_t *)args;
        time_new = localtime(time);
		IMAP_RTC->RTCCON |= 0x01;
        /* 0-99 range              : Years since 1900 */
		IMAP_RTC->BCDYEAR = BIN2BCD(time_new->tm_year-100);
        /* RTC_Month_Date_Definitions 1 - 12 : Months *since* january 0-11 */
		IMAP_RTC->BCDMON = BIN2BCD(time_new->tm_mon + 1);
        /* 1-31 range : Day of the month 1-31 */
		IMAP_RTC->BCDDATE = BIN2BCD(time_new->tm_mday);
        /* 0 - 6 : Days since Sunday (0-6) */
		IMAP_RTC->BCDDAY = BIN2BCD(time_new->tm_wday);
        /* 0-23 range : Hours since midnight 0-23 */
		IMAP_RTC->BCDHOUR = BIN2BCD(time_new->tm_hour);
        /* the 0-59 range : Minutes 0-59 */
		IMAP_RTC->BCDMIN = BIN2BCD(time_new->tm_min);
        /* the 0-59 range : Seconds 0-59 */
		IMAP_RTC->BCDSEC = BIN2BCD(time_new->tm_sec);

		IMAP_RTC->RTCCON&=~0x01;
		IMAP_RTC->TICNT&=~(0x01<<7);
    }
    break;
    }

    return RT_EOK;
}

void rt_hw_rtc_init(void)
{
    rtc.type    = RT_Device_Class_RTC;

    /* register rtc device */
    rtc.init    = RT_NULL;
    rtc.open    = rt_rtc_open;
    rtc.close   = RT_NULL;
    rtc.read    = rt_rtc_read;
    rtc.write   = RT_NULL;
    rtc.control = rt_rtc_control;

    /* no private */
    rtc.user_data = RT_NULL;

    rt_device_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);

#ifdef RT_USING_FINSH
    {
        extern void list_date(void);
        list_date();
    }
#endif

    return;
}

#endif
