/*
 * File      : gui_watch_gradient_spot.c
 * This file is part of GUI Engine
 */
#include <guidef.h>
#include <string.h>
#include <gui_matrix.h>
#include <gui_obj.h>
#include <tp_algo.h>
#include <gui_kb.h>
#include "gui_watch_gradient_spot.h"
#include <math.h>


static void watch_gradient_spot_prepare(gui_obj_t *obj)
{
    GUI_UNUSED(obj);
    gui_dispdev_t *dc = gui_get_dc();
    gui_obj_t *root = (gui_obj_t *)obj;

    uint32_t cx = dc->fb_width / 2;
    uint32_t cy = dc->fb_height / 2;
    GUI_UNUSED(root);
    GUI_UNUSED(cx);
    GUI_UNUSED(cy);
}

static void draw_watch_gradient_spot(gui_watch_gradient_spot_t *this, NVGcontext *vg)
{
    uint32_t cx = this->c_x;
    uint32_t cy = this->c_y;
    gui_dispdev_t *dc = gui_get_dc();

    static float vary_anlge =   0;
    vary_anlge += 0.01f;
    float dx1 = 25.0f * (float)cos(1.5f * vary_anlge);
    float dy1 = 25.0f * (float)sin(1.5f * vary_anlge);
    float dx2 = 30.0f * (float)cos(-vary_anlge);
    float dy2 = 30.0f * (float)sin(-vary_anlge);
    float dx3 = 32.0f * (float)cos(2.0f * vary_anlge);
    float dy3 = 25.0f * (float)sin(2.0f * vary_anlge);
    float dx4 = 20.0f * (float)cos(vary_anlge);
    float dy4 = 20.0f * (float)sin(vary_anlge);
    float dx5 = 30.0f * (float)sin(3.0f * vary_anlge);
    float dy5 = 10.0f * (float)sin(3.0f * vary_anlge);

    float cx1 = 60 + dx1 - cx, cy1 = 60 + dy1 - cy;
    float cx2 = 394 + dx2 - cx, cy2 = 60 + dy2 - cy;
    float cx3 = 394 + dx3 - cx, cy3 = 384 + dy3 - cy;
    float cx4 = 70 + dx4 - cx, cy4 = 384 + dy4 - cy;
    float cx5 = 70 + 1.5f * dx5 - cx, cy5 = 227 + dy5 - cy;
    float cx6 = 68 - 0.5f * dx3 - cx, cy6 = 55 + dy3 - cy;
    float cx7 = 344 + dx1 - cx, cy7 = 55 + 0.8f * dy1 - cy;
    float cx8 = 385 + 0.77f * dx5 - cx, cy8 = 377 - dy5 - cy;
    float cx9 = 75 + dx4 - cx, cy9 = 380 + dy4 - cy;
    float cx10 = 80 + 1.5f * dx2 - cx, cy10 = 90 + dy2 - cy;
    float cx11 = 337 + dx3 - cx, cy11 = 130 + 1.5f * dy3 - cy;
    float cx12 = 350 + 0.77f * dx1 - cx, cy12 = 350 - dy1 - cy;
    float cx13 = 80 + dx5 - cx, cy13 = 366 + dy5 - cy;

    float arc_data1[] =
    {
        (cx1 + cx5) / 2, (cy1 + cy5) / 2,
        cx1, cy1, (cx1 + cx2) / 2, (cy1 + cy2) / 2,
        cx2, cy2, (cx2 + cx3) / 2, (cy2 + cy3) / 2,
        cx3, cy3, (cx4 + cx3) / 2, (cy3 + cy4) / 2,
        cx4, cy4, (cx4 + cx5) / 2, (cy4 + cy5) / 2,
        cx5, cy5, (cx1 + cx5) / 2, (cy1 + cy5) / 2,
    };

    float arc_data2[] =
    {
        (cx6 + cx9) / 2, (cy6 + cy9) / 2,
        cx6, cy6, (cx6 + cx7) / 2, (cy6 + cy7) / 2,
        cx7, cy7, (cx7 + cx8) / 2, (cy7 + cy8) / 2,
        cx8, cy8, (cx8 + cx9) / 2, (cy8 + cy9) / 2,
        cx9, cy9, (cx9 + cx6) / 2, (cy9 + cy6) / 2,
    };

    float arc_data3[] =
    {
        (cx10 + cx13) / 2, (cy10 + cy13) / 2,
        cx10, cy10, cx10 * 0.4f + cx11 * 0.6f, cy10 * 0.4f + cy11 * 0.6f,
        cx11, cy11, (cx11 + cx12) / 2, (cy11 + cy12) / 2,
        cx12, cy12, (cx12 + cx13) / 2, (cy12 + cy13) / 2,
        cx13, cy13, (cx13 + cx10) / 2, (cy13 + cy10) / 2,
    };

    {
        nvgBeginPath(vg);
        nvgTranslate(vg, GET_BASE(this)->dx, GET_BASE(this)->dy);
        nvgLineCap(vg, NVG_ROUND);
        nvgTranslate(vg, dc->screen_width / 2, dc->screen_height / 2);

        nvgMoveTo(vg, arc_data1[0], arc_data1[1]);
        for (size_t i = 0; i < 5; i++)
        {
            nvgQuadTo(vg, arc_data1[2 + i * 4], arc_data1[2 + i * 4 + 1], arc_data1[2 + i * 4 + 2],
                      arc_data1[2 + i * 4 + 3]);
        }
        NVGpaint bg = nvgLinearGradient(vg, -100, -100, 200, 200, nvgRGBA(0x4b, 0x5d, 0x3d, 230),
                                        nvgRGBA(0x4b, 0x5d, 0x3d, 0));
        nvgFillPaint(vg, bg);
        nvgFill(vg);
    }


    {
        nvgBeginPath(vg);
        nvgMoveTo(vg, arc_data2[0], arc_data2[1]);
        for (size_t i = 0; i < 4; i++)
        {
            nvgQuadTo(vg, arc_data2[2 + i * 4], arc_data2[2 + i * 4 + 1], arc_data2[2 + i * 4 + 2],
                      arc_data2[2 + i * 4 + 3]);
        }
        NVGpaint bg = nvgLinearGradient(vg, -100, -100, 200, 200, nvgRGBA(0x41, 0x5d, 0x1E, 200), nvgRGBA(0,
                                        255, 66, 0));
        nvgFillPaint(vg, bg);
        nvgFill(vg);
    }

    {
        nvgBeginPath(vg);
        nvgMoveTo(vg, arc_data3[0], arc_data3[1]);
        for (size_t i = 0; i < 4; i++)
        {
            nvgQuadTo(vg, arc_data3[2 + i * 4], arc_data3[2 + i * 4 + 1], arc_data3[2 + i * 4 + 2],
                      arc_data3[2 + i * 4 + 3]);
        }

        NVGpaint bg = nvgLinearGradient(vg, -100, -100, 200, 200, nvgRGBA(0x41, 0x4f, 0x1E, 100),
                                        nvgRGBA(0x41, 0x4f, 0x1E, 0));
        nvgFillPaint(vg, bg);
        nvgFill(vg);
    }

    static float d = 0;
    d += 0.0005f;

    {
        //for second point
        nvgResetTransform(vg);

        nvgBeginPath(vg);

        float width = 4;
        float height = 300;
        float x = width / 2;
        float y = 260;

        nvgTranslate(vg, GET_BASE(this)->dx, GET_BASE(this)->dy);
        nvgTranslate(vg, (dc->screen_width - width) / 2, (dc->screen_height / 2) - y);

        nvgTranslate(vg, x, y);
        nvgRotate(vg, M_PI * (d / 60.0f));
        nvgTranslate(vg, -x, -y);

        nvgRoundedRect(vg, 0, 0, width, height, 2);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
        nvgFill(vg);
    }

    {
        //for minuts point
        nvgResetTransform(vg);

        nvgBeginPath(vg);

        float width = 8;
        float height = 250;
        float x = width / 2;
        float y = 210;

        nvgTranslate(vg, GET_BASE(this)->dx, GET_BASE(this)->dy);
        nvgTranslate(vg, (dc->screen_width - width) / 2, (dc->screen_height / 2) - y);

        nvgTranslate(vg, x, y);
        nvgRotate(vg, M_PI * (d / 60.0f / 60.0f));
        nvgTranslate(vg, -x, -y);

        nvgRoundedRect(vg, 0, 0, width, height, 2);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
        nvgFill(vg);
    }


    {
        //for hour point
        nvgResetTransform(vg);

        nvgBeginPath(vg);

        float width = 16;
        float height = 200;
        float x = width / 2;
        float y = 180;

        nvgTranslate(vg, GET_BASE(this)->dx, GET_BASE(this)->dy);
        nvgTranslate(vg, (dc->screen_width - width) / 2, (dc->screen_height / 2) - y);

        nvgTranslate(vg, x, y);
        nvgRotate(vg, M_PI * (d));
        nvgTranslate(vg, -x, -y);

        nvgRoundedRect(vg, 0, 0, width, height, 2);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
        nvgFill(vg);
    }


    {
        //for center point
        nvgResetTransform(vg);
        nvgTranslate(vg, GET_BASE(this)->dx, GET_BASE(this)->dy);
        nvgTranslate(vg, dc->screen_width / 2, dc->screen_height / 2);
        nvgBeginPath(vg);
        nvgCircle(vg, 0, 0, 10);
        nvgFillColor(vg, nvgRGBA(0x41, 0x5d, 0x1E, 255));
        nvgFill(vg);
    }

}

