/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file gui_watchface_gradient.c
  * @brief  This file is part of GUI Engine
  * @details create watchface gradien widget
  * @author triton_yu@realsil.com.cn
  * @date 2023/10/24
  * @version 1.0
  ***************************************************************************************
    * @attention
  * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
  ***************************************************************************************
  */
/*nt
 * File      : gui_watchface_gradient.c
 *
 */
#include <math.h>
#include "gui_obj.h"
#include "gui_watchface_gradient.h"


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

static void gui_watchface_gradient_canvas_design(gui_canvas_t *canvas)
{
    gui_dispdev_t *dc = gui_get_dc();
    NVGcontext *vg = canvas->vg;
    gui_canvas_t *this = canvas;
    gui_obj_t *obj = (gui_obj_t *)this;

    nvgResetTransform(vg);
    nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                 obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);
    nvgBeginPath(canvas->vg);
    nvgRoundedRect(canvas->vg, 0, 0, GET_BASE(canvas)->w, GET_BASE(canvas)->h, 37);
    nvgFillColor(canvas->vg, nvgRGB(0x7C, 0x7A, 0xEB));
    nvgFill(canvas->vg);
    nvgBeginPath(canvas->vg);
    nvgCircle(canvas->vg, GET_BASE(canvas)->w / 2, GET_BASE(canvas)->h / 2,
              WATCHFACE_GRADIENT_RING1 * WATCHFACE_GRADIENT_SCLAE / 2);
    nvgFillColor(canvas->vg, nvgRGBA(94, 92, 230, 0.5 * 0xff));
    nvgFill(canvas->vg);
    nvgBeginPath(canvas->vg);
    nvgCircle(canvas->vg, GET_BASE(canvas)->w / 2, GET_BASE(canvas)->h / 2,
              WATCHFACE_GRADIENT_RING2 * WATCHFACE_GRADIENT_SCLAE / 2);
    nvgFillColor(canvas->vg, nvgRGBA(168, 167, 241, 0.5 * 0xff));
    nvgFill(canvas->vg);
    nvgBeginPath(canvas->vg);
    nvgCircle(canvas->vg, GET_BASE(canvas)->w / 2, GET_BASE(canvas)->h / 2,
              WATCHFACE_GRADIENT_RING3 * WATCHFACE_GRADIENT_SCLAE / 2);
    nvgFillColor(canvas->vg, nvgRGBA(94, 92, 230, 0.5 * 0xff));
    nvgFill(canvas->vg);
    static float d = 0;
    d += 0.005f;

    {
        //for hour point
        nvgResetTransform(vg);

        nvgBeginPath(vg);

        float width = 5 * WATCHFACE_GRADIENT_SCLAE;
        float height = 24 * WATCHFACE_GRADIENT_SCLAE;
        float x = width / 2;
        float y = height;

        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);

        nvgRoundedRect(vg, GET_BASE(this)->x + GET_BASE(this)->w / 2 - x,
                       GET_BASE(this)->y + GET_BASE(this)->h / 2 - y, width, height, 0);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 1 * 255));
        nvgFill(vg);
    }

    {
        float r0, r1, ax, ay, bx, by, cx, cy;
        float a0, a1;
        cx = GET_BASE(canvas)->w / 2;
        cy = GET_BASE(canvas)->h / 2;
        r1 = WATCHFACE_GRADIENT_RING2 * WATCHFACE_GRADIENT_SCLAE  / 2.0F;
        r0 = WATCHFACE_GRADIENT_RING3 * WATCHFACE_GRADIENT_SCLAE  / 2.0F;
        a0 = M_PI * (d / 60.0f / 60.0f) * 2.0f - NVG_PI / 2.0f;
        a1 = a0 - NVG_PI / 1.7f;
        nvgResetTransform(vg);
        nvgBeginPath(vg);
        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);
        nvgArc(vg, GET_BASE(canvas)->w / 2, GET_BASE(canvas)->h / 2, r1, a1, a0, NVG_CW);
        nvgArc(vg, GET_BASE(canvas)->w / 2, GET_BASE(canvas)->h / 2, r0, a0, a1, NVG_CCW);
        nvgClosePath(vg);
        ax = cx + cosf(a0) * (r0 + r1) * 0.5f;
        ay = cy + sinf(a0) * (r0 + r1) * 0.5f;
        bx = cx + cosf(a1) * (r0 + r1) * 0.5f;
        by = cy + sinf(a1) * (r0 + r1) * 0.5f;
        NVGpaint paint = nvgLinearGradient(vg, ax, ay, bx, by, nvgRGBA(255, 153, 102, 1 * 255), nvgRGBA(255,
                                           153, 102, 0));
        nvgFillPaint(vg, paint);
        nvgFill(vg);
    }

    {
        //for hour point
        nvgResetTransform(vg);

        nvgBeginPath(vg);

        float width = 15 * WATCHFACE_GRADIENT_SCLAE;
        float height = 73 * WATCHFACE_GRADIENT_SCLAE ;
        float x = width / 2;
        float y = height + (20 + 3) * WATCHFACE_GRADIENT_SCLAE;

        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);

        nvgRoundedRect(vg, GET_BASE(this)->x + GET_BASE(this)->w / 2 - x,
                       GET_BASE(this)->y + GET_BASE(this)->h / 2 - y, width, height, width / 2);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
        nvgFill(vg);
    }

    {
        //for hour point
        nvgResetTransform(vg);

        nvgBeginPath(vg);

        float width = 9 * WATCHFACE_GRADIENT_SCLAE;
        float height = 67 * WATCHFACE_GRADIENT_SCLAE;
        float x = width / 2;
        float y = height + (20 + 3 + 3) * WATCHFACE_GRADIENT_SCLAE;

        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);

        nvgRoundedRect(vg, GET_BASE(this)->x + GET_BASE(this)->w / 2 - x,
                       GET_BASE(this)->y + GET_BASE(this)->h / 2 - y, width, height, width / 2);
        nvgFillColor(vg, nvgRGBA(255, 153, 102, 1 * 255));
        nvgFill(vg);
    }

    {
        //for minuts point
        nvgResetTransform(vg);

        nvgBeginPath(vg);

        float width = 5;
        float height = 28;
        float x = width / 2;
        float y = height;

        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);

        nvgRoundedRect(vg, GET_BASE(this)->x + GET_BASE(this)->w / 2 - x,
                       GET_BASE(this)->y + GET_BASE(this)->h / 2 - y, width, height, width / 2);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 1 * 255));
        nvgFill(vg);
    }

    {
        float r0, r1, ax, ay, bx, by, cx, cy;
        float a0, a1;
        cx = GET_BASE(canvas)->w / 2;
        cy = GET_BASE(canvas)->h / 2;
        r1 = WATCHFACE_GRADIENT_RING1 * WATCHFACE_GRADIENT_SCLAE  / 2;
        r0 = WATCHFACE_GRADIENT_RING2 * WATCHFACE_GRADIENT_SCLAE  / 2.0F;
        a0 = M_PI * (d / 5.0f) - NVG_PI / 2.0f;
        a1 = a0 - NVG_PI / 1.7f;
        nvgResetTransform(vg);
        nvgBeginPath(vg);
        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);
        nvgArc(vg, GET_BASE(canvas)->w / 2, GET_BASE(canvas)->h / 2, r1, a1, a0, NVG_CW);
        nvgArc(vg, GET_BASE(canvas)->w / 2, GET_BASE(canvas)->h / 2, r0, a0, a1, NVG_CCW);
        nvgClosePath(vg);
        ax = cx + cosf(a0) * (r0 + r1) * 0.5f;
        ay = cy + sinf(a0) * (r0 + r1) * 0.5f;
        bx = cx + cosf(a1) * (r0 + r1) * 0.5f;
        by = cy + sinf(a1) * (r0 + r1) * 0.5f;
