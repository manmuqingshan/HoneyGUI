/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file gui_api_acc.h
  * @brief Application Programming Interface for UI
  * @details Acc Engine
  * @author sienna_shen@realsil.com.cn
  * @date 2025/3/5
  * @version 1.0
  ***************************************************************************************
    * @attention
  * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
  ***************************************************************************************
  */

/*============================================================================*
 *               Define to prevent recursive inclusion
 *============================================================================*/
#ifndef __GUI_API_ACC_H__
#define __GUI_API_ACC_H__
#ifdef __cplusplus
extern "C" {
#endif


/*============================================================================*
 *                        Header Files
 *============================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <guidef.h>

/*============================================================================*
 *                         Macros
 *============================================================================*/



/*============================================================================*
 *                         Functions
 *============================================================================*/

void gui_acc_info_register(struct acc_engine *info);

struct acc_engine *gui_get_acc(void);

#ifdef __cplusplus
}
#endif
#endif
