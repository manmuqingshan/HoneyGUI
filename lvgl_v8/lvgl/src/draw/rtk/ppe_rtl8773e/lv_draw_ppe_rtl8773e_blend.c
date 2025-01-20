/**
 * @file lv_draw_ppe_blend.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"
#if LV_USE_GPU_PPE_RTL8773E
#include "lv_draw_ppe_rtl8773e_blend.h"
#include "lv_draw_ppe_rtl8773e_utils.h"
#include "rtl_ppe.h"
#include "trace.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_res_t lv_ppe_fill(const lv_area_t *dest_area, lv_draw_ctx_t *draw_ctx,
                     const lv_draw_sw_blend_dsc_t *dsc)
{
    ppe_buffer_t target;
    memset(&target, 0, sizeof(ppe_buffer_t));
    target.address = (uint32_t)draw_ctx->buf;
    target.width = lv_area_get_width(draw_ctx->buf_area);
    target.height = lv_area_get_height(draw_ctx->buf_area);
    target.format = sizeof(lv_color_t) == 2 ? PPE_RGB565 : PPE_ARGB8888;
    target.opacity = dsc->opa;
    target.stride = target.width;
    lv_color32_t bg_color = lv_ppe_toABGR8888(dsc->color);
    ppe_rect_t rect = {.x = dest_area->x1, .w = dest_area->x2 - dest_area->x1 + 1,
                       .y = dest_area->y1, .h = dest_area->y2 - dest_area->y1 + 1
                      };
    PPE_err err = PPE_Mask(&target, bg_color.full, &rect);
    if (err == PPE_SUCCESS)
    {
        return LV_RES_OK;
    }
    else
    {
        return LV_RES_INV;
    }
}

lv_res_t lv_ppe_bare_rect_copy(lv_draw_ctx_t *draw_ctx, const lv_draw_img_dsc_t *dsc,
                               const lv_area_t *coords, const uint8_t *map_p)
{
    lv_area_t blend_area = {0};
    lv_area_t src_area = {0};
    if (!_lv_area_intersect(&blend_area, draw_ctx->buf_area, draw_ctx->clip_area))
    {
        return LV_RES_OK;
    }
    if (!_lv_area_intersect(&src_area, coords, &blend_area))
    {
        return LV_RES_OK;
    }
    lv_area_t dest_area = {0};
    lv_area_copy(&dest_area, &src_area);
    lv_area_move(&dest_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);
    lv_area_move(&src_area, -coords->x1, -coords->y1);
    lv_coord_t src_stride = lv_area_get_width(coords);
    lv_coord_t dst_stride = lv_area_get_width(draw_ctx->buf_area);
    lv_ppe_buffer_copy(draw_ctx->buf, dst_stride, &dest_area, (const void *)map_p, src_stride,
                       &src_area, sizeof(lv_color_t));
    return LV_RES_OK;
}

lv_res_t lv_ppe_blend_img(lv_draw_ctx_t *draw_ctx, const lv_draw_img_dsc_t *dsc,
                          ppe_matrix_t *matrix,
                          const lv_area_t *coords, const uint8_t *map_p, lv_img_cf_t cf)
{
    lv_area_t constraint_area;
    ppe_rect_t draw_area;
    if (_lv_area_intersect(&constraint_area, draw_ctx->buf_area, draw_ctx->clip_area))
    {
        draw_area.x = constraint_area.x1;
        draw_area.y = constraint_area.y1;
        draw_area.w = lv_area_get_width(&constraint_area);
        draw_area.h = lv_area_get_height(&constraint_area);
    }
    else
    {
        return LV_RES_OK;
    }
    ppe_buffer_t target, source;
    memset(&target, 0, sizeof(ppe_buffer_t));
    memset(&source, 0, sizeof(ppe_buffer_t));
    target.address = (uint32_t)draw_ctx->buf;
    target.width = lv_area_get_width(draw_ctx->buf_area);
    target.height = lv_area_get_height(draw_ctx->buf_area);
    target.format = sizeof(lv_color_t) == 2 ? PPE_RGB565 : PPE_ARGB8888;
    target.win_x_min = 0;
    target.win_x_max = lv_area_get_width(draw_ctx->buf_area);
    target.win_y_min = 0;
    target.win_y_max = lv_area_get_height(draw_ctx->buf_area);
    target.stride = target.width;

    source.address = (uint32_t)map_p;
    uint32_t source_width = lv_area_get_width(coords);
    uint32_t source_height = lv_area_get_height(coords);
    source.width = source_width;
    source.height = source_height;
    source.win_x_min = target.win_x_min;
    source.win_x_max = target.win_x_max;
    source.win_y_min = target.win_y_min;
    source.win_y_max = target.win_y_max;
    source.stride = source.width;
    PPE_BLEND_MODE mode = PPE_SRC_OVER_MODE;

    switch (cf)
    {
    case LV_IMG_CF_ALPHA_8BIT:
        source.format = PPE_A8;
        break;
    case LV_IMG_CF_TRUE_COLOR:
        if (LV_COLOR_DEPTH == 16)
        {
            source.format = PPE_RGB565;
        }
        if (LV_COLOR_DEPTH == 32)
        {
            source.format = PPE_ARGB8888;
        }
        break;
    case LV_IMG_CF_TRUE_COLOR_ALPHA:
        if (LV_COLOR_DEPTH == 16)
        {
            source.format = PPE_ARGB8565;
        }
        if (LV_COLOR_DEPTH == 32)
        {
            source.format = PPE_ARGB8888;
        }
        break;
    case LV_IMG_CF_RGB888:
        source.format = PPE_RGB888;
        break;
    case LV_IMG_CF_RGBA8888:
        source.format = PPE_RGBA8888;
        break;
    case LV_IMG_CF_RGBX8888:
        source.format = PPE_RGBX8888;
        break;
    case LV_IMG_CF_RGB565:
        source.format = PPE_RGB565;
        break;
    case LV_IMG_CF_RGBA5658:
        source.format = PPE_RGBA5658;
        break;
    case LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED:
        {
            if (LV_COLOR_DEPTH == 16)
            {
                source.format = PPE_ARGB8565;
            }
            if (LV_COLOR_DEPTH == 32)
            {
                source.format = PPE_ARGB8888;
            }
            lv_color32_t min = lv_ppe_toABGR8888(LV_COLOR_CHROMA_KEY);
            lv_color32_t max = {.full = min.full};
            source.color_key_enable = true;
            source.color_key_min = min.full;
            if (max.ch.blue < 0xFF)
            {
                max.ch.blue += 1;
            }
            else
            {
                return LV_RES_INV;
            }
            if (max.ch.red < 0xFF)
            {
                max.ch.red += 1;
            }
            else
            {
                return LV_RES_INV;
            }
            if (max.ch.green < 0xFF)
            {
                max.ch.green += 1;
            }
            else
            {
                return LV_RES_INV;
            }
            source.color_key_max = max.full;
        }
    default:
        return LV_RES_INV;
    }

    ppe_matrix_t inverse, pre_trans;
    memcpy(&inverse, matrix, sizeof(ppe_matrix_t));

    ppe_rect_t image_area;
    if (!ppe_get_area(&image_area, &draw_area, &inverse, &source))
    {
        return LV_RES_OK;
    }
    uint32_t size = 0;
    uint8_t *pic_buffer = lv_ppe_get_buffer(&size);
    if (image_area.w * image_area.h * PPE_Get_Pixel_Size(source.format) <= size)
    {
        lv_area_t lv_src_area = {.x1 = image_area.x, .x2 = image_area.x + image_area.w - 1, \
                                 .y1 = image_area.y, .y2 = image_area.y + image_area.h - 1
                                };
        lv_area_t lv_dst_area = {.x1 = 0, .x2 = image_area.w - 1, .y1 = 0, .y2 = image_area.h - 1};
        lv_ppe_buffer_copy(pic_buffer, image_area.w, &lv_dst_area, (const void *)map_p, \
                           source.width, &lv_src_area, PPE_Get_Pixel_Size(source.format));
        ppe_get_identity(&pre_trans);
        pre_trans.m[0][2] = image_area.x * -1.0f;
        pre_trans.m[1][2] = image_area.y * -1.0f;
        ppe_mat_multiply(&pre_trans, &inverse);
        ppe_translate(draw_ctx->buf_area->x1, draw_ctx->buf_area->y1, &pre_trans);
        memcpy(&inverse, &pre_trans, sizeof(float) * 9);
        source.width = image_area.w;
        source.height = image_area.h;
        source.stride = source.width;
        source.address = (uint32_t)pic_buffer;
    }
    else
    {
        ppe_translate(draw_ctx->buf_area->x1, draw_ctx->buf_area->y1, &inverse);
    }
    source.opacity = dsc->opa;

    lv_area_move(&constraint_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);
    ppe_rect_t draw_rect = {.x = constraint_area.x1, .y = constraint_area.y1, \
                            .w = constraint_area.x2 - constraint_area.x1 + 1, \
                            .h = constraint_area.y2 - constraint_area.y1 + 1
                           };
    if (dsc->antialias)
    {
        source.high_quality = true;
    }
    PPE_err err = PPE_Blit_Inverse(&target, &source, &inverse, &draw_rect, mode);
    PPE_Finish();
    if (err == PPE_SUCCESS)
    {
        return LV_RES_OK;
    }
    return LV_RES_INV;
}

lv_res_t lv_ppe_blit_transform(lv_draw_ctx_t *draw_ctx, const lv_draw_img_dsc_t *dsc,
                               const lv_area_t *coords, const uint8_t *map_p, lv_img_cf_t cf)
{
    lv_area_t constraint_area;
    ppe_rect_t draw_area;
    if (_lv_area_intersect(&constraint_area, draw_ctx->buf_area, draw_ctx->clip_area))
    {
        draw_area.x = constraint_area.x1;
        draw_area.y = constraint_area.y1;
        draw_area.w = lv_area_get_width(&constraint_area);
        draw_area.h = lv_area_get_height(&constraint_area);
    }
    else
    {
        return LV_RES_OK;
    }
    ppe_buffer_t target, source;
    memset(&target, 0, sizeof(ppe_buffer_t));
    memset(&source, 0, sizeof(ppe_buffer_t));
    target.address = (uint32_t)draw_ctx->buf;
    target.width = lv_area_get_width(draw_ctx->buf_area);
    target.height = lv_area_get_height(draw_ctx->buf_area);
    target.format = sizeof(lv_color_t) == 2 ? PPE_RGB565 : PPE_ARGB8888;
    target.win_x_min = 0;
    target.win_x_max = lv_area_get_width(draw_ctx->buf_area);
    target.win_y_min = 0;
    target.win_y_max = lv_area_get_height(draw_ctx->buf_area);
    target.stride = target.width;

    source.address = (uint32_t)map_p;
    uint32_t source_width = lv_area_get_width(coords);
    uint32_t source_height = lv_area_get_height(coords);
    source.width = source_width;
    source.height = source_height;
    source.win_x_min = target.win_x_min;
    source.win_x_max = target.win_x_max;
    source.win_y_min = target.win_y_min;
    source.win_y_max = target.win_y_max;
    source.stride = source.width;
    PPE_BLEND_MODE mode = PPE_SRC_OVER_MODE;

    if (LV_COLOR_DEPTH == 16)
    {
        if (cf == LV_IMG_CF_TRUE_COLOR)
        {
            source.format = PPE_RGB565;
        }
        else if (cf == LV_IMG_CF_TRUE_COLOR_ALPHA)
        {
            source.format = PPE_ARGB8565;
        }
        if (cf == LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED)
        {
            source.format = PPE_RGB565;
            lv_color32_t min = lv_ppe_toABGR8888(LV_COLOR_CHROMA_KEY);
            lv_color32_t max = {.full = min.full};
            source.color_key_enable = true;
            source.color_key_min = min.full;
            if (max.ch.blue < 0xFF)
            {
                max.ch.blue += 1;
            }
            else
            {
                return LV_RES_INV;
            }
            if (max.ch.red < 0xFF)
            {
                max.ch.red += 1;
            }
            else
            {
                return LV_RES_INV;
            }
            if (max.ch.green < 0xFF)
            {
                max.ch.green += 1;
            }
            else
            {
                return LV_RES_INV;
            }
            source.color_key_max = max.full;
        }
        else
        {
            return LV_RES_INV;
        }
    }
    else if (LV_COLOR_DEPTH == 32)
    {
        source.format = PPE_ARGB8888;
        if (cf == LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED)
        {
            source.format = PPE_ARGB8888;
            lv_color32_t min = lv_ppe_toABGR8888(LV_COLOR_CHROMA_KEY);
            lv_color32_t max = {.full = min.full};
            source.color_key_enable = true;
            source.color_key_min = min.full;
            if (max.ch.blue < 0xFF)
            {
                max.ch.blue += 1;
            }
            else
            {
                return LV_RES_INV;
            }
            if (max.ch.red < 0xFF)
            {
                max.ch.red += 1;
            }
            else
            {
                return LV_RES_INV;
            }
            if (max.ch.green < 0xFF)
            {
                max.ch.green += 1;
            }
            else
            {
                return LV_RES_INV;
            }
            source.color_key_max = max.full;
        }
    }
    else if (cf == LV_IMG_CF_RGB888)
    {
        source.format = PPE_RGB888;
    }
    else
    {
        return LV_RES_INV;
    }
    ppe_matrix_t matrix, inverse, pre_trans;
    lv_ppe_get_matrix(&matrix, coords, dsc);
    memcpy(&inverse, &matrix, sizeof(ppe_matrix_t));
    ppe_matrix_inverse(&inverse);

    ppe_rect_t image_area;
    if (!ppe_get_area(&image_area, &draw_area, &inverse, &source))
    {
        return LV_RES_OK;
    }
    uint32_t size = 0;
    uint8_t *pic_buffer = lv_ppe_get_buffer(&size);
    if (image_area.w * image_area.h * PPE_Get_Pixel_Size(source.format) <= size)
    {
        lv_area_t lv_src_area = {.x1 = image_area.x, .x2 = image_area.x + image_area.w - 1, \
                                 .y1 = image_area.y, .y2 = image_area.y + image_area.h - 1
                                };
        lv_area_t lv_dst_area = {.x1 = 0, .x2 = image_area.w - 1, .y1 = 0, .y2 = image_area.h - 1};
        lv_ppe_buffer_copy(pic_buffer, image_area.w, &lv_dst_area, (const void *)map_p, \
                           source.width, &lv_src_area, PPE_Get_Pixel_Size(source.format));
        ppe_get_identity(&pre_trans);
        pre_trans.m[0][2] = image_area.x * -1.0f;
        pre_trans.m[1][2] = image_area.y * -1.0f;
        ppe_mat_multiply(&pre_trans, &inverse);
        ppe_translate(draw_ctx->buf_area->x1, draw_ctx->buf_area->y1, &pre_trans);
        memcpy(&inverse, &pre_trans, sizeof(float) * 9);
        source.width = image_area.w;
        source.height = image_area.h;
        source.stride = source.width;
        source.address = (uint32_t)pic_buffer;
    }
    else
    {
        ppe_translate(draw_ctx->buf_area->x1, draw_ctx->buf_area->y1, &inverse);
    }
    source.opacity = dsc->opa;

    lv_area_move(&constraint_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);
    ppe_rect_t draw_rect = {.x = constraint_area.x1, .y = constraint_area.y1, \
                            .w = constraint_area.x2 - constraint_area.x1 + 1, \
                            .h = constraint_area.y2 - constraint_area.y1 + 1
                           };
    if (dsc->antialias)
    {
        source.high_quality = true;
    }
    PPE_err err = PPE_Blit_Inverse(&target, &source, &inverse, &draw_rect, mode);
    PPE_Finish();
    if (err == PPE_SUCCESS)
    {
        return LV_RES_OK;
    }
    return LV_RES_INV;
}

lv_res_t lv_ppe_blit_recolor(lv_draw_ctx_t *draw_ctx, const lv_draw_img_dsc_t *dsc,
                             const lv_area_t *coords, const uint8_t *map_p, lv_img_cf_t cf)
{
    lv_area_t constraint_area;
    ppe_rect_t draw_area;
    if (_lv_area_intersect(&constraint_area, draw_ctx->buf_area, draw_ctx->clip_area))
    {
        draw_area.x = constraint_area.x1;
        draw_area.y = constraint_area.y1;
        draw_area.w = lv_area_get_width(&constraint_area);
        draw_area.h = lv_area_get_height(&constraint_area);
    }
    else
    {
        return LV_RES_OK;
    }

    ppe_buffer_t target, source;
    memset(&target, 0, sizeof(ppe_buffer_t));
    memset(&source, 0, sizeof(ppe_buffer_t));
    target.address = (uint32_t)draw_ctx->buf;
    target.width = lv_area_get_width(draw_ctx->buf_area);
    target.height = lv_area_get_height(draw_ctx->buf_area);
    target.format = sizeof(lv_color_t) == 2 ? PPE_RGB565 : PPE_ARGB8888;
    target.win_x_min = 0;
    target.win_x_max = lv_area_get_width(draw_ctx->buf_area);
    target.win_y_min = 0;
    target.win_y_max = lv_area_get_height(draw_ctx->buf_area);
    target.stride = target.width;

    source.address = (uint32_t)map_p;
    uint32_t source_width = lv_area_get_width(coords);
    uint32_t source_height = lv_area_get_height(coords);
    source.width = source_width;
    source.height = source_height;
    source.win_x_min = target.win_x_min;
    source.win_x_max = target.win_x_max;
    source.win_y_min = target.win_y_min;
    source.win_y_max = target.win_y_max;
    source.stride = source.width;
    PPE_BLEND_MODE mode = PPE_SRC_OVER_MODE;

    switch (cf)
    {
    case LV_IMG_CF_ALPHA_8BIT:
        source.format = PPE_A8;
        break;
    case LV_IMG_CF_TRUE_COLOR:
        if (LV_COLOR_DEPTH == 16)
        {
            source.format = PPE_RGB565;
        }
        if (LV_COLOR_DEPTH == 32)
        {
            source.format = PPE_ARGB8888;
        }
        break;
    case LV_IMG_CF_TRUE_COLOR_ALPHA:
        if (LV_COLOR_DEPTH == 16)
        {
            source.format = PPE_ARGB8565;
        }
        if (LV_COLOR_DEPTH == 32)
        {
            source.format = PPE_ARGB8888;
        }
        break;
    case LV_IMG_CF_RGB888:
        source.format = PPE_RGB888;
        break;
    case LV_IMG_CF_RGBA8888:
        source.format = PPE_RGBA8888;
        break;
    case LV_IMG_CF_RGBX8888:
        source.format = PPE_RGBX8888;
        break;
    case LV_IMG_CF_RGB565:
        source.format = PPE_RGB565;
        break;
    case LV_IMG_CF_RGBA5658:
        source.format = PPE_RGBA5658;
        break;
    case LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED:
        {
            if (LV_COLOR_DEPTH == 16)
            {
                source.format = PPE_ARGB8565;
            }
            if (LV_COLOR_DEPTH == 32)
            {
                source.format = PPE_ARGB8888;
            }
            if (cf == LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED)
            {
                lv_color32_t min = lv_ppe_toABGR8888(LV_COLOR_CHROMA_KEY);
                lv_color32_t max = {.full = min.full};
                source.color_key_enable = true;
                source.color_key_min = min.full;
                if (max.ch.blue < 0xFF)
                {
                    max.ch.blue += 1;
                }
                else
                {
                    return LV_RES_INV;
                }
                if (max.ch.red < 0xFF)
                {
                    max.ch.red += 1;
                }
                else
                {
                    return LV_RES_INV;
                }
                if (max.ch.green < 0xFF)
                {
                    max.ch.green += 1;
                }
                else
                {
                    return LV_RES_INV;
                }
                source.color_key_max = max.full;
            }
        }
    default:
        return LV_RES_INV;
    }
    ppe_matrix_t matrix, inverse, pre_trans;
    lv_ppe_get_matrix(&matrix, coords, dsc);
    memcpy(&inverse, &matrix, sizeof(ppe_matrix_t));
    ppe_matrix_inverse(&inverse);

    ppe_rect_t image_area;
    if (!ppe_get_area(&image_area, &draw_area, &inverse, &source))
    {
        return LV_RES_OK;
    }
    uint32_t size = 0;
    uint8_t *pic_buffer = lv_ppe_get_buffer(&size);
    if (image_area.w * image_area.h * PPE_Get_Pixel_Size(source.format) <= size)
    {
        lv_area_t lv_src_area = {.x1 = image_area.x, .x2 = image_area.x + image_area.w - 1, \
                                 .y1 = image_area.y, .y2 = image_area.y + image_area.h - 1
                                };
        lv_area_t lv_dst_area = {.x1 = 0, .x2 = image_area.w - 1, .y1 = 0, .y2 = image_area.h - 1};
        lv_ppe_buffer_copy(pic_buffer, image_area.w, &lv_dst_area, (const void *)map_p, \
                           source.width, &lv_src_area, PPE_Get_Pixel_Size(source.format));
        ppe_get_identity(&pre_trans);
        pre_trans.m[0][2] = image_area.x * -1.0f;
        pre_trans.m[1][2] = image_area.y * -1.0f;
        ppe_mat_multiply(&pre_trans, &inverse);
        ppe_translate(draw_ctx->buf_area->x1, draw_ctx->buf_area->y1, &pre_trans);
        memcpy(&inverse, &pre_trans, sizeof(float) * 9);
        source.width = image_area.w;
        source.height = image_area.h;
        source.address = (uint32_t)pic_buffer;
        source.stride = source.width;
    }
    else
    {
        return LV_RES_INV;
    }

    lv_color32_t recolor_value = lv_ppe_toABGR8888(dsc->recolor);
    recolor_value.ch.alpha = dsc->recolor_opa;
    source.opacity = 0xFF;
    ppe_rect_t recolor_rect = {.x = 0, .y = 0, .w = source.width, .h = source.height};
    PPE_Mask(&source, recolor_value.full, &recolor_rect);

    source.opacity = dsc->opa;

    lv_area_move(&constraint_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);
    ppe_rect_t draw_rect = {.x = constraint_area.x1, .y = constraint_area.y1, \
                            .w = constraint_area.x2 - constraint_area.x1 + 1, \
                            .h = constraint_area.y2 - constraint_area.y1 + 1
                           };
    if (dsc->antialias)
    {
        source.high_quality = true;
    }
    PPE_err err = PPE_Blit_Inverse(&target, &source, &inverse, &draw_rect, mode);
    PPE_Finish();
    if (err == PPE_SUCCESS)
    {
        return LV_RES_OK;
    }
    return LV_RES_INV;
}

lv_res_t lv_ppe_mask(lv_draw_ctx_t *draw_ctx, const lv_draw_sw_blend_dsc_t *dsc)
{
    ppe_buffer_t target, source;
    memset(&target, 0, sizeof(ppe_buffer_t));
    memset(&source, 0, sizeof(ppe_buffer_t));
    target.address = (uint32_t)draw_ctx->buf;
    target.width = lv_area_get_width(draw_ctx->buf_area);
    target.height = lv_area_get_height(draw_ctx->buf_area);
    target.format = sizeof(lv_color_t) == 2 ? PPE_RGB565 : PPE_ARGB8888;
    target.win_x_min = 0;
    target.win_x_max = lv_area_get_width(draw_ctx->buf_area);
    target.win_y_min = 0;
    target.win_y_max = lv_area_get_height(draw_ctx->buf_area);
    target.stride = target.width;

    source.address = (uint32_t)dsc->mask_buf;
    source.width = dsc->mask_area->x2 - dsc->mask_area->x1 + 1;
    source.height = dsc->mask_area->y2 - dsc->mask_area->y1 + 1;
    source.format = PPE_A8;
    source.stride = source.width;
    // target.win_x_min = target.win_x_min;
    // target.win_x_max = target.win_x_max;
    // target.win_y_min = target.win_y_min;
    // target.win_y_max = target.win_y_max;

    ppe_matrix_t inverse;
    ppe_get_identity(&inverse);
    lv_area_t constraint_area;
    lv_area_move(&constraint_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);
    ppe_rect_t draw_rect = {.x = constraint_area.x1, .y = constraint_area.y1, \
                            .w = constraint_area.x2 - constraint_area.x1 + 1, \
                            .h = constraint_area.y2 - constraint_area.y1 + 1
                           };
    PPE_err err = PPE_Blit_Inverse(&target, &source, &inverse, &draw_rect, PPE_SRC_OVER_MODE);
    PPE_Finish();
    if (err == PPE_SUCCESS)
    {
        return LV_RES_OK;
    }
    else
    {
        return LV_RES_INV;
    }
}


#endif /*LV_USE_GPU_RTK_PPE*/
