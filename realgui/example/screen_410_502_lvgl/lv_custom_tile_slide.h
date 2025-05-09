/**
 * @file lv_custom_tile_slide.h
 *
 */

#ifndef LV_CUSTOM_TILE_SLIDE_H
#define LV_CUSTOM_TILE_SLIDE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "lvgl.h"

#include "lv_display_private.h"
#include "lv_tileview_private.h"
#include "lv_area_private.h"

#if LV_USE_MATRIX
#include "lv_matrix.h"
#endif
#if LV_DRAW_TRANSFORM_USE_MATRIX
#include "lv_custom_matrix.h"
#endif
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
    CLASSIC,        /**< Default slide animation */
    FADE,           /**< Cross-fade opacity transition */
    SCALE,          /**< Zoom animation effect */
    SCALE_FADE,     /**< Combined zoom & fade effect */

    /*need matrix*/
    BOX,            /**< 3D box rotation effect */
    CUBE_ROTATION,  /**< 3D cube rotation transition */
    SPIRAL_NOTEBOOK,/**< Spiral notebook flip effect */

    EFFECT_COUNT,   /**< Total number of effects */
} SLIDE_EFFECT;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * @brief Custom tileview scroll event handler
 *
 * Handles dynamic scaling and opacity effects during scrolling:
 * - LV_EVENT_SCROLL_BEGIN: Log scroll start
 * - LV_EVENT_SCROLL:       Apply real-time transform effects
 * - LV_EVENT_SCROLL_END:   Reset child elements
 *
 * @param e LVGL event object containing event data
 */
void tileview_custom_cb(lv_event_t *e);

/**
 * @brief Create cross-shaped tileview layout
 *
 * Initializes a tileview with 5 tiles in cross pattern:
 * - Center tile (yellow background)
 * - Top tile (orange)
 * - Bottom tile (green)
 * - Left tile (blue)
 * - Right tile (pink)
 *
 * @note Each tile contains a label and colored background.
 *       Scroll directions are configured for adjacent navigation.
 */
void create_cross_tileview(void);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_CUSTOM_TILE_SLIDE_H*/
