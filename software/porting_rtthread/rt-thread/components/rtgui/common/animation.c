#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/animation.h>

enum _anim_state
{
    _ANIM_STOPPED,
    _ANIM_RUNNING,
};

struct rtgui_animation
{
    struct rtgui_widget *parent;
    struct rtgui_timer  *timer;
    enum _anim_state state;

    struct rtgui_dc_buffer *bg_buf;
    struct rtgui_dc_buffer *fg_buf;
    int dc_cnt;

    unsigned int tick, tick_interval, max_tick;
    rtgui_anim_motion motion;

    rtgui_anim_engine engine;
    void *eng_ctx;

    rtgui_anim_onfinish on_finish;
};

int rtgui_anim_motion_linear(unsigned int tick, unsigned int max_tick)
{
    return tick * RTGUI_ANIM_TICK_RANGE / max_tick;
}

int rtgui_anim_motion_insquare(unsigned int tick, unsigned int max_tick)
{
    /* Care about integer overflow. tick can within 0~(4G/RTGUI_ANIM_TICK_RANGE). */
    return tick * RTGUI_ANIM_TICK_RANGE / max_tick * tick / max_tick;
}

int rtgui_anim_motion_outsquare(unsigned int tick, unsigned int max_tick)
{
    /* Care about integer overflow. tick can within 0~(4G/RTGUI_ANIM_TICK_RANGE). */
    tick = max_tick - tick;
    return RTGUI_ANIM_TICK_RANGE - (tick * RTGUI_ANIM_TICK_RANGE / max_tick *
                                    tick / max_tick);
}

void rtgui_anim_engine_move(struct rtgui_dc *background,
                            struct rtgui_dc_buffer *background_buffer,
                            struct rtgui_dc_buffer *items,
                            int item_cnt,
                            int progress,
                            void *param)
{
    int cx, cy, w, h;
    struct rtgui_anim_engine_move_ctx *ctx = param;
    struct rtgui_rect dc_rect;

    if (!(background && background_buffer && items))
        return;

    rtgui_dc_get_rect(background, &dc_rect);

    cx = progress * (ctx->end.x - ctx->start.x) / RTGUI_ANIM_TICK_RANGE;
    cy = progress * (ctx->end.y - ctx->start.y) / RTGUI_ANIM_TICK_RANGE;
    w = rtgui_rect_width(dc_rect);
    h = rtgui_rect_height(dc_rect);

    dc_rect.x1 = cx + ctx->start.x;
    dc_rect.y1 = cy + ctx->start.y;
    dc_rect.x2 = dc_rect.x1 + w;
    dc_rect.y2 = dc_rect.y1 + h;
    /* DC buffer is buggy on negative rect.{x1,y1}. */
    if (dc_rect.x1 < 0)
        dc_rect.x1 = 0;
    if (dc_rect.y1 < 0)
        dc_rect.y1 = 0;
    rtgui_dc_blit((struct rtgui_dc*)background_buffer, NULL, background, NULL);
    /* To prevent overlapping, only one item can be drawn by
     * rtgui_anim_engine_move. */
    rtgui_dc_blit((struct rtgui_dc*)(items), NULL, background, &dc_rect);
}

static void _anim_timeout(struct rtgui_timer *timer, void *parameter)
{
    struct rtgui_dc *dc;
    struct rtgui_animation *anim = parameter;

    /* There maybe timeout event pending in the queue even if the timer has
     * been stopped. */
    if (anim->state != _ANIM_RUNNING)
        return;

    anim->tick += anim->tick_interval;
    if(anim->tick > anim->max_tick)
    {
        anim->tick = anim->max_tick;
    }

    RT_ASSERT(anim->parent);
    dc = rtgui_dc_begin_drawing(anim->parent);
    if (dc == RT_NULL)
        return;

    RT_ASSERT(anim->motion);
    RT_ASSERT(anim->engine);
    anim->engine(dc, anim->bg_buf, anim->fg_buf, anim->dc_cnt,
                 anim->motion(anim->tick, anim->max_tick),
                 anim->eng_ctx);

    rtgui_dc_end_drawing(dc);

    if (anim->tick == anim->max_tick)
    {
        rtgui_anim_stop(anim);
        anim->tick = 0;
        if (anim->on_finish)
            anim->on_finish(anim);
    }
}