static void watch_gradient_spot_draw_cb(gui_obj_t *obj)
{
    gui_watch_gradient_spot_t *this = (gui_watch_gradient_spot_t *)obj;
    gui_dispdev_t *dc = gui_get_dc();
    extern NVGcontext *nvgCreateAGGE(uint32_t w, uint32_t h, uint32_t stride, enum NVGtexture format,
                                     uint8_t *data);
    extern void nvgDeleteAGGE(NVGcontext * ctx);
    NVGcontext *vg = nvgCreateAGGE(dc->fb_width, dc->fb_height, dc->fb_width * (dc->bit_depth >> 3),
                                   (dc->bit_depth >> 3) == 2 ? NVG_TEXTURE_BGR565 : NVG_TEXTURE_BGRA, dc->frame_buf);
    nvgBeginFrame(vg, dc->fb_width, dc->fb_height, 1);

    nvgResetTransform(vg);

    draw_watch_gradient_spot(this, vg);

    nvgEndFrame(vg);
    nvgDeleteAGGE(vg);
}
static void watch_gradient_spot_end(gui_obj_t *obj)
{

}
static void watch_gradient_spot_destory(gui_obj_t *obj)
{

}



static void watch_gradient_spot_ctor(gui_watch_gradient_spot_t *this, gui_obj_t *parent,
                                     const char *name,
                                     int16_t x,
                                     int16_t y, int16_t w, int16_t h)
{
    //for base class
    gui_obj_t *base = (gui_obj_t *)this;
    gui_obj_ctor(base, parent, name, x, y, w, h);

    //for root class
    gui_obj_t *root = (gui_obj_t *)this;
    root->type = VG_LITE_CLOCK;
    root->obj_prepare = watch_gradient_spot_prepare;
    root->obj_draw = watch_gradient_spot_draw_cb;
    root->obj_end = watch_gradient_spot_end;
    root->obj_destory = watch_gradient_spot_destory;

    //for self

}

void gui_watch_gradient_spot_set_center(gui_watch_gradient_spot_t *this, float c_x, float c_y)
{
    this->c_x = c_x;
    this->c_y = c_y;
}



gui_watch_gradient_spot_t *gui_watch_gradient_spot_create(void *parent,  const char *name,
                                                          int16_t x, int16_t y, int16_t w, int16_t h)
{
    GUI_ASSERT(parent != NULL);
    if (name == NULL)
    {
        name = "watch_gradient_spot";
    }
    gui_watch_gradient_spot_t *this = gui_malloc(sizeof(gui_watch_gradient_spot_t));
    GUI_ASSERT(this != NULL);
    memset(this, 0x00, sizeof(gui_watch_gradient_spot_t));

    watch_gradient_spot_ctor(this, (gui_obj_t *)parent, name, x, y, w, h);

    gui_list_init(&(GET_BASE(this)->child_list));
    if ((GET_BASE(this)->parent) != NULL)
    {
        gui_list_insert_before(&((GET_BASE(this)->parent)->child_list),
                               &(GET_BASE(this)->brother_list));
    }




    GET_BASE(this)->create_done = true;
    return this;
}


