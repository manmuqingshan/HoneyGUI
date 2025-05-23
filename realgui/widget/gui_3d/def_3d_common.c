/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file def_3d_common.c
  * @brief 3d common calculation for 3d widget
  * @details 3d common calculation for 3d widget
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
#include "def_3d_common.h"
#include "gui_api.h"

/* Calculates coefficients of perspective transformation
* which maps (xi,yi) to (ui,vi), (i=1,2,3,4):
*
*      c00*xi + c01*yi + c02
* ui = ---------------------
*      c20*xi + c21*yi + c22
*
*      c10*xi + c11*yi + c12
* vi = ---------------------
*      c20*xi + c21*yi + c22
*
* Coefficients are calculated by solving linear system:
* / x0 y0  1  0  0  0 -x0*u0 -y0*u0 \ /c00\ /u0\
* | x1 y1  1  0  0  0 -x1*u1 -y1*u1 | |c01| |u1|
* | x2 y2  1  0  0  0 -x2*u2 -y2*u2 | |c02| |u2|
* | x3 y3  1  0  0  0 -x3*u3 -y3*u3 |.|c10|=|u3|,
* |  0  0  0 x0 y0  1 -x0*v0 -y0*v0 | |c11| |v0|
* |  0  0  0 x1 y1  1 -x1*v1 -y1*v1 | |c12| |v1|
* |  0  0  0 x2 y2  1 -x2*v2 -y2*v2 | |c20| |v2|
* \  0  0  0 x3 y3  1 -x3*v3 -y3*v3 / \c21/ \v3/
*
* where:
*   cij - matrix coefficients, c22 = 1
*/
static void gui_3d_swap(float *a, float *b)
{
    float c = *a;
    *a = *b;
    *b = c;
}


static bool gui_3d_gauss(float A[][9], int equ, int var,
                         float *answer)   //epu:A's row  var:A's col-1
{
    int row, col;
    for (row = 0, col = 0; col < var && row < equ; col++, row++)
    {
        int max_r = row;
        for (int i = row + 1; i < equ; i++)
        {
            if (fabs(A[i][col]) > fabs(A[max_r][col]))
            {
                max_r = i;
            }
        }
        if (max_r != row)
        {
            for (int j = 0; j < var + 1; j++)
            {
                gui_3d_swap(&A[row][j], &A[max_r][j]);
            }
        }

        if (fabs(A[row][col]) < (1e-6))
        {
            //row--;
            //continue;
            return false;
        }

        for (int i = row + 1; i < equ; i++)
        {

            if (fabs(A[i][col]) < (1e-6))
            {
                continue;
            }
            float tmp = -A[i][col] / A[row][col];
            for (int j = col; j < var + 1; j++)
            {
                A[i][j] += tmp * A[row][j];
            }
        }
    }


    for (int i = var - 1; i >= 0; i--)
    {
        float tmp = 0;
        for (int j = i + 1; j < var; j++)
        {
            tmp += A[i][j] * (*(answer + j));
        }
        answer[i] = (A[i][var] - tmp) / A[i][i];
    }
    return true;
}

bool gui_3d_generate_2d_matrix(gui_3d_point_2d_t *src, gui_3d_point_2d_t *dst, float *ret)
{
    float x0 = src[0].x, x1 = src[1].x, x2 = src[3].x, x3 = src[2].x;
    float y0 = src[0].y, y1 = src[1].y, y2 = src[3].y, y3 = src[2].y;
    float u0 = dst[0].x, u1 = dst[1].x, u2 = dst[3].x, u3 = dst[2].x;
    float v0 = dst[0].y, v1 = dst[1].y, v2 = dst[3].y, v3 = dst[2].y;
    float A[8][9] =
    {
        { x0, y0, 1, 0, 0, 0, -x0 * u0, -y0 * u0, u0 },
        { x1, y1, 1, 0, 0, 0, -x1 * u1, -y1 * u1, u1 },
        { x2, y2, 1, 0, 0, 0, -x2 * u2, -y2 * u2, u2 },
        { x3, y3, 1, 0, 0, 0, -x3 * u3, -y3 * u3, u3 },
        { 0, 0, 0, x0, y0, 1, -x0 * v0, -y0 * v0, v0 },
        { 0, 0, 0, x1, y1, 1, -x1 * v1, -y1 * v1, v1 },
        { 0, 0, 0, x2, y2, 1, -x2 * v2, -y2 * v2, v2 },
        { 0, 0, 0, x3, y3, 1, -x3 * v3, -y3 * v3, v3 },
    };
    if (gui_3d_gauss(A, 8, 8, ret) == true)
    {
        *(ret + 8) = 1;
        return true;
    }
    return false;

}