#ifdef _WIN32
        NVGpaint paint = nvgLinearGradient(vg, ax, ay, bx, by, nvgRGBA(168, 167, 241, 1 * 255), nvgRGBA(94,
                                           92, 230, 0));
#else
        NVGpaint paint = nvgLinearGradient(vg, ax, ay, bx, by, nvgRGBA(94,
                                                                       92, 230, 1 * 255), nvgRGBA(94,
                                                                               92, 230, 0));
#endif
        nvgFillPaint(vg, paint);
        nvgFill(vg);
    }

    {
        //for minuts point
        nvgResetTransform(vg);

        nvgBeginPath(vg);

        float width = 15 * WATCHFACE_GRADIENT_SCLAE;
        float height = 123 * WATCHFACE_GRADIENT_SCLAE;
        float x = width / 2;
        float y = height + (20 + 5) * WATCHFACE_GRADIENT_SCLAE;

        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);

        nvgRoundedRect(vg, GET_BASE(this)->x + GET_BASE(this)->w / 2 - x,
                       GET_BASE(this)->y + GET_BASE(this)->h / 2 - y, width, height, width / 2);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
        nvgFill(vg);
    }

    {
        //for minuts point
        nvgResetTransform(vg);

        nvgBeginPath(vg);

        float width = 9 * WATCHFACE_GRADIENT_SCLAE;
        float height = 116 * WATCHFACE_GRADIENT_SCLAE;
        float x = width / 2;
        float y = height + (20 + 5 + 3) * WATCHFACE_GRADIENT_SCLAE;

        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);

        nvgRoundedRect(vg, GET_BASE(this)->x + GET_BASE(this)->w / 2 - x,
                       GET_BASE(this)->y + GET_BASE(this)->h / 2 - y, width, height, width / 2);
        nvgFillColor(vg, nvgRGBA(94, 92, 230, 1 * 255));
        nvgFill(vg);
    }

    {
        //for sceond point
        float cx, cy;
        cx = GET_BASE(canvas)->w / 2;
        cy = GET_BASE(canvas)->h / 2;
        nvgResetTransform(vg);
        nvgBeginPath(vg);
        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);
        nvgRect(vg, GET_BASE(this)->x + cx, GET_BASE(this)->y + cy, cx * 2, cy * 1.3f);

        nvgClosePath(vg);
