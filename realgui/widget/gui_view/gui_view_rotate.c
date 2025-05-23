/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file gui_view_rotate.c
  * @brief view widget
  * @details view widget
  * @author shel_deng@realsil.com.cn
  * @date 2025/2/18
  * @version 1.0
  ***************************************************************************************
    * @attention
  * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
  ***************************************************************************************
  */

/*============================================================================*
 *                        Header Files
 *============================================================================*/
#include <string.h>
#include "guidef.h"
#include "gui_server.h"
#include "gui_obj.h"
#include "gui_view.h"

/*============================================================================*
 *                           Types
 *============================================================================*/


/*============================================================================*
 *                           Constants
 *============================================================================*/


/*============================================================================*
 *                            Macros
 *============================================================================*/


/*============================================================================*
 *                            Variables
 *============================================================================*/


/*============================================================================*
 *                           Private Functions
 *============================================================================*/

void gui_view_rotate(gui_view_t *this)
{
    gui_obj_t *obj = GUI_BASE(this);
    gui_dispdev_t *dc = gui_get_dc();
    gui_matrix_t rotate_3D;
    gui_matrix_t temp;
    int16_t idx = this->cur_id.x;
    int16_t idy = this->cur_id.y;
    float w = this->base.w;
    float h = this->base.h;
    float rotate_degree_x = 0;
    float rotate_degree_y = 0;

    gui_vertex_t v0 = {-w, -h, 0};
    gui_vertex_t v1 = {w,  -h, 0};
    gui_vertex_t v2 = {w,  h,  0};
    gui_vertex_t v3 = {-w, h,  0};

    gui_vertex_t tv0, tv1, tv2, tv3;
    gui_vertex_t rv0, rv1, rv2, rv3;

    int16_t release_x = this->release_x;
    int16_t release_y = this->release_y;
    if (release_x > this->base.w / 2)
    {
        idx++;
        release_x = release_x - this->base.w;
    }
    if (release_x < -this->base.w / 2)
    {
        idx--;
        release_x = release_x + this->base.w;
    }

    if (release_y > this->base.h / 2)
    {
        idy++;
        release_y = release_y - this->base.h;
    }
    if (release_y < -this->base.h / 2)
    {
        idy--;
        release_y = release_y + this->base.h;
    }

    rotate_degree_x = 90 * release_y / (this->base.h / 2);
    rotate_degree_y = 90 * release_x / (this->base.w / 2);

    matrix_compute_rotate(-rotate_degree_x, rotate_degree_y, 0, &rotate_3D);

    matrix_transfrom_rotate(&rotate_3D, &v0, &tv0, 0, 0, 0);
    matrix_transfrom_rotate(&rotate_3D, &v1, &tv1, 0, 0, 0);
    matrix_transfrom_rotate(&rotate_3D, &v2, &tv2, 0, 0, 0);
    matrix_transfrom_rotate(&rotate_3D, &v3, &tv3, 0, 0, 0);

    matrix_compute_rotate(0, 0, 0, &rotate_3D);
    float xoff = (float)dc->screen_width / 2;
    float yoff = (float)dc->screen_height / 2 ;
    float zoff = -(xoff + yoff);

    matrix_transfrom_rotate(&rotate_3D, &tv0, &rv0, xoff, yoff, zoff);
    matrix_transfrom_rotate(&rotate_3D, &tv1, &rv1, xoff, yoff, zoff);
    matrix_transfrom_rotate(&rotate_3D, &tv2, &rv2, xoff, yoff, zoff);
    matrix_transfrom_rotate(&rotate_3D, &tv3, &rv3, xoff, yoff, zoff);

    gui_vertex_t p = {(float)(dc->screen_width) / 2, (float)(dc->screen_height) / 2, -zoff};

    matrix_transfrom_blit(this->base.w, this->base.h, &p, &rv0, &rv1, &rv2, &rv3,
                          &temp);

    matrix_translate((idx) * 2 * (int)this->base.w, \
                     (idy) * 2 * (int)this->base.h, \
                     obj->matrix); //todo multi 2 for bug fix

    matrix_multiply(obj->matrix, &temp);
}