#if 1
// Set the intial cube rotation degree and step.
static const int16_t sin_table[] =
{
    0,     572,   1144,  1715,  2286,  2856,  3425,  3993,  4560,  5126,  5690,  6252,  6813,  7371,  7927,  8481,
    9032,  9580,  10126, 10668, 11207, 11743, 12275, 12803, 13328, 13848, 14364, 14876, 15383, 15886, 16383, 16876,
    17364, 17846, 18323, 18794, 19260, 19720, 20173, 20621, 21062, 21497, 21925, 22347, 22762, 23170, 23571, 23964,
    24351, 24730, 25101, 25465, 25821, 26169, 26509, 26841, 27165, 27481, 27788, 28087, 28377, 28659, 28932, 29196,
    29451, 29697, 29934, 30162, 30381, 30591, 30791, 30982, 31163, 31335, 31498, 31650, 31794, 31927, 32051, 32165,
    32269, 32364, 32448, 32523, 32587, 32642, 32687, 32722, 32747, 32762, 32767
};

static float gui_3d_sin(int angle)
{
    int16_t ret = 0;
    angle       = angle % 360;

    if (angle < 0) { angle = 360 + angle; }

    if (angle < 90)
    {
        ret = sin_table[angle];
    }
    else if (angle >= 90 && angle < 180)
    {
        angle = 180 - angle;
        ret   = sin_table[angle];
    }
    else if (angle >= 180 && angle < 270)
    {
        angle = angle - 180;
        ret   = -sin_table[angle];
    }
    else     /*angle >=270*/
    {
        angle = 360 - angle;
        ret   = -sin_table[angle];
    }

    return ret / 32767.0f;
}

static float gui_3d_cos(int angle)
{
    return gui_3d_sin(angle + 90);
}
#endif

gui_point_4d_t gui_point_4d(float x, float y, float z)
{
    gui_point_4d_t p;
    p.x = x;
    p.y = y;
    p.z = z;
    p.w = 1;
    return p;
}