struct rtgui_animation* rtgui_anim_create(struct rtgui_widget *parent,
                                          int interval)
{
    struct rtgui_animation *anim = rtgui_malloc(sizeof(*anim));

    if (anim == RT_NULL)
        return RT_NULL;

    anim->timer = rtgui_timer_create(interval, RT_TIMER_FLAG_PERIODIC,
                                     _anim_timeout, anim);
    if (anim->timer == RT_NULL)
    {
        rtgui_free(anim);
        return RT_NULL;
    }

    anim->parent = parent;

    anim->fg_buf = RT_NULL;
    anim->dc_cnt = 0;

    anim->tick = 0;
    anim->tick_interval = interval;
    anim->max_tick = 0;

    /* Set default handlers. */
    anim->motion = rtgui_anim_motion_linear;
    anim->engine = RT_NULL;
    anim->eng_ctx = RT_NULL;
    anim->on_finish = rtgui_anim_destroy;
    anim->state = _ANIM_STOPPED;

    return anim;
}

void rtgui_anim_destroy(struct rtgui_animation *anim)
{
    /* Only free animation and timer. If you want to free the dc_buffer,
     * overwrite the on_finish. */
    rtgui_timer_destory(anim->timer);
    rtgui_free(anim);
}

void rtgui_anim_set_fg_buffer(struct rtgui_animation *anim,
                              struct rtgui_dc_buffer *dc,
                              int cnt)
{
    RT_ASSERT(anim);

    anim->fg_buf = dc;
    anim->dc_cnt = cnt;
}

void rtgui_anim_set_bg_buffer(struct rtgui_animation *anim,
                              struct rtgui_dc_buffer *dc)
{
    RT_ASSERT(anim);

    anim->bg_buf = dc;
}

void rtgui_anim_set_engine(struct rtgui_animation *anim,
                           rtgui_anim_engine engine,
                           void *ctx)
{
    RT_ASSERT(anim);

    anim->engine = engine;
    anim->eng_ctx = ctx;
}

void* rtgui_anim_get_engine_ctx(struct rtgui_animation *anim)
{
    RT_ASSERT(anim);

    return anim->eng_ctx;
}

unsigned int rtgui_anim_get_duration(struct rtgui_animation *anim)
{
    RT_ASSERT(anim);

    return anim->max_tick;
}

unsigned int rtgui_anim_get_cur_tick(struct rtgui_animation *anim)
{
    RT_ASSERT(anim);

    return anim->tick;
}

void rtgui_anim_set_cur_tick(struct rtgui_animation *anim, unsigned int tick)
{
    RT_ASSERT(anim);

    if (tick > RTGUI_ANIM_TICK_RANGE)
        anim->tick = RTGUI_ANIM_TICK_RANGE;
    else
        anim->tick = tick;
}

void rtgui_anim_set_onfinish(struct rtgui_animation *anim,
                             rtgui_anim_onfinish on_finish)
{
    RT_ASSERT(anim);

    anim->on_finish = on_finish;
}

void rtgui_anim_set_motion(struct rtgui_animation *anim,
                           rtgui_anim_motion motion)
{
    RT_ASSERT(anim);

    anim->motion = motion;
}

void rtgui_anim_set_duration(struct rtgui_animation *anim,
                             unsigned int tick)
{
    RT_ASSERT(anim);

    anim->max_tick = tick;
}

void rtgui_anim_start(struct rtgui_animation *anim)
{
    RT_ASSERT(anim);

    if (anim->fg_buf && anim->max_tick && anim->state == _ANIM_STOPPED)
    {
        anim->state = _ANIM_RUNNING;
        rtgui_timer_start(anim->timer);
    }
}

void rtgui_anim_stop(struct rtgui_animation *anim)
{
    RT_ASSERT(anim);

    anim->state = _ANIM_STOPPED;
    rtgui_timer_stop(anim->timer);
}

