/**
 * @file def_msg.h
 * @author wenjing_jiang(wenjing_jiang@realsil.com.cn)
 * @brief
 * @version 0.1
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __DEF_MSG_H__
#define __DEF_MSG_H__



#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef void (*gui_msg_cb)(void *);
typedef struct gui_msg
{
    uint16_t event;
    uint16_t sub_event;
    gui_msg_cb cb;
    void *payload;
} gui_msg_t;


#ifdef __cplusplus
}
#endif

#endif