#ifdef _WIN32
        NVGpaint paint = nvgLinearGradient(vg, cx * 2.0f, cy * 3.0f, cx * 2.0f, cy, nvgRGBA(255, 51, 119,
                                           1 * 255), nvgRGBA(255, 51, 119, 0));
#else
        NVGpaint paint = nvgLinearGradient(vg, cx * 1.5f, cy * 2.0f, cx * 1.5f, cy * 1.0f, nvgRGBA(255, 51,
                                           119,
                                           1 * 255), nvgRGBA(255, 51, 119, 0));
#endif
        nvgFillPaint(vg, paint);
        nvgFill(vg);
    }

    {
        //for sceond point
        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);
        nvgBeginPath(vg);
        nvgCircle(vg, GET_BASE(canvas)->w / 2, GET_BASE(canvas)->h / 2, 15.0f / 2.0f);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 1 * 255));
        nvgFill(vg);
    }

    {
        //for sceond point
        nvgResetTransform(vg);
        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);
        nvgBeginPath(vg);
        nvgCircle(vg, GET_BASE(canvas)->w / 2, GET_BASE(canvas)->h / 2, 7.0f / 2.0f);
        nvgFillColor(vg, nvgRGBA(0, 0, 0, 1 * 255));
        nvgFill(vg);
    }

    nvgResetTransform(vg);
    //todo for degree by howie
    nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                 obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);

    nvgBeginPath(vg);
    nvgRoundedRect(vg, -dc->screen_width, -dc->screen_height - GET_BASE(this)->y, dc->screen_width,
                   dc->screen_height * 2, 0);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 1 * 255));
    nvgFill(vg);
    nvgBeginPath(vg);
    nvgRoundedRect(vg, GET_BASE(this)->w, - GET_BASE(this)->y, dc->screen_width, dc->screen_height, 0);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 1 * 255));
    nvgFill(vg);
    nvgBeginPath(vg);
    nvgRoundedRect(vg, - GET_BASE(this)->x, - dc->screen_height, dc->screen_width * 2,
                   dc->screen_height, 0);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 1 * 255));
    nvgFill(vg);
    nvgBeginPath(vg);
    nvgRoundedRect(vg, 0, GET_BASE(this)->h, dc->screen_width * 2, dc->screen_height, 0);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 1 * 255));
    nvgFill(vg);
}

static void gui_watchface_gradient_prepare(gui_canvas_t *this)
{
    GUI_UNUSED(this);
    gui_dispdev_t *dc = gui_get_dc();
    gui_obj_t *root = (gui_obj_t *)this;

    uint32_t cx = dc->fb_width / 2;
    uint32_t cy = dc->fb_height / 2;

    GUI_UNUSED(root);
    GUI_UNUSED(cx);
    GUI_UNUSED(cy);
}

