/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file
  * @brief
  * @details
  * @author
  * @date
  * @version
  ***************************************************************************************
    * @attention
  * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
  ***************************************************************************************
  */

/*============================================================================*
 *                        Header Files
 *============================================================================*/
#include <guidef.h>
#include <string.h>
#include <gui_obj.h>
#include "gui_px.h"
#include <tp_algo.h>



/** @defgroup WIDGET WIDGET
  * @{
  */
/*============================================================================*
 *                           Types
 *============================================================================*/
/** @defgroup WIDGET_Exported_Types WIDGET Exported Types
  * @{
  */


/** End of WIDGET_Exported_Types
  * @}
  */

/*============================================================================*
 *                           Constants
 *============================================================================*/
/** @defgroup WIDGET_Exported_Constants WIDGET Exported Constants
  * @{
  */


/** End of WIDGET_Exported_Constants
  * @}
  */

/*============================================================================*
 *                            Macros
 *============================================================================*/
/** @defgroup WIDGET_Exported_Macros WIDGET Exported Macros
  * @{
  */



/** End of WIDGET_Exported_Macros
  * @}
  */
/*============================================================================*
 *                            Variables
 *============================================================================*/
/** @defgroup WIDGET_Exported_Variables WIDGET Exported Variables
  * @{
  */


/** End of WIDGET_Exported_Variables
  * @}
  */

/*============================================================================*
 *                           Private Functions
 *============================================================================*/
/** @defgroup WIDGET_Exported_Functions WIDGET Exported Functions
  * @{
  */


static void prepare(gui_px_t *this)
{
    touch_info_t *tp = tp_get_info();
    gui_obj_t *root = (gui_obj_t *)this;
    gui_dispdev_t *dc = gui_get_dc();

    GUI_UNUSED(this);
    GUI_UNUSED(root);
    GUI_UNUSED(tp);
    GUI_UNUSED(dc);
    gui_fb_change();
}

static px_void PX_ApplicationUpdate(gui_px_t *this, px_dword elapsed)
{
    PX_ObjectUpdate(this->px_root, elapsed);
}

static px_void PX_ApplicationRender(gui_px_t *this, px_dword elapsed)
{
    px_surface *pRenderSurface = &this->RenderSurface;

    PX_SurfaceClear(pRenderSurface, 0, 0, pRenderSurface->width - 1, pRenderSurface->height - 1,
                    PX_COLOR_BACKGROUNDCOLOR);


    PX_ObjectRender(pRenderSurface, this->px_root, elapsed);
}

static void draw(gui_px_t *this)
{
    touch_info_t *tp = tp_get_info();
    gui_obj_t *root = (gui_obj_t *)this;
    gui_dispdev_t *dc = gui_get_dc();

    GUI_UNUSED(this);
    GUI_UNUSED(root);
    GUI_UNUSED(tp);
    GUI_UNUSED(dc);

    //time

    this->elapsed = PX_TimeGetTime() - this->timelasttime;
    this->timelasttime = PX_TimeGetTime();


    PX_ApplicationUpdate(this, this->elapsed);
    PX_ApplicationRender(this, this->elapsed);
    px_surface *pRenderSurface = &this->RenderSurface;

    memcpy(dc->frame_buf, pRenderSurface->surfaceBuffer,
           dc->fb_width * dc->fb_height * dc->bit_depth / 8);
}
static void end(gui_px_t *this)
{
    touch_info_t *tp = tp_get_info();
    gui_obj_t *root = (gui_obj_t *)this;
    gui_dispdev_t *dc = gui_get_dc();

    GUI_UNUSED(this);
    GUI_UNUSED(root);
    GUI_UNUSED(tp);
    GUI_UNUSED(dc);
}
static void destory(gui_px_t *this)
{
    touch_info_t *tp = tp_get_info();
    gui_obj_t *root = (gui_obj_t *)this;
    gui_dispdev_t *dc = gui_get_dc();

    GUI_UNUSED(this);
    GUI_UNUSED(root);
    GUI_UNUSED(tp);
    GUI_UNUSED(dc);
}

static px_bool GUI_PX_ApplicationInitialize(gui_px_t *this, px_int screen_width,
                                            px_int screen_height, void (*main_cb)(gui_px_t *this))
{

    this->mem_static = MP_Create(gui_malloc(1024 * 1024 * 2), 1024 * 1024 * 2);
    this->mp_static = &this->mem_static;
    this->mem_dynamic = MP_Create(gui_malloc(1024 * 1024 * 5), 1024 * 1024 * 5);
    this->mp_dynamic = &this->mem_dynamic;

    if (!PX_SurfaceCreate(this->mp_static, screen_width, screen_height, &this->RenderSurface))
    {
        return PX_FALSE;
    }

    PX_SurfaceClear(&this->RenderSurface, 0, 0, this->RenderSurface.width - 1,
                    this->RenderSurface.height - 1, PX_COLOR_BACKGROUNDCOLOR);

    this->px_root = PX_ObjectCreateRoot(this->mp_dynamic);

    if (main_cb != NULL)
    {
        main_cb(this);
    }
    else
    {
        GUI_ASSERT(NULL != NULL);
    }





}

static void px_ctor(gui_px_t *this, gui_obj_t *parent, const char *name,
                    void (*main_cb)(gui_px_t *this),
                    int16_t x,
                    int16_t y, int16_t w, int16_t h)
{
    //for root class
    gui_obj_t *root = (gui_obj_t *)this;
    gui_obj_ctor(root, parent, name, x, y, w, h);

    root->obj_prepare = (void (*)(struct _gui_obj_t *))prepare;
    root->obj_draw = (void (*)(struct _gui_obj_t *))draw;
    root->obj_end = (void (*)(struct _gui_obj_t *))end;
    root->obj_destory = (void (*)(struct _gui_obj_t *))destory;

    //for self

    gui_dispdev_t *dc = gui_get_dc();


    GUI_PX_ApplicationInitialize(this, dc->fb_width, dc->fb_height, main_cb);


}

/*============================================================================*
 *                           Public Functions
 *============================================================================*/

/**
 * @brief
 *
 * @param parent
 * @param name
 * @param data
 * @param x
 * @param y
 * @param w
 * @param h
 * @return gui_px_t*
 */
gui_px_t *gui_px_create(void *parent,  const char *name, void (*main_cb)(gui_px_t *this),
                        int16_t x,
                        int16_t y, int16_t w, int16_t h)
{
    GUI_ASSERT(parent != NULL);
    if (name == NULL)
    {
        name = "PAINTER_ENGINE";
    }
    gui_px_t *this = gui_malloc(sizeof(gui_px_t));
    GUI_ASSERT(this != NULL);
    memset(this, 0x00, sizeof(gui_px_t));

    px_ctor(this, (gui_obj_t *)parent, name, main_cb, x, y, w, h);

    gui_list_init(&(GET_BASE(this)->child_list));
    if ((GET_BASE(this)->parent) != NULL)
    {
        gui_list_insert_before(&((GET_BASE(this)->parent)->child_list),
                               &(GET_BASE(this)->brother_list));
    }


    GET_BASE(this)->create_done = true;
    return this;
}


/** End of WIDGET_Exported_Functions
  * @}
  */

/** End of WIDGET
  * @}
  */





