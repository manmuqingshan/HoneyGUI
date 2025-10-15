/**
\internal
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file gui_glass.h
  * @brief Glass widget header file.
  * @details Glass widget is used to simulate the refraction effect of glass
  * @author astor_zhang@realsil.com.cn
  * @date 2025/10/13
  * @version 1.0
  ***************************************************************************************
    * @attention
  * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
  ***************************************************************************************
\endinternal
  */

/*============================================================================*
 *               Define to prevent recursive inclusion
 *============================================================================*/
#ifndef __GUI_CUSTOM_GLASS_EFFECT_H__
#define __GUI_CUSTOM_GLASS_EFFECT_H__
#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                        Header Files
 *============================================================================*/
#include "guidef.h"
#include "gui_api.h"
#include "draw_img.h"
#include "gui_matrix.h"
#include "gui_obj.h"

/*============================================================================*
 *                         Types
 *============================================================================*/

/** @brief  Glass widget structure. */
#ifdef  __CC_ARM
#pragma anon_unions
#endif

typedef struct gui_glass
{
    gui_obj_t base;                    /* Base object structure. */
    draw_img_t *draw_img;              /* Drawing image structure. */

    float t_x;                         /* Translation in X direction. */
    float t_y;                         /* Translation in Y direction. */

    void *data;                        /* Glass data (address or filesystem path). */
    union
    {
        void *filename;               /* Filepath for partial draw. */
        void *ftl;                    /* FTL address. */
    };
    uint32_t storage_type  : 3;        /* Storage type: e.g., file system, flash, etc. */
    uint8_t checksum;                  /* Checksum for change detection. */
} gui_glass_t;


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
 * @brief Load the width of glass in pixel.
 *
 * @param this The glass widget pointer.
 * @return uint16_t Width of glass.
 */
uint16_t gui_glass_get_width(gui_glass_t *_this);

/**
 * @brief Load the height of glass in pixel.
 *
 * @param this The glass widget pointer.
 * @return uint16_t Height of glass.
 */
uint16_t gui_glass_get_height(gui_glass_t *_this);

/**
 * @brief Refresh the size of glass.
 *
 * @param this The glass widget pointer.
 */
void gui_glass_refresh_size(gui_glass_t *_this);

/**
 * @brief Refresh the source data of glass.
 *
 * @param this The glass widget pointer.
 */
void gui_glass_refresh_draw_data(gui_glass_t  *_this);


/**
 * @brief Set glass attributes (name, path, position).
 *
 * @param this Glass widget pointer.
 * @param name Widget name.
 * @param addr Glass data address/path.
 * @param x X-axis coordinate.
 * @param y Y-axis coordinate.
 */
void gui_glass_set_attribute(gui_glass_t  *_this,
                             const char *name,
                             void       *addr,
                             int16_t     x,
                             int16_t     y);


/**
 * @brief Translate (move) the glass.
 *
 * @param this The glass widget pointer.
 * @param t_x New X-axis coordinate.
 * @param t_y New Y-axis coordinate.
 */
void gui_glass_translate(gui_glass_t *_this, float t_x, float t_y);


/**
 * @brief Create an glass widget from memory address.
 * @note Create an glass widget and set attribute.
 * @param parent The father widget it nested in.
 * @param name Widget name.
 * @param addr The bin file address.
 * @param x The X-axis coordinate of the widget.
 * @param y The Y-axis coordinate of the widget.
 * @param w The width of the widget.
 * @param h The height of the widget.
 * @return The widget object pointer.
 */
gui_glass_t *gui_glass_create_from_mem(void       *parent,
                                       const char *name,
                                       void       *addr,
                                       int16_t     x,
                                       int16_t     y,
                                       int16_t     w,
                                       int16_t     h);

/**
 * @brief Create an glass widget from memory address.
 * @note Create an glass widget and set attribute.
 * @param parent The father widget it nested in.
 * @param name Widget name.
 * @param ftl Not xip address, use ftl address.
 * @param x The X-axis coordinate of the widget.
 * @param y The Y-axis coordinate of the widget.
 * @param w The width of the widget.
 * @param h The height of the widget.
 * @return Return the widget object pointer.
 */
gui_glass_t *gui_glass_create_from_ftl(void       *parent,
                                       const char *name,
                                       void       *ftl,
                                       int16_t     x,
                                       int16_t     y,
                                       int16_t     w,
                                       int16_t     h);

/**
 * @brief Create an glass widget from filesystem.
 *
 * @param parent The father widget it nested in.
 * @param name Widget name.
 * @param file Glass file path.
 * @param x The X-axis coordinate of the widget.
 * @param y The Y-axis coordinate of the widget.
 * @param w The width of the widget.
 * @param h The height of the widget.
 * @return gui_glass_t*.
 */
gui_glass_t *gui_glass_create_from_fs(void       *parent,
                                      const char *name,
                                      void       *file,
                                      int16_t     x,
                                      int16_t     y,
                                      int16_t     w,
                                      int16_t     h);


/**
 * @brief Get the translation in X direction.
 *
 * @param this The glass widget pointer.
 * @return Translation in X direction.
 */
float gui_glass_get_t_x(gui_glass_t *_this);

/**
 * @brief Get the translation in Y direction.
 *
 * @param this The glass widget pointer.
 * @return Translation in Y direction.
 */
float gui_glass_get_t_y(gui_glass_t *_this);


/**
 * @brief Sets the glass data for a specified glass widget.
 *
 * This function assigns the given glass data to the specified glass widget.
 * The glass data might correspond to various formats, and the format
 * should be compatible with the handling of `gui_glass_t`.
 *
 * @param widget          The pointer to the glass widget (`gui_glass_t`) for which the glass data is to be set.
 * @param glass_data_pointer  The pointer to the glass data to be set to the widget.
 *                            The data should persist as long as the widget needs it or until it is explicitly updated.
 */
void gui_glass_set_data(gui_glass_t *_this, const uint8_t *glass_data_pointer);

/**
 * @brief Gets the glass data from a specified glass widget.
 *
 * This function returns the current glass data that is set in the specified glass widget.
 *
 * @param widget The pointer to the glass widget (`gui_glass_t`) from which the glass data should be retrieved.
 *
 * @return A pointer to the glass data currently set in the widget. If no glass data is set, the result may be `NULL`.
 */
const uint8_t *gui_glass_get_data(gui_glass_t *_this);




#ifdef __cplusplus
}
#endif

#endif
