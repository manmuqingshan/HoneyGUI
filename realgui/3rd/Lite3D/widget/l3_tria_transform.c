/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file def_3d_rect.c
  * @brief 3D object calculation composed of rectangular grids
  * @details 3D object calculation composed of rectangular grids
  * @author sienna_shen@realsil.com.cn
  * @date 2025/3/7
  * @version 1.0
  ***************************************************************************************
    * @attention
  * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
  ***************************************************************************************
  */

#include <stdio.h>
#include <math.h>
#include "l3_common.h"



static void l3_tria_face_transform_camera(l3_tria_face_t *face, l3_camera_t *camera)
{
    face->transform_vertex[0].position = l3_4x4_matrix_mul_4d_point(&camera->mat_cam,
                                                                    face->transform_vertex[0].position);
    face->transform_vertex[1].position = l3_4x4_matrix_mul_4d_point(&camera->mat_cam,
                                                                    face->transform_vertex[1].position);
    face->transform_vertex[2].position = l3_4x4_matrix_mul_4d_point(&camera->mat_cam,
                                                                    face->transform_vertex[2].position);
}

static void l3_tria_face_calculate_normal(l3_tria_face_t *face)
{
    l3_4d_vector_t v1, v2;

    v1 = l3_4d_point_sub(face->transform_vertex[1].position, face->transform_vertex[0].position);
    v2 = l3_4d_point_sub(face->transform_vertex[2].position, face->transform_vertex[1].position);
    face->transform_vertex[0].normal = l3_4d_vector_unit(l3_4d_vector_cross(v1, v2));
    face->transform_vertex[1].normal = face->transform_vertex[0].normal;
    face->transform_vertex[2].normal = face->transform_vertex[0].normal;


}

static void l3_tria_face_update_back_face(l3_tria_face_t *face, L3_CULLMODE cullmode)
{
    if (cullmode == L3_CULLMODE_NONE)
    {
        face->state &= ~L3_FACESTATE_BACKFACE;
        return;
    }

    bool bBackFace = true;
    l3_4d_vector_t n = face->transform_vertex[0].normal;
    l3_4d_point_t v1 = {n.ux, n.uy, n.uz, 1.0f};
    float dot;

    for (int j = 0; j < 3; j++)
    {
        l3_4d_point_t v2 = face->transform_vertex[j].position;
        dot = l3_4d_point_dot(v1, v2);

        if ((dot > 0 && cullmode != L3_CULLMODE_CCW) ||
            (dot <= 0 && cullmode != L3_CULLMODE_CW))
        {
            bBackFace = false;
            break;
        }
    }

    if (bBackFace)
    {
        face->state |= L3_FACESTATE_BACKFACE;
    }
    else
    {
        face->state &= ~L3_FACESTATE_BACKFACE;
    }

}

static void l3_tria_face_transform_perspective(l3_tria_face_t *face, l3_camera_t *camera)
{
    float z;
    z = 1 / face->transform_vertex[0].position.z;
    face->transform_vertex[0].position.x = camera->d * face->transform_vertex[0].position.x * z /
                                           camera->aspect_ratio;
    face->transform_vertex[0].position.y = camera->d * face->transform_vertex[0].position.y * z;

    z = 1 / face->transform_vertex[1].position.z;
    face->transform_vertex[1].position.x = camera->d * face->transform_vertex[1].position.x * z /
                                           camera->aspect_ratio;
    face->transform_vertex[1].position.y = camera->d * face->transform_vertex[1].position.y * z;

    z = 1 / face->transform_vertex[2].position.z;
    face->transform_vertex[2].position.x = camera->d * face->transform_vertex[2].position.x * z /
                                           camera->aspect_ratio;
    face->transform_vertex[2].position.y = camera->d * face->transform_vertex[2].position.y * z;

}

static void l3_tria_face_transform_screen(l3_tria_face_t *face, l3_camera_t *camera)
{
    float alpha = 0.5f * (camera->viewport_width - 1);
    float beta = 0.5f * (camera->viewport_height - 1);

    for (int i = 0; i < 3; i++)
    {
        // Transform to screen space
        face->transform_vertex[i].position.x = alpha + alpha * face->transform_vertex[i].position.x;
        face->transform_vertex[i].position.y = beta + beta * face->transform_vertex[i].position.y;
    }

}

void l3_tria_scene(l3_tria_face_t *face, l3_camera_t *camera)
{
    l3_tria_face_transform_camera(face, camera);
    l3_tria_face_calculate_normal(face);
    l3_tria_face_update_back_face(face, L3_CULLMODE_CCW);
    l3_tria_face_transform_perspective(face, camera);
    l3_tria_face_transform_screen(face, camera);
}




