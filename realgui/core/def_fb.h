/**
 * @file def_vg.h
 * @author wenjing_jiang(wenjing_jiang@realsil.com.cn)
 * @brief
 * @version 0.1
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __DEF_FB_H__
#define __DEF_FB_H__



#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "def_type.h"


typedef enum t_gui_dc_type
{
    DC_RAMLESS,
    DC_SINGLE,
    DC_DOUBLE,
} T_GUI_DC_TYPE;

typedef enum t_gui_pfb_type
{
    PFB_Y_DIRECTION,
    PFB_X_DIRECTION,
} T_GUI_PFB_TYPE;


typedef struct _gui_frame_monitor_t
{
    uint32_t start;
    void (*start_cb)(void);
    uint32_t input_prepare;
    void (*input_prepare_cb)(void);
    uint32_t draw_prepare;
    void (*draw_prepare_cb)(void);
    uint32_t draw;
    void (*draw_cb)(void);
    uint32_t end;
    void (*end_cb)(void);
} gui_frame_monitor_t;

typedef struct gui_dispdev
{
    /* width and height */
    uint16_t screen_width;
    uint16_t screen_height;
    uint16_t fb_width;
    uint16_t fb_height;
    uint16_t bit_depth;
    uint16_t driver_ic_scan_line_time_us;
    uint16_t host_write_line_time_us;
    uint16_t target_w;
    uint16_t target_h;
    T_GUI_DC_TYPE type;
    T_GUI_PFB_TYPE pfb_type;
    /* pixel data */
    uint8_t *frame_buf;
    uint8_t *shot_buf;
    uint8_t *disp_buf_1;
    uint8_t *disp_buf_2;

    gui_rect_t section;
    uint32_t section_count;
    uint32_t section_total;
    void (*lcd_update)(struct gui_dispdev *dc);
    void (*direct_draw_bitmap_to_lcd)(int16_t x, int16_t y, int16_t width, int16_t height,
                                      const uint8_t *bitmap);
    void (*virtual_lcd_update)(struct gui_dispdev *dc);
    int (*flash_seq_trans_enable)(void);
    int (*flash_seq_trans_disable)(void);
    uint32_t (*get_lcd_us)(void);
    void (*reset_lcd_timer)(void);
    void (*lcd_te_wait)(void);
    void (*lcd_power_on)(void);
    void (*lcd_power_off)(void);
    void (*lcd_draw_sync)(void);
    uint8_t *lcd_gram;
    uint32_t frame_count;
    gui_frame_monitor_t *lcd_frame_monitor;
} gui_dispdev_t;


#ifdef __cplusplus
}
#endif

#endif

