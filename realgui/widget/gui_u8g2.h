/**
 \internal
*****************************************************************************************
*     Copyright(c) 2024, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file gui_u8g2.h
  * @brief u8g2 widget header file
  * @details u8g2 widget header file
  * @author luke_sun@realsil.com.cn
  * @date 2024/07/03
  * @version v1.0
  ***************************************************************************************
    * @attention
  * <h2><center>&copy; COPYRIGHT 2024 Realtek Semiconductor Corporation</center></h2>
  ***************************************************************************************
 \endinternal
  */

/*============================================================================*
 *               Define to prevent recursive inclusion
 *============================================================================*/
#ifndef __GUI_U8G2_H__
#define __GUI_U8G2_H__
#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                        Header Files
 *============================================================================*/

#include "guidef.h"
#include "gui_api.h"
#include "gui_obj.h"
#include "u8g2.h"

/*============================================================================*
 *                         Types
 *============================================================================*/

typedef struct gui_u8g2
{
    gui_obj_t base;
    u8g2_t *u8g2;
    void (*u8g2_draw_cb)(u8g2_t *u8g2);
    uint8_t *buf;
} gui_u8g2_t;


/*============================================================================*
 *                         Constants
 *============================================================================*/


/*============================================================================*
 *                         Macros
 *============================================================================*/


/*============================================================================*
 *                         Variables
 *============================================================================*/


/*============================================================================*
 *                         Functions
 *============================================================================*/

/**
 * @brief
 *
 * @param this
 * @param cb
 */
void gui_u8g2_set_draw_cb(gui_u8g2_t *this, void (*cb)(u8g2_t *u8g2));


/**
 * @brief
 *
 * @param parent
 * @param name
 * @param x
 * @param y
 * @param w
 * @param h
 * @return gui_u8g2_t*
 */
gui_u8g2_t *gui_u8g2_create(void       *parent,
                            const char *name,
                            int16_t     x,
                            int16_t     y,
                            int16_t     w,
                            int16_t     h);


#ifdef __cplusplus
}
#endif

#endif