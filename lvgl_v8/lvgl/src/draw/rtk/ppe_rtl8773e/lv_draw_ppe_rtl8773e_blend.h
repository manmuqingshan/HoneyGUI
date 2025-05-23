/**
 * @file lv_draw_rtk_ppe_blend_v2.h
 *
 */

#ifndef LV_DRAW_PPE_BLEND_H
#define LV_DRAW_PPE_BLEND_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../../lv_conf_internal.h"

#if LV_USE_GPU_PPE_RTL8773E
#include "../misc/lv_area.h"
#include "../../sw/lv_draw_sw.h"
#include "lv_draw_ppe_rtl8773e.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_res_t lv_ppe_bare_rect_copy(lv_draw_ctx_t *draw_ctx, const lv_draw_img_dsc_t *dsc,
                               const lv_area_t *coords, const uint8_t *map_p);

lv_res_t lv_ppe_fill(const lv_area_t *dest_area, lv_draw_ctx_t *draw_ctx,
                     const lv_draw_sw_blend_dsc_t *dsc);

lv_res_t lv_ppe_blend_img(lv_draw_ctx_t *draw_ctx, const lv_draw_img_dsc_t *dsc,
                          ppe_matrix_t *inverse,
                          const lv_area_t *coords, const uint8_t *map_p, lv_img_cf_t cf);
lv_res_t lv_ppe_blit_transform(lv_draw_ctx_t *draw_ctx, const lv_draw_img_dsc_t *dsc,
                               const lv_area_t *coords, const uint8_t *map_p, lv_img_cf_t cf);
lv_res_t lv_ppe_blit_recolor(lv_draw_ctx_t *draw_ctx, const lv_draw_img_dsc_t *dsc,
                             const lv_area_t *coords, const uint8_t *map_p, lv_img_cf_t cf);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_GPU_PPE_RTL8773E*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DRAW_PPE_BLEND_H*/
