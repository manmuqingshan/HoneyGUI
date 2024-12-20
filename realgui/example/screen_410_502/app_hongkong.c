#include <gui_tabview.h>
#include "gui_card.h"
#include <gui_obj.h>
#include <gui_win.h>
#include <gui_text.h>
#include <gui_curtain.h>
#include "root_image_hongkong/ui_resource.h"
#include <gui_app.h>
#include "gui_tab.h"
#include "app_hongkong.h"
#include "gui_win.h"
#include "gui_server.h"
#include "gui_components_init.h"
#include <stdio.h>
#include "guidef.h"
#include "wheel_algo.h"
#include "kb_algo.h"
#include "gui_multi_level.h"

static void app_hongkong_ui_design(gui_app_t *app);

static gui_tabview_t *tv;
static gui_win_t *win_hk; //, *win_control;
gui_multi_level_t *m10;
bool control_flag = 0;

static gui_app_t app_hongkong =
{
    .screen =
    {
        .name = "app_hongkong",
        .x    = 0,
        .y    = 0,
        .parent = NULL,
    },
    .ui_design = app_hongkong_ui_design,
    .active_ms = 1000000,
};

void *get_app_hongkong(void)
{
    return &app_hongkong;
}

static void kb_button_cb()
{
#ifdef _WIN32
    touch_info_t *wheel = wheel_get_info();
    // kb_info_t *kb = kb_get_info();
    static bool hold = 0;
    // static bool kb_hold = 0;
    if (hold)
    {
        if (wheel->button_up)
        {
            gui_obj_event_set(GUI_BASE(win_hk), GUI_EVENT_8);
        }
    }
    if (wheel->button_hold)
    {
        hold = 1;
    }
    else
    {
        hold = 0;
    }
    // if (kb_hold)
    // {
    //     if (kb->released)
    //     {
    //         gui_log("kb_hold %d\n", kb->released);
    //         gui_obj_event_set(GUI_BASE(win_control), GUI_EVENT_8);
    //     }
    // }
    // if (kb->pressed)
    // {
    //     kb_hold = 1;
    // }
    // else
    // {
    //     kb_hold = 0;
    // }
#else
#include "kb_algo.h"
    gui_kb_port_data_t *kb = port_kb_get_data();
    static uint8_t hold = 0;
    if (hold)
    {
        if (kb->event == GUI_KB_EVENT_UP)
        {
            gui_obj_event_set(GUI_BASE(win_hk), GUI_EVENT_8);
        }
    }
    if (kb->event == GUI_KB_EVENT_DOWN)
    {
        hold = 1;
    }
    else
    {
        hold = 0;
    }
#endif
}

static void switch_app_menu()
{
    gui_log("enter menu\n");
    extern void *get_app_menu();
    gui_switch_app(gui_current_app(), get_app_menu());
}
// extern void page_tb_control(gui_obj_t *parent);
// static void switch_control_board(void *obj, gui_event_t e, void *param)
// {
//     gui_log("switch_control_board\n");
//     page_tb_control((gui_obj_t *)param);

//     // gui_multi_level_t *ml0 = param;
//     // if (ml_index == 1)
//     // {
//     //     GUI_API(gui_multi_level_t).jump(ml0, 1, 0);
//     // }
//     // else
//     // {
//     //     GUI_API(gui_multi_level_t).jump(ml0, 0, 1);
//     // }
// }
static void app_hongkong_ui_design(gui_app_t *app)
{
    gui_log("app_hongkong_ui_design\n");

    tv = gui_tabview_create(&(app->screen), "hongkong_tabview", 0, 0, 0, 0);
    win_hk = gui_win_create(&(app->screen), "window_hongkong", 0, 0, 0, 0);
    gui_win_set_animate(win_hk, 1000, -1, kb_button_cb, NULL);
    gui_obj_add_event_cb(win_hk, (gui_event_cb_t)switch_app_menu, GUI_EVENT_8, &(app->screen));
    gui_tabview_set_style(tv, TAB_CUBE);
    gui_tabview_enable_pre_load(tv, true);
    extern void page_tb_control_enter(void *parent);
    page_tb_control_enter(&(app->screen));
    // gui_obj_tree_print(&(app->screen));
    // win_control = gui_win_create(&(app->screen), NULL, 0, 0, 0, 0);
    // gui_obj_add_event_cb(win_control, (gui_event_cb_t)switch_control_board, GUI_EVENT_8,  &(app->screen));

    gui_tab_t *tb_clock = gui_tab_create(tv, "tb_clock",           0, 0, 0, 0, 0, 0);
    gui_tab_t *tb_activity = gui_tab_create(tv, "tb_activity",     0, 0, 0, 0, 1, 0);
    gui_tab_t *tb_heart = gui_tab_create(tv, "tb_heart",           0, 0, 0, 0, 2, 0);
    gui_tab_t *tb_cube = gui_tab_create(tv, "tb_cube",           0, 0, 0, 0, 3, 0);
    gui_tab_t *tb_weather = gui_tab_create(tv, "tb_weather",       0, 0, 0, 0, 5, 0);
    gui_tab_t *tb_music = gui_tab_create(tv, "tb_music",           0, 0, 0, 0, 4, 0);
    gui_tab_t *tb_ani = gui_tab_create(tv, "tb_ani",          0, 0, 0, 0, 6, 0);
    // page_tb_clock(win);
    page_tb_clock(gui_tab_get_rte_obj(tb_clock));
    // page_tb_control(gui_tab_get_rte_obj(tb_activity));
    page_tb_activity(gui_tab_get_rte_obj(tb_activity));
    page_tb_heart(gui_tab_get_rte_obj(tb_heart));
    page_tb_cube(gui_tab_get_rte_obj(tb_cube));
    page_tb_weather(gui_tab_get_rte_obj(tb_weather));
    page_tb_music(gui_tab_get_rte_obj(tb_music));
}


uint8_t resource_root[1024 * 1024 * 20];
static int app_init(void)
{
#if defined _WIN32
    extern int open(const char *file, int flags, ...);
    extern int read(int fd, void *buf, size_t len);
    extern int close(int fd);
    defaultPath = "realgui\\example\\screen_454_454\\root_image\\root\\";
    int fd;
    fd = open("./realgui/example/screen_410_502/root_image_hongkong/root(0x4400000).bin", 0);
    if (fd > 0)
    {
        printf("open root(0x4400000).bin Successful!\n");
        read(fd, resource_root, 1024 * 1024 * 20);
    }
    else
    {
        printf("open root(0x4400000).bin Fail!\n");
        printf("open root(0x4400000).bin Fail!\n");
        printf("open root(0x4400000).bin Fail!\n");
        return 0;
    }
#endif
    gui_server_init();
    gui_app_startup(get_app_hongkong());
    return 0;
}

GUI_INIT_APP_EXPORT(app_init);

