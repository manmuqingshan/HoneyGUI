#include "root_image_hongkong/ui_resource.h"
#include "gui_perspective.h"
#include "gui_canvas.h"
#include "gui_win.h"
#include "gui_obj.h"
#include "gui_app.h"
#include <gui_tabview.h>
#include "app_hongkong.h"


extern gui_tabview_t *tv;
gui_perspective_t *img_test;


static void canvas_cb_black(gui_canvas_t *canvas)
{
    nvgRect(canvas->vg, 0, 0, 368, 448);
    nvgFillColor(canvas->vg, nvgRGBA(0, 0, 128, 255));
    nvgFill(canvas->vg);
}

static void callback_prism_touch_clicked()
{
    gui_app_t *app = get_app_hongkong();
    gui_obj_t *screen = &(app->screen);
    int angle = img_test->release_x;
    if (img_test->release_x < 0)
    {
        angle = img_test->release_x + 360;
    }
    angle = (angle % 360) / (360 / 6);
    if (angle < 0 || angle > 5)
    {
        angle = 0;
    }

    gui_tree_free(screen);
    app->ui_design(get_app_hongkong());


    gui_tabview_jump_tab(tv, angle, 0);
}
void callback_prism(void *obj, gui_event_t e)
{
    gui_app_t *app = get_app_hongkong();
    gui_obj_t *screen = &(app->screen);

    gui_tree_free(screen);

    gui_win_t *win = gui_win_create(screen, "win", 0, 0, 368, 448);
    gui_canvas_t *canvas = gui_canvas_create(win, "canvas", 0, 0, 0, 368, 448);
    gui_canvas_set_canvas_cb(canvas, canvas_cb_black);

#ifdef __WIN32
    gui_perspective_imgfile_t imgfile =
    {
        .flg_fs = true,
        .img_path[0] = "Clockn.bin",
        .img_path[1] = "Weather.bin",
        .img_path[2] = "Music.bin",
        .img_path[3] = "QuickCard.bin",
        .img_path[4] = "HeartRate.bin",
        .img_path[5] = "Activity.bin"
    };
    // gui_perspective_imgfile_t imgfile =
    // {
    //     .flg_fs = false,
    //     .data_addr[0] = CLOCKN_BIN,
    //     .data_addr[1] = WEATHER_BIN,
    //     .data_addr[2] = MUSIC_BIN,
    //     .data_addr[3] = QUICKCARD_BIN,
    //     .data_addr[4] = HEARTRATE_BIN,
    //     .data_addr[5] = ACTIVITY_BIN
    // };
#else
    gui_perspective_imgfile_t imgfile =
    {
        .flg_fs = false,
        .data_addr[0] = CLOCKN_BIN,
        .data_addr[1] = WEATHER_BIN,
        .data_addr[2] = MUSIC_BIN,
        .data_addr[3] = QUICKCARD_BIN,
        .data_addr[4] = HEARTRATE_BIN,
        .data_addr[5] = ACTIVITY_BIN
    };
#endif
    img_test = gui_perspective_create(canvas, "test", &imgfile, 0, 0);

    gui_obj_add_event_cb(win, (gui_event_cb_t)callback_prism_touch_clicked, GUI_EVENT_TOUCH_CLICKED,
                         NULL);
}