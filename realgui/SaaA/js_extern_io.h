/**
 * @file js_user.h
 * @author howie_wang (howie_wang@realtek.com.cn)
 * @brief
 * @version 0.1
 * @date 2023-11-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __JS_EXTERN_IO_H__
#define __JS_EXTERN_IO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "js_user.h"



typedef enum
{
// js extern io event define, 1 byte
    EXTERN_EVENT_NULL,
    EXTERN_EVENT_SMARTHOME      = 0x01,
    EXTERN_EVENT_TIMER          = 0x02,
    EXTERN_EVENT_WIFI           = 0x03,
    EXTERN_EVENT_KEY            = 0x04,
// js smarthome: subevent define,  1 byte
    SH_EVENT_IOT_SWITCH         = 1,

// js wifi manage: subevent define,  1 byte
    WIFI_EVENT_MANAGE_ON            = 0x00,
    WIFI_EVENT_MANAGE_OFF           = 0x01,
    WIFI_EVENT_MANAGE_SCAN          = 0x02,
    WIFI_EVENT_MANAGE_CONNECT       = 0x03,
    WIFI_EVENT_MANAGE_DISCONNECT    = 0x04,
// js key manage: subevent define,  1 byte
    KEY_EVENT_PRESS                 = 0x00,
    KEY_EVENT_CLICK                 = 0x01,
    KEY_EVENT_LONG_PRESS            = 0x02,
    KEY_EVENT_RELEASE               = 0x03,

// js xxx event define


} JS_EXTERN_EVENT_ENUM;


// size and mem alignment refer to gui_msg_t
#ifdef  __CC_ARM
#pragma anon_unions
#endif
// typedef struct gui_msg
// {
//     uint16_t event;
//     gui_msg_cb cb;  // typedef void (*gui_msg_cb)(void *);
//     void *payload;
// } gui_msg_t;

typedef struct
{
    /* the event type */
    // uint16_t event;
    /* user field of event */
    union
    {
        uint32_t  param;
        uint8_t extern_event_type;
        gui_msg_cb cb;    // gui_msg
    };
    union
    {
        void  *data;
        uint8_t *data_rsv;   // reserve
        void *payload;   // gui_msg
    };
} gui_msg_js_t;



void gui_extern_event_js_handler(gui_msg_t *msg);

#ifdef __cplusplus
}
#endif

#endif