float gui_point4D_dot(gui_point_4d_t p1, gui_point_4d_t p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

gui_point_4d_t gui_point_4d_unit(gui_point_4d_t p)
{
    gui_point_4d_t pt;
    if (p.x || p.y || p.z)
    {
        float sqare = sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
        pt.x = p.x / sqare;
        pt.y = p.y / sqare;
        pt.z = p.z / sqare;
        pt.w = 1;
        return pt;
    }
    return p;
}

gui_point_4d_t gui_point_4d_cross(gui_point_4d_t p1, gui_point_4d_t p2)
{
    gui_point_4d_t pt;
    pt.x = p1.y * p2.z - p2.y * p1.z;
    pt.y = p1.z * p2.x - p2.z * p1.x;
    pt.z = p1.x * p2.y - p2.x * p1.y;
    pt.w = 1;
    return pt;
}

gui_point_4d_t gui_point_4d_sub(gui_point_4d_t p1, gui_point_4d_t p2)
{
    gui_point_4d_t v;
    v.x = p1.x - p2.x;
    v.y = p1.y - p2.y;
    v.z = p1.z - p2.z;
    v.w = 1;
    return v;
}

void gui_3d_matrix_identity(gui_3d_matrix_t *m)
{
    m->_11 = 1.0f;    m->_12 = 0.0f;    m->_13 = 0.0f;    m->_14 = 0.0f;
    m->_21 = 0.0f;    m->_22 = 1.0f;    m->_23 = 0.0f;    m->_24 = 0.0f;
    m->_31 = 0.0f;    m->_32 = 0.0f;    m->_33 = 1.0f;    m->_34 = 0.0f;
    m->_41 = 0.0f;    m->_42 = 0.0f;    m->_43 = 0.0f;    m->_44 = 1.0f;
}

void gui_3d_matrix_zero(gui_3d_matrix_t *Mat)
{
    Mat->m[0][0] = 0; Mat->m[0][1] = 0; Mat->m[0][2] = 0; Mat->m[0][3] = 0;
    Mat->m[1][0] = 0; Mat->m[1][1] = 0; Mat->m[1][2] = 0; Mat->m[1][3] = 0;
    Mat->m[2][0] = 0; Mat->m[2][1] = 0; Mat->m[2][2] = 0; Mat->m[2][3] = 0;
    Mat->m[3][0] = 0; Mat->m[3][1] = 0; Mat->m[3][2] = 0; Mat->m[3][3] = 0;
}

void gui_3d_matrix_rotateX(gui_3d_matrix_t *m, float rotX)
{
    m->_11 = 1.0f;    m->_12 = 0;                               m->_13 = 0.0f;
    m->_14 = 0.0f;
    m->_21 = 0.0f;    m->_22 = gui_3d_cos(rotX);                m->_23 = gui_3d_sin(rotX);
    m->_24 = 0.0f;
    m->_31 = 0.0f;    m->_32 = -gui_3d_sin(rotX);               m->_33 = gui_3d_cos(rotX);
    m->_34 = 0.0f;
    m->_41 = 0.0f;    m->_42 = 0.0f;                            m->_43 = 0.0f;
    m->_44 = 1.0f;
}

void gui_3d_matrix_rotateY(gui_3d_matrix_t *m, float rotY)
{
    gui_3d_matrix_t *mat = m;
    float Angle = rotY;
    mat->_11 = gui_3d_cos(Angle);     mat->_12 = 0.0f;
    mat->_13 = gui_3d_sin(Angle);         mat->_14 = 0.0f;
    mat->_21 = 0.0f;                      mat->_22 = 1.0f;                          mat->_23 = 0.0f;
    mat->_24 = 0.0f;
    mat->_31 = -gui_3d_sin(Angle);        mat->_32 = 0.0f;
    mat->_33 = gui_3d_cos(Angle);         mat->_34 = 0.0f;
    mat->_41 = 0.0f;                      mat->_42 = 0.0f;                          mat->_43 = 0.0f;
    mat->_44 = 1.0f;
}

void gui_3d_matrix_rotateZ(gui_3d_matrix_t *m, float rotZ)
{
    gui_3d_matrix_t *mat = m;
    float Angle = rotZ;
    mat->_11 = gui_3d_cos(Angle);     mat->_12 = gui_3d_sin(Angle);         mat->_13 = 0.0f;
    mat->_14 = 0.0f;
    mat->_21 = -gui_3d_sin(Angle);        mat->_22 = gui_3d_cos(Angle);         mat->_23 = 0.0f;
    mat->_24 = 0.0f;
    mat->_31 = 0.0f;                      mat->_32 = 0.0f;                          mat->_33 = 1.0f;
    mat->_34 = 0.0f;
    mat->_41 = 0.0f;                      mat->_42 = 0.0f;                          mat->_43 = 0.0f;
    mat->_44 = 1.0f;
}

void gui_3d_matrix_scale(gui_3d_matrix_t *m, float scale_x, float scale_y, float scale_z)
{
    gui_3d_matrix_t *mat = m;
    mat->_11 = scale_x;   mat->_12 = 0.0f;      mat->_13 = 0.0f;      mat->_14 = 0.0f;
    mat->_21 = 0.0f;      mat->_22 = scale_y;   mat->_23 = 0.0f;      mat->_24 = 0.0f;
    mat->_31 = 0.0f;      mat->_32 = 0.0f;      mat->_33 = scale_z;   mat->_34 = 0.0f;
    mat->_41 = 0.0f;      mat->_42 = 0.0f;      mat->_43 = 0.0f;      mat->_44 = 1.0f;
}

void gui_3d_matrix_translate(gui_3d_matrix_t *m, float t_x, float t_y, float t_z)
{
    gui_3d_matrix_t *mat = m;
    mat->_11 = 1.0f;  mat->_12 = 0.0f;  mat->_13 = 0.0f;  mat->_14 = 0.0f;
    mat->_21 = 0.0f;  mat->_22 = 1.0f;  mat->_23 = 0.0f;  mat->_24 = 0.0f;
    mat->_31 = 0.0f;  mat->_32 = 0.0f;  mat->_33 = 1.0f;  mat->_34 = 0.0f;
    mat->_41 = t_x;   mat->_42 = t_y;   mat->_43 = t_z;   mat->_44 = 1.0f;
}

gui_3d_matrix_t gui_3d_matrix_multiply(gui_3d_matrix_t Mat1, gui_3d_matrix_t Mat2)
{
    gui_3d_matrix_t ptmat;
    ptmat.m[0][0] = Mat1.m[0][0] * Mat2.m[0][0]/**/ + Mat1.m[0][1] * Mat2.m[1][0]/**/ + Mat1.m[0][2] *
                    Mat2.m[2][0]/**/ + Mat1.m[0][3] * Mat2.m[3][0];
    ptmat.m[0][1] = Mat1.m[0][0] * Mat2.m[0][1]/**/ + Mat1.m[0][1] * Mat2.m[1][1]/**/ + Mat1.m[0][2] *
                    Mat2.m[2][1]/**/ + Mat1.m[0][3] * Mat2.m[3][1];
    ptmat.m[0][2] = Mat1.m[0][0] * Mat2.m[0][2]/**/ + Mat1.m[0][1] * Mat2.m[1][2]/**/ + Mat1.m[0][2] *
                    Mat2.m[2][2]/**/ + Mat1.m[0][3] * Mat2.m[3][2];
    ptmat.m[0][3] = Mat1.m[0][0] * Mat2.m[0][3]/**/ + Mat1.m[0][1] * Mat2.m[1][3]/**/ + Mat1.m[0][2] *
                    Mat2.m[2][3]/**/ + Mat1.m[0][3] * Mat2.m[3][3];

    ptmat.m[1][0] = Mat1.m[1][0] * Mat2.m[0][0]/**/ + Mat1.m[1][1] * Mat2.m[1][0]/**/ + Mat1.m[1][2] *
                    Mat2.m[2][0]/**/ + Mat1.m[1][3] * Mat2.m[3][0];
    ptmat.m[1][1] = Mat1.m[1][0] * Mat2.m[0][1]/**/ + Mat1.m[1][1] * Mat2.m[1][1]/**/ + Mat1.m[1][2] *
                    Mat2.m[2][1]/**/ + Mat1.m[1][3] * Mat2.m[3][1];
    ptmat.m[1][2] = Mat1.m[1][0] * Mat2.m[0][2]/**/ + Mat1.m[1][1] * Mat2.m[1][2]/**/ + Mat1.m[1][2] *
                    Mat2.m[2][2]/**/ + Mat1.m[1][3] * Mat2.m[3][2];
    ptmat.m[1][3] = Mat1.m[1][0] * Mat2.m[0][3]/**/ + Mat1.m[1][1] * Mat2.m[1][3]/**/ + Mat1.m[1][2] *
                    Mat2.m[2][3]/**/ + Mat1.m[1][3] * Mat2.m[3][3];

    ptmat.m[2][0] = Mat1.m[2][0] * Mat2.m[0][0]/**/ + Mat1.m[2][1] * Mat2.m[1][0]/**/ + Mat1.m[2][2] *
                    Mat2.m[2][0]/**/ + Mat1.m[2][3] * Mat2.m[3][0];
    ptmat.m[2][1] = Mat1.m[2][0] * Mat2.m[0][1]/**/ + Mat1.m[2][1] * Mat2.m[1][1]/**/ + Mat1.m[2][2] *
                    Mat2.m[2][1]/**/ + Mat1.m[2][3] * Mat2.m[3][1];
    ptmat.m[2][2] = Mat1.m[2][0] * Mat2.m[0][2]/**/ + Mat1.m[2][1] * Mat2.m[1][2]/**/ + Mat1.m[2][2] *
                    Mat2.m[2][2]/**/ + Mat1.m[2][3] * Mat2.m[3][2];
    ptmat.m[2][3] = Mat1.m[2][0] * Mat2.m[0][3]/**/ + Mat1.m[2][1] * Mat2.m[1][3]/**/ + Mat1.m[2][2] *
                    Mat2.m[2][3]/**/ + Mat1.m[2][3] * Mat2.m[3][3];

    ptmat.m[3][0] = Mat1.m[3][0] * Mat2.m[0][0]/**/ + Mat1.m[3][1] * Mat2.m[1][0]/**/ + Mat1.m[3][2] *
                    Mat2.m[2][0]/**/ + Mat1.m[3][3] * Mat2.m[3][0];
    ptmat.m[3][1] = Mat1.m[3][0] * Mat2.m[0][1]/**/ + Mat1.m[3][1] * Mat2.m[1][1]/**/ + Mat1.m[3][2] *
                    Mat2.m[2][1]/**/ + Mat1.m[3][3] * Mat2.m[3][1];
    ptmat.m[3][2] = Mat1.m[3][0] * Mat2.m[0][2]/**/ + Mat1.m[3][1] * Mat2.m[1][2]/**/ + Mat1.m[3][2] *
                    Mat2.m[2][2]/**/ + Mat1.m[3][3] * Mat2.m[3][2];
    ptmat.m[3][3] = Mat1.m[3][0] * Mat2.m[0][3]/**/ + Mat1.m[3][1] * Mat2.m[1][3]/**/ + Mat1.m[3][2] *
                    Mat2.m[2][3]/**/ + Mat1.m[3][3] * Mat2.m[3][3];
    return ptmat;
}



gui_point_4d_t gui_3d_point4D_mul_matrix(gui_point_4d_t p, gui_3d_matrix_t mat)
{
    gui_point_4d_t point;
    point.x = p.x * mat._11 + p.y * mat._21 + p.z * mat._31 + 1 * mat._41;
    point.y = p.x * mat._12 + p.y * mat._22 + p.z * mat._32 + 1 * mat._42;
    point.z = p.x * mat._13 + p.y * mat._23 + p.z * mat._33 + 1 * mat._43;
    point.w = p.x * mat._14 + p.y * mat._24 + p.z * mat._34 + 1 * mat._44;
    return point;
}


static void gui_3d_generate_rotate_around_line(gui_3d_matrix_t *mrot, float px, float py, float pz,
                                               float ux, float uy, float uz, float angle_degrees)
{
    // Convert degrees to radians
    float angle = angle_degrees * (3.141562f / 180.0f);
    // Normalize the direction vector (u)
    float mag = sqrt(ux * ux + uy * uy + uz * uz);
    float a = ux / mag, b = uy / mag, c = uz / mag;

    // Step 1: Translate to the origin
    gui_3d_matrix_t T1;
    gui_3d_matrix_identity(&T1);
    T1.m[3][0] = -px;
    T1.m[3][1] = -py;
    T1.m[3][2] = -pz;

    // Step 2: Rotate to align u with the Z-axis
    float theta = atan2(b, c);
    gui_3d_matrix_t Rx;
    gui_3d_matrix_identity(&Rx);
    Rx.m[1][1] = cos(theta);
    Rx.m[1][2] = -sin(theta);
    Rx.m[2][1] = sin(theta);
    Rx.m[2][2] = cos(theta);

    float phi = atan2(a, sqrt(b * b + c * c));
    gui_3d_matrix_t Ry;
    gui_3d_matrix_identity(&Ry);
    Ry.m[0][0] = cos(phi);
    Ry.m[0][2] = sin(phi);
    Ry.m[2][0] = -sin(phi);
    Ry.m[2][2] = cos(phi);

    // Step 3: Rotate around the Z-axis
    gui_3d_matrix_t Rz;
    gui_3d_matrix_identity(&Rz);
    Rz.m[0][0] = cos(angle);
    Rz.m[0][1] = -sin(angle);
    Rz.m[1][0] = sin(angle);
    Rz.m[1][1] = cos(angle);

    // Inverse rotations
    gui_3d_matrix_t Ryi;
    gui_3d_matrix_identity(&Ryi);
    Ryi.m[0][0] = cos(-phi);
    Ryi.m[0][2] = sin(-phi);
    Ryi.m[2][0] = -sin(-phi);
    Ryi.m[2][2] = cos(-phi);

    gui_3d_matrix_t Rxi;
    gui_3d_matrix_identity(&Rxi);
    Rxi.m[1][1] = cos(-theta);
    Rxi.m[1][2] = -sin(-theta);
    Rxi.m[2][1] = sin(-theta);
    Rxi.m[2][2] = cos(-theta);

    // Step 4: Translate back to the original position
    gui_3d_matrix_t T2;
    gui_3d_matrix_identity(&T2);
    T2.m[3][0] = px;
    T2.m[3][1] = py;
    T2.m[3][2] = pz;

    // Combine all transformations
    gui_3d_matrix_t temp1 = gui_3d_matrix_multiply(Ryi, Rxi);
    gui_3d_matrix_t temp2 = gui_3d_matrix_multiply(temp1, Rz);
    gui_3d_matrix_t temp3 = gui_3d_matrix_multiply(temp2, Ry);
    gui_3d_matrix_t temp4 = gui_3d_matrix_multiply(temp3, Rx);
    gui_3d_matrix_t temp5 = gui_3d_matrix_multiply(temp4, T1);
    *mrot = gui_3d_matrix_multiply(T2, temp5);
}

gui_point_4d_t gui_3d_point(float x, float y, float z)
{
    gui_point_4d_t point;
    point.x = x;
    point.y = y;
    point.z = z;
    point.w = 1.0f;
    return point;
}

gui_vector_4d_t gui_3d_vector(float ux, float uy, float uz)
{
    gui_vector_4d_t vector;
    vector.ux = ux;
    vector.uy = uy;
    vector.uz = uz;
    vector.uw = 1.0f;
    return vector;
}

void gui_3d_calculator_matrix(gui_3d_matrix_t *matrix, \
                              float x, float y, float z, \
                              gui_point_4d_t point, gui_vector_4d_t vector, float degrees, \
                              float scale)
{
    gui_3d_matrix_t mrot, mscale, mtrans;
    float px = point.x;
    float py = point.y;
    float pz = point.z;
    float ux = vector.ux;
    float uy = vector.uy;
    float uz = vector.uz;
    gui_3d_matrix_identity(matrix);

    gui_3d_generate_rotate_around_line(&mrot, px, py, pz, ux, uy, uz, degrees);

    gui_3d_matrix_scale(&mscale, scale, scale, scale);
    gui_3d_matrix_translate(&mtrans, x, y, z);

    *matrix = gui_3d_matrix_multiply(*matrix, mscale);

    *matrix = gui_3d_matrix_multiply(*matrix, mrot);

    *matrix = gui_3d_matrix_multiply(*matrix, mtrans);
}

void gui_3d_world_inititalize(gui_3d_matrix_t *world, float x, float y, float z, float rotX,
                              float rotY, float rotZ, float scale)
{
    gui_3d_matrix_t mrotx, mroty, mrotz, mscale, mtrans;
    gui_3d_matrix_identity(world);
    gui_3d_matrix_rotateX(&mrotx, rotX);
    gui_3d_matrix_rotateY(&mroty, rotY);
    gui_3d_matrix_rotateZ(&mrotz, rotZ);
    gui_3d_matrix_scale(&mscale, scale, scale, scale);
    gui_3d_matrix_translate(&mtrans, x, y, z);

    *world = gui_3d_matrix_multiply(*world, mscale);
    *world = gui_3d_matrix_multiply(*world, mrotx);
    *world = gui_3d_matrix_multiply(*world, mroty);

    *world = gui_3d_matrix_multiply(*world, mrotz);
    *world = gui_3d_matrix_multiply(*world, mtrans);


}

bool gui_3d_camera_UVN_initialize(gui_3d_camera_t *camera, gui_point_4d_t cameraPosition,
                                  gui_point_4d_t cameraTarget, float near, float far, float fov, float viewPortWidth,
                                  float viewPortHeight)
{
    camera->position = cameraPosition;
    camera->targetDirection = cameraTarget;
    camera->near_z = near;
    camera->far_z = far;
    camera->viewport_width = viewPortWidth;
    camera->viewport_height = viewPortHeight;

    camera->viewport_center_x = (viewPortWidth - 1) / 2;
    camera->viewport_center_y = (viewPortHeight - 1) / 2;

    camera->aspect_ratio = viewPortWidth / (float)viewPortHeight;

    gui_3d_matrix_identity(&camera->mat_cam);
    gui_3d_matrix_identity(&camera->mat_per);
    gui_3d_matrix_identity(&camera->mat_scr);

    camera->fov = fov;
    camera->viewplane_width = 2.0f;
    camera->viewplane_height = 2.0f / camera->aspect_ratio;

    if (fov == 90)
    {
        camera->d = 1;
    }
    else
    {
        camera->d = (0.5f) * (camera->viewplane_width) * tanf(fov);
    }
    //camera->zbuffer=(float *)malloc(sizeof(float)*camera->viewport_height*camera->viewport_width);
    //return camera->zbuffer!=NULL;
    return true;
}


void gui_3d_camera_build_UVN_matrix(gui_3d_camera_t *camera)
{
    gui_3d_matrix_t mt_inv;
    gui_3d_matrix_t mt_uvn;
    gui_point_4d_t u, v, n;

    gui_3d_matrix_identity(&mt_inv);
    mt_inv._41 = -camera->position.x;
    mt_inv._42 = -camera->position.y;
    mt_inv._43 = -camera->position.z;

    n.x = camera->targetDirection.x - camera->position.x;
    n.y = camera->targetDirection.y - camera->position.y;
    n.z = camera->targetDirection.z - camera->position.z;
    n.w = 1;

    n = gui_point_4d_unit(n);
    v = gui_point_4d(0, 1, 0);
    u = gui_point_4d_cross(v, n);
    v = gui_point_4d_cross(n, u);
    gui_3d_matrix_zero(&mt_uvn);
    mt_uvn._11 = u.x;
    mt_uvn._12 = v.x;
    mt_uvn._13 = n.x;

    mt_uvn._21 = u.y;
    mt_uvn._22 = v.y;
    mt_uvn._23 = n.y;

    mt_uvn._31 = u.z;
    mt_uvn._32 = v.z;
    mt_uvn._33 = n.z;

    mt_uvn._44 = 1;
    camera->mat_cam = gui_3d_matrix_multiply(mt_inv, mt_uvn);
}

gui_3d_description_t *gui_get_3d_desc(void *desc_addr)
{
    unsigned char *ptr = (unsigned char *)desc_addr;
    gui_3d_description_t *desc = (gui_3d_description_t *)gui_malloc(sizeof(gui_3d_description_t));

    // face type
    desc->face_type = (GUI_3D_FACE_TYPE) * ((int *)ptr);
    ptr += sizeof(int);

    // attrib
    desc->attrib.num_vertices = *((unsigned int *)ptr);
    ptr += sizeof(unsigned int);
    desc->attrib.num_normals = *((unsigned int *)ptr);
    ptr += sizeof(unsigned int);
    desc->attrib.num_texcoords = *((unsigned int *)ptr);
    ptr += sizeof(unsigned int);
    desc->attrib.num_faces = *((unsigned int *)ptr);
    ptr += sizeof(unsigned int);
    desc->attrib.num_face_num_verts = *((unsigned int *)ptr);
    ptr += sizeof(unsigned int);
    desc->attrib.pad0 = *((int *)ptr);
    ptr += sizeof(int);

    desc->attrib.vertices = (gui_obj_vertex_coordinate_t *)ptr;
    ptr += desc->attrib.num_vertices * sizeof(gui_obj_vertex_coordinate_t);
    desc->attrib.normals = (gui_obj_vertex_coordinate_t *)ptr;
    ptr += desc->attrib.num_normals * sizeof(gui_obj_vertex_coordinate_t);
    desc->attrib.texcoords = (gui_obj_texcoord_coordinate_t *)ptr;
    ptr += desc->attrib.num_texcoords * sizeof(gui_obj_texcoord_coordinate_t);
    desc->attrib.faces = (gui_obj_vertex_index_t *)ptr;
    ptr += desc->attrib.num_faces * sizeof(gui_obj_vertex_index_t);
    desc->attrib.face_num_verts = (int *)ptr;
    ptr += desc->attrib.num_face_num_verts * sizeof(int);
    desc->attrib.material_ids = (int *)ptr;
    ptr += desc->attrib.num_face_num_verts * sizeof(int);

    // shape
    desc->num_shapes = *((unsigned int *)ptr);
    ptr += sizeof(unsigned int);
    desc->shapes = (gui_obj_shape_t *)ptr;
    ptr += desc->num_shapes * sizeof(gui_obj_shape_t);

    // material
    desc->num_materials = *((unsigned int *)ptr);
    ptr += sizeof(unsigned int);
    if (desc->num_materials > 0)
    {
        desc->materials = (gui_obj_material_t *)ptr;
        ptr += desc->num_materials * sizeof(gui_obj_material_t);

        // textures size
        desc->texture_sizes = (unsigned int *)ptr;
        ptr += desc->num_materials * sizeof(unsigned int);
        desc->textures = (unsigned char **)gui_malloc(desc->num_materials * sizeof(unsigned char *));
        // texture content
        for (uint32_t i = 0; i < desc->num_materials; i++)
        {
            if (desc->texture_sizes[i] > 0)
            {
                desc->textures[i] = (unsigned char *)ptr;
                ptr += desc->texture_sizes[i];
            }
        }

    }

    return desc;

}



