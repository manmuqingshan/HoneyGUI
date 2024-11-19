#include "guidef.h"
#include "gui_img.h"
#include "gui_tabview.h"
#include "gui_tab.h"
#include "gui_img.h"
#include "gui_obj.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <gui_app.h>
#include "tiger_blue.txt"
// #include "tiger_grey.txt"
// #include "tiger_laven.txt"
// #include "tiger_lime.txt"
#include "tiger_turk.txt"
// #include "tiger_white.txt"
#include "tiger_yellow.txt"
#include "gui_server.h"
#include "gui_components_init.h"
// #include "gui_cube.h"
// #include "gui_win.h"
#include "gui_canvas_arc.h"
// #include "gui_canvas_round_rect.h"
#include "tiger_blue_compressed.txt"
// #include "acc_sw_rle.h"





static void app_ui_design(gui_app_t *app)
{

    // gui_canvas_round_rect_create(&(app->screen), "t", 84, 100, 298, 78, 38, gui_rgba(100, 0, 0, 255));

    // gui_canvas_arc_t *arc = gui_canvas_arc_create(&(app->screen), "t", 454 / 2, 454 / 2, 200, 0, 300, 20, gui_rgba(255, 0, 0, 255));
    // gui_canvas_arc_set_cap(arc, CANVAS_ARC_ROUND);

    // gui_canvas_arc_create(&(app->screen), "t", 454 / 2, 454 / 2, 150, 0, 360, 20, gui_rgba(0, 255, 0, 255));

    // gui_canvas_arc_create(&(app->screen), "t", 454 / 2, 454 / 2, 100, 0, 270, 20, gui_rgba(0, 255, 0, 255));

    // return;

    // gui_win_t *win0 = gui_win_create(&(app->screen), "win0", 100, 100, 200, 200);
    // gui_win_t *win1 = gui_win_create(win0, "win1", 100, 100, 200, 200);

    // gui_img_create_from_mem(win1,  "img_1_test", (void *)_actiger_blue, 50, 50, 0, 0);
    // return;

    gui_img_create_from_mem(&(app->screen),  "img_1_test", (void *)_actiger_blue_compressed, 0, 0, 0,
                            0);
    return;

    // gui_tabview_t *tv = gui_tabview_create(&(app->screen), "tabview", 0, 0, 0, 0);
    // gui_tabview_set_style(tv, TAB_CUBE);

    // gui_tabview_enable_pre_load(tv, true);

    // gui_tab_t *tab_1 = gui_tab_create(tv, "tb_1",    0, 0, 0, 0, 0, 0);
    // gui_tab_t *tab_2 = gui_tab_create(tv, "tb_2",    0, 0, 0, 0, 1, 0);


    // gui_img_t *img_blue = gui_img_create_from_mem(gui_tab_get_rte_obj(tab_1),  "img_1_test",
    //                                               (void *)_actiger_blue, 0, 0, 0,
    //                                               0);
    // gui_img_t *img_yellow = gui_img_create_from_mem(gui_tab_get_rte_obj(tab_1),  "img_1",
    //                                                 (void *)_actiger_yellow, 250, 250,
    //                                                 0, 0);




    // gui_img_t *img_2 = gui_img_create_from_mem(gui_tab_get_rte_obj(tab_2),  "img_2",
    //                                            (void *)_actiger_turk, 100, 100, 0, 0);

}


static gui_app_t rtk_gui_demo =
{
    .screen =
    {
        .name = "rtk_gui_demo",
        .x    = 0,
        .y    = 0,
    },
    .ui_design = app_ui_design,
    .active_ms = 1000 * 60 * 60,
};


static int app_init(void)
{
    gui_server_init();
    gui_app_startup(&rtk_gui_demo);
    return 0;
}

GUI_INIT_APP_EXPORT(app_init);


