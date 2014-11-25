#include <rtthread.h>
#include <board.h>

#ifdef RT_USING_RTGUI
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>

/**
* VOL-:XUNRTS1  <---> PE14/EINT4[14]  left
* VOL+:XNDCS1N  <---> GPA[5]/EINT1[5]  right 
* HOME:XUTXD1   <---> 
* MENU:XSD2DAT3 <---> GPO[11]/EINT4[27] enter
*/
#define key_right_GETVALUE()     (IMAP_GPA->DAT&(1<<5))      
#define key_left_GETVALUE()      (IMAP_GPE->DAT&(1<<14))        
#define key_enter_GETVALUE()     (IMAP_GPO->DAT&(1<<11))       


/************************************************************************************************************
*函数名： Key_GPIO_Config()
*参数：void
*返回值：void
*功能：按键GPIO的初始化函数，使用按键前必须先调用此函数进行初始化
************************************************************************************************************/
static void key_gpio_config(void)
{
	IMAP_GPA->CON &= ~(0x03 << 10);
	IMAP_GPE->CON &= ~(0x03 << 28);
	IMAP_GPO->CON &= ~(0x03 << 22);
}

static void key_thread_entry(void *parameter)
{
    rt_time_t next_delay;
    struct rtgui_event_kbd kbd_event;

    key_gpio_config();

    /* init keyboard event */
    RTGUI_EVENT_KBD_INIT(&kbd_event);
    kbd_event.wid = RT_NULL;
    kbd_event.mod  = RTGUI_KMOD_NONE;
    kbd_event.unicode = 0;

    while (1)
    {
        next_delay = 10;
        kbd_event.key = RTGUIK_UNKNOWN;
        kbd_event.type = RTGUI_KEYDOWN;

        if (key_enter_GETVALUE() == 0)
        {
            rt_thread_delay(next_delay * 4);
            if (key_enter_GETVALUE() == 0)
            {
                /* HOME key */
                rt_kprintf("key_home\n");
                kbd_event.key  = RTGUIK_HOME;
            }
            else
            {
                rt_kprintf("key_enter\n");
                kbd_event.key  = RTGUIK_RETURN;
            }
        }

        if (key_left_GETVALUE()    == 0)
        {
            rt_kprintf("key_left\n");
            kbd_event.key  = RTGUIK_LEFT;
        }

        if (key_right_GETVALUE()  == 0)
        {
            rt_kprintf("key_right\n");
            kbd_event.key  = RTGUIK_RIGHT;
        }


        if (kbd_event.key != RTGUIK_UNKNOWN)
        {
            /* post down event */
            rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));

            next_delay = 10;
            /* delay to post up event */
            rt_thread_delay(next_delay);

            /* post up event */
            kbd_event.type = RTGUI_KEYUP;
            rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));
        }

        /* wait next key press */
        rt_thread_delay(next_delay);
    }
}

int rt_hw_key_init(void)
{
    rt_thread_t key_tid;
    key_tid = rt_thread_create("key",
                               key_thread_entry, RT_NULL,
                               512, RTGUI_SVR_THREAD_PRIORITY - 1, 5);
    if (key_tid != RT_NULL) rt_thread_startup(key_tid);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_key_init);

#endif
