/**
 \internal
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file l3.h
  * @brief Lite 3D widget
  * @details Lite 3D widget
  * @author sienna_shen@realsil.com.cn
  * @date 2025/4/11
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
#ifndef __L3_H__
#define __L3_H__
#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                            Header Files
 *============================================================================*/
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "l3_common.h"

/*============================================================================*
 *                               Types
 *============================================================================*/


/**
 * @brief Callback type for global transformations.
 *
 * This callback is used to apply transformations to the entire 3D model,
 * including world coordinates and camera coordinates.
 */
typedef void (*l3_global_transform_cb)(l3_model_t *__this);

/**
 * @brief Callback type for face-specific transformations.
 *
 * This callback is used to apply transformations to a specific face of the 3D model.
 * @param face_index The index of the face to transform.
 */
typedef void (*l3_face_transform_cb)(l3_model_t *__this, size_t face_index/*face offset*/);

/*============================================================================*
 *                            Functions
 *============================================================================*/

/**
 * @brief Create a new 3D model.
 *
 * @param desc_addr Address of the model descriptor.
 * @param draw_type Drawing type for the model.
 * @param x X-coordinate of the model.
 * @param y Y-coordinate of the model.
 * @param view_w Width of the view.
 * @param view_h Height of the view.
 * @return Pointer to the created 3D model.
 */
l3_model_t *l3_create_model(void *desc_addr, L3_DRAW_TYPE draw_type, int16_t x,
                            int16_t y, int16_t view_w, int16_t view_h);

/**
 * @brief Set the target canvas for rendering.
 *
 * @param _this Pointer to the 3D model.
 * @param x X-coordinate of the canvas.
 * @param y Y-coordinate of the canvas.
 * @param w Width of the canvas.
 * @param h Height of the canvas.
 * @param bit_depth Bit depth of the canvas.
 * @param canvas Pointer to the canvas buffer.
 */
void l3_set_target_canvas(l3_model_t *_this, \
                          uint16_t x, uint16_t y, \
                          uint16_t w, uint16_t h, \
                          uint16_t bit_depth, \
                          uint8_t *canvas);

/**
 * @brief Set the image for a specific face of the model.
 *
 * @param this Pointer to the 3D model.
 * @param face_index Index of the face.
 * @param image_addr Address of the image data.
 */
void l3_set_face_image(l3_model_t *_this, uint8_t face_index, void *image_addr);

/**
 * @brief Set global transform callback.
 *
 * @param _this the 3D model pointer
 * @param cb Set callback functions for the world coordinate system, camera coordinate system,
 *           and light source for all faces
 */
void l3_set_global_transform(l3_model_t *_this, l3_global_transform_cb cb);

/**
 * @brief Set face transform callback.
 *
 * @param _this the 3D model pointer
 * @param cb Set callback functions for the world coordinate system, camera coordinate system,
 *           and light source for the specified face
 */
void l3_set_face_transform(l3_model_t *_this, l3_face_transform_cb cb);

/**
 * @brief Push the model's state to the rendering pipeline.
 *
 * @param _this Pointer to the 3D model.
 */
void l3_push(l3_model_t *_this);

/**
 * @brief Render the model.
 *
 * @param _this Pointer to the 3D model.
 */
void l3_draw(l3_model_t *_this);


/**
 * @brief Free the memory allocated for the 3D model.
 *
 * @param _this Pointer to the 3D model.
 */
void l3_free_model(l3_model_t *_this);

/**
 * @brief Get the version of the Lite 3D library.
 *
 * @return Pointer to the version string.
 */
char *l3_version(void);

extern void *(*l3_malloc_imp)(size_t size);
extern void (*l3_free_imp)(void *ptr);
extern void (*l3_draw_tria_to_canvas_imp)(l3_draw_tria_img_t *image,
                                          l3_draw_rect_img_t *combined_image, float *zbuffer);
extern void (*l3_draw_rect_img_to_canvas_imp)(l3_draw_rect_img_t *image, l3_canvas_t *dc,
                                              l3_rect_t *rect);

#ifdef __cplusplus
}
#endif

#endif