static void gui_watchface_gradient_widget_nanovg_draw_cb(gui_obj_t *obj)
{
    gui_canvas_t *this = (gui_canvas_t *)obj;
    gui_dispdev_t *dc = gui_get_dc();

    if (this->nanovg_canvas_cb != NULL)
    {
        NVGcontext *vg = nvgCreateAGGE(dc->fb_width, dc->fb_height, dc->fb_width * (dc->bit_depth >> 3),
                                       (dc->bit_depth >> 3) == 2 ? NVG_TEXTURE_BGR565 : NVG_TEXTURE_BGRA, dc->frame_buf);
        nvgBeginFrame(vg, dc->fb_width, dc->fb_height, 1);

        this->vg = vg;
        nvgResetTransform(vg);

        nvgResetTransform(vg);
        //todo for degree by howie
        nvgTransform(vg, obj->matrix->m[0][0], obj->matrix->m[1][0], obj->matrix->m[0][1],
                     obj->matrix->m[1][1], obj->matrix->m[0][2], obj->matrix->m[1][2]);

        this->nanovg_canvas_cb(this);

        nvgEndFrame(vg);
        nvgDeleteAGGE(vg);
    }
}

static void gui_watchface_gradient_widget_nanovg_end(gui_obj_t *obj)
{
    gui_canvas_t *this = (gui_canvas_t *)obj;
    GUI_UNUSED(this);
}

static void gui_watchface_gradient_widget_nanovg_destroy(gui_obj_t *obj)
{

}

static void gui_watchface_gradient_cb(gui_obj_t *obj, T_OBJ_CB_TYPE cb_type)
{
    if (obj != NULL)
    {
        switch (cb_type)
        {
        case OBJ_PREPARE:
            gui_watchface_gradient_prepare((gui_canvas_t *)obj);
            break;

        case OBJ_DRAW:
            gui_watchface_gradient_widget_nanovg_draw_cb(obj);
            break;

        case OBJ_END:
            gui_watchface_gradient_widget_nanovg_end(obj);
            break;

        case OBJ_DESTROY:
            gui_watchface_gradient_widget_nanovg_destroy(obj);
            break;

        default:
            break;
        }
    }
}

static void gui_watchface_gradient_widget_nanovg_ctor(gui_canvas_t *this,
                                                      gui_obj_t    *parent,
                                                      const char   *name,
                                                      void         *data,
                                                      int16_t       x,
                                                      int16_t       y,
                                                      int16_t       w,
                                                      int16_t       h)
{
    //for base class
    gui_obj_t *base = (gui_obj_t *)this;
    gui_obj_ctor(base, parent, name, x, y, w, h);

    //for root class
    gui_obj_t *root = (gui_obj_t *)this;
    root->type = VG_LITE_CLOCK;
    root->obj_cb = gui_watchface_gradient_cb;
    root->has_prepare_cb = true;
    root->has_draw_cb = true;
    root->has_end_cb = true;
    root->has_destroy_cb = true;
}

static void gui_watchface_gradient_ctor(gui_watchface_gradient_t *this,
                                        gui_obj_t                *parent,
                                        const char               *name,
                                        int16_t                   x,
                                        int16_t                   y,
                                        int16_t                   w,
                                        int16_t                   h)
{
    gui_watchface_gradient_widget_nanovg_ctor((gui_canvas_t *)this, parent, name, NULL, x, y, w, h);
    gui_canvas_set_canvas_cb((gui_canvas_t *)this, gui_watchface_gradient_canvas_design);
}

/*============================================================================*
 *                           Public Functions
 *============================================================================*/

gui_watchface_gradient_t *gui_watchface_gradient_create(void       *parent,
                                                        const char *name,
                                                        int16_t     x,
                                                        int16_t     y,
                                                        int16_t     w,
                                                        int16_t     h)
{
    GUI_ASSERT(parent != NULL);

    if (name == NULL)
    {
        name = "watchface_gradient";
    }

    gui_watchface_gradient_t *this = gui_malloc(sizeof(gui_watchface_gradient_t));
    GUI_ASSERT(this != NULL);
    memset(this, 0x00, sizeof(gui_watchface_gradient_t));

    gui_watchface_gradient_ctor(this, (gui_obj_t *)parent, name, x, y, w, h);

    gui_list_init(&(GET_BASE(this)->child_list));
    if ((GET_BASE(this)->parent) != NULL)
    {
        gui_list_insert_before(&((GET_BASE(this)->parent)->child_list),
                               &(GET_BASE(this)->brother_list));
    }

    GET_BASE(this)->create_done = true;
    return this;
}
