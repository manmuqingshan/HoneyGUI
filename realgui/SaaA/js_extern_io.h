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
typedef struct
{
//
    union
    {
        struct
        {
            uint16_t gui_event;  // fixed
            union
            {
                struct
                {
                    uint8_t js_event;       // module
                    uint8_t js_subevent;    // module internal event
                };
                uint16_t gui_sub_event;
            };
            gui_msg_cb gui_cb;   // fixed
            union
            {
                uint32_t data32;            // data
                uint8_t data[4];            // data
                void *pdata;
                void *gui_payload;
            };
        };
        //
        gui_msg_t gui_msg;
    };
} gui_msg_js_t;

void gui_send_msg_to_js(uint8_t event, uint8_t subevent, void *data);
void gui_extern_event_js_handler(gui_msg_t *msg);

#ifdef __cplusplus
}
#endif

#endif
