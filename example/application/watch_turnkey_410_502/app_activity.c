/*============================================================================*
 *                        Header Files
 *============================================================================*/
#include <math.h>
#include <time.h>
#include "root_image/ui_resource.h"
#include "gui_img.h"
#include "gui_win.h"
#include "gui_text.h"
#include "cJSON.h"
#include "gui_canvas.h"
#include "guidef.h"
#include "gui_view.h"
#include "app_main_watch.h"
#include "gui_list.h"

/*============================================================================*
 *                            Macros
 *============================================================================*/
#ifdef M_PI
#undef M_PI
#define M_PI 3.1415926f
#else
#define M_PI 3.1415926f
#endif

#define SCREEN_WIDTH (int16_t)gui_get_screen_width()
#define SCREEN_HEIGHT (int16_t)gui_get_screen_height()
#define CURRENT_VIEW_NAME "activity_view"
#define COUNT_MAX 250
#define RADIUS 190

/*============================================================================*
 *                           Function Declaration
 *============================================================================*/
static void activity_design(gui_view_t *view);
static void clear_activity(gui_view_t *view);
extern void activity_move_design(gui_obj_t *obj);
extern void activity_exercise_design(gui_obj_t *obj);
extern void activity_stand_design(gui_obj_t *obj);

/*============================================================================*
 *                            Variables
 *============================================================================*/
static gui_view_t *current_view = NULL;
// const static gui_view_descriptor_t *menu_view = NULL;
static gui_view_descriptor_t const descriptor =
{
    /* change Here for current view */
    .name = (const char *)CURRENT_VIEW_NAME,
    .pView = &current_view,
    .on_switch_in = activity_design,
    .on_switch_out = clear_activity,
};

extern char *cjson_content;
static uint8_t *img_ring_data = NULL;
uint8_t *img_dot_data = NULL;
gui_img_t *img_ring;
gui_img_t *img_dot;
static uint16_t count = COUNT_MAX; //for timer
// static bool draw_flag = 0; //0: get new json data
bool has_draw_bg = 0; // only draw background once
static char move_content[30] = {0};
static char ex_content[30] = {0};
static char stand_content[30] = {0};

static char time_text_content[10];
gui_text_t *time_text;

uint8_t activeIndex = 0;
gui_win_t *win_menu_activity = NULL;
gui_win_t *win_activity = NULL;
gui_win_t *win_activity_arc = NULL;

gui_img_t *img_icon0 = NULL;
gui_img_t *img_icon1 = NULL;
gui_img_t *img_icon2 = NULL;
bool ring_flag_enter;
/*============================================================================*
 *                           Private Functions
 *============================================================================*/
static int gui_view_descriptor_register_init(void)
{
    gui_view_descriptor_register(&descriptor);
    gui_log("File: %s, Function: %s\n", __FILE__, __func__);
    return 0;
}
static GUI_INIT_VIEW_DESCRIPTOR_REGISTER(gui_view_descriptor_register_init);

static int gui_view_get_other_view_descriptor_init(void)
{
    /* you can get other view descriptor point here */
    // menu_view = gui_view_descriptor_get("menu_view");
    gui_log("File: %s, Function: %s\n", __FILE__, __func__);
    return 0;
}
static GUI_INIT_VIEW_DESCRIPTOR_GET(gui_view_get_other_view_descriptor_init);

static void clear_activity(gui_view_t *view)
{
    (void)view;
    if (img_ring_data)
    {
        gui_lower_free(img_ring_data);
        img_ring_data = NULL;
    }
    if (img_dot_data)
    {
        gui_lower_free(img_dot_data);
        img_dot_data = NULL;
    }
    activeIndex = 0;
    ring_flag_enter = false;
    has_draw_bg = 0;
    count = COUNT_MAX;
    if (img_ring && img_ring->base.timer)
    {
        gui_obj_stop_timer(GUI_BASE(img_ring));
    }
}

static void arc_activity_cb(NVGcontext *vg)
{
    static int move_val = 3750;
    static int ex_val = 15;
    static int stand_val = 10;

    uint8_t line_width = 32;
    uint8_t radius_max = RADIUS - line_width;
    uint8_t interval = 6;
    float progress = count / (float)COUNT_MAX;

    if (!has_draw_bg)
    {
        has_draw_bg = true;
        nvgBeginPath(vg);
        nvgArc(vg, RADIUS, RADIUS, radius_max, 3 * M_PI / 2,
               M_PI * 3.5f, NVG_CW);
        nvgStrokeWidth(vg, line_width);
        nvgStrokeColor(vg, nvgRGB(58, 23, 29));
        nvgStroke(vg);

        nvgBeginPath(vg);
        nvgArc(vg, RADIUS, RADIUS, radius_max - (line_width + interval), 3 * M_PI / 2,
               M_PI * 3.5f, NVG_CW);
        nvgStrokeWidth(vg, line_width);
        nvgStrokeColor(vg, nvgRGB(30, 55, 25));
        nvgStroke(vg);

        nvgBeginPath(vg);
        nvgArc(vg, RADIUS, RADIUS, radius_max - 2 * (line_width + interval), 3 * M_PI / 2,
               M_PI * 3.5f, NVG_CW);
        nvgStrokeWidth(vg, line_width);
        nvgStrokeColor(vg, nvgRGB(22, 50, 47));
        nvgStroke(vg);
    }

    nvgBeginPath(vg);
    nvgArc(vg, RADIUS, RADIUS, radius_max, 3 * M_PI / 2,
           M_PI * (1.5f + 2.0f * move_val * progress / 20000.0f), NVG_CW);  // cap 20000 steps
    nvgStrokeWidth(vg, line_width);
    nvgStrokeColor(vg, nvgRGB(230, 67, 79));
    nvgStroke(vg);

    nvgBeginPath(vg);
    nvgArc(vg, RADIUS, RADIUS, radius_max - (line_width + interval), 3 * M_PI / 2,
           M_PI * (1.5f + 2.0f * ex_val * progress / 30.0f), NVG_CW);  // cap 30 min.
    nvgStrokeWidth(vg, line_width);
    nvgStrokeColor(vg, nvgRGB(186, 253, 79));
    nvgStroke(vg);

    nvgBeginPath(vg);
    nvgArc(vg, RADIUS, RADIUS, radius_max - 2 * (line_width + interval), 3 * M_PI / 2,
           M_PI * (1.5f + 2.0f * stand_val * progress / 12.0f), NVG_CW); // cap 1 hour
    nvgStrokeWidth(vg, line_width);
    nvgStrokeColor(vg, nvgRGB(117, 230, 229));
    nvgStroke(vg);
    gui_fb_change();
    // gui_log("progress: %f\n", progress);
}
void drawCircles_cb(NVGcontext *vg)
{
    float circleDiameter = 12.0f;
    float circleRadius = circleDiameter / 2.0f;
    float spacing = 4.0f;

    float startX = 0;
    float startY = 0;

    NVGcolor circleColor = nvgRGB(120, 80, 90);
    NVGcolor specialCircleColor = nvgRGB(255, 255, 255);
    // gui_log("activeIndex: %d\n", activeIndex);
    for (int i = 0; i < 6; ++i)
    {
        nvgBeginPath(vg);

        float y = startY + i * (circleDiameter + spacing) + circleRadius;
        nvgCircle(vg, startX + circleRadius, y, circleRadius);

        if (activeIndex == 0)
        {
            nvgFillColor(vg, specialCircleColor);
        }
        else if (i == activeIndex - 1)
        {
            nvgFillColor(vg, specialCircleColor);
        }
        else
        {
            nvgFillColor(vg, circleColor);
        }

        nvgFill(vg);
    }
}
static void activity_timer_cb(void *obj)
{
    GUI_UNUSED(obj);
    if (current_view->current_transition_style < SWITCH_OUT_NONE_ANIMATION &&
        gui_view_get_next() != NULL)
    {
        return;
    }

    gui_obj_timer_t *timer = img_ring->base.timer;

    count += timer->interval_ms;
    uint8_t *img_ring_data = (void *)gui_img_get_image_data(img_ring);
    gui_canvas_render_to_image_buffer(GUI_CANVAS_OUTPUT_RGBA, 0, RADIUS * 2, RADIUS * 2,
                                      arc_activity_cb, img_ring_data);
    gui_img_set_image_data(img_ring, img_ring_data);
    gui_img_refresh_size(img_ring);

    // dot img
    // gui_canvas_render_to_image_buffer(GUI_CANVAS_OUTPUT_RGBA, 0, 12, 96,
    //     drawCircles_cb, img_dot_data);
    // gui_img_set_image_data(img_dot, img_dot_data);
    // gui_img_refresh_size(img_dot);

    if (count >= COUNT_MAX)
    {
        count = 0;
        gui_obj_stop_timer(GUI_BASE(img_ring));
    }
}

static void enter_timer_cb(void *obj)
{
    gui_view_t *view = gui_view_get_current();
    // if (strcmp(GUI_BASE(view)->name, CURRENT_VIEW_NAME) == 0)
    {
        count = 0;
        has_draw_bg = false;
        activeIndex = 0;
        uint8_t *img_ring_data = (void *)gui_img_get_image_data(img_ring);
// gui_log("Function: %s line: %d\n", __func__, __LINE__);
        // int image_h = RADIUS * 2;
        // int image_w = RADIUS * 2;
        // int pixel_bytes = 4;
        // size_t buffer_size = image_h * image_w * pixel_bytes + sizeof(gui_rgb_data_head_t);
        // memset(img_ring_data, 0, buffer_size);
        gui_obj_create_timer(GUI_BASE(img_ring), 10, true, activity_timer_cb);
        gui_obj_start_timer(GUI_BASE(img_ring));
        gui_obj_stop_timer(GUI_BASE(obj));
    }
}
void time_update_cb(void *p)
{
    GUI_UNUSED(p);
    time_t rawtime;
    struct tm timeinfo;

#ifdef __WIN32
    struct tm *tmp;
    time(&rawtime);
    tmp = localtime(&rawtime);
    if (tmp != NULL)
    {
        timeinfo = *tmp;
    }
#else
    time(&rawtime);
    localtime_r(&rawtime, &timeinfo);
#endif

    sprintf(time_text_content, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);

    // gui_text_t *time_text = gui_text_create(p, "time_text", -30, 33, 0, 0);
    gui_text_set(time_text, (void *)time_text_content, GUI_FONT_SRC_TTF, APP_COLOR_WHITE,
                 strlen(time_text_content), 36);
    gui_text_type_set(time_text, SF_COMPACT_TEXT_BOLD_BIN, FONT_SRC_MEMADDR);
    gui_text_mode_set(time_text, RIGHT);
    gui_text_rendermode_set(time_text, 2);
}
// extern void activity_move_design(gui_view_t *view);
static void imageIcon_not_show(void)
{
    if (activeIndex == 0)
    {
        img_icon0->base.not_show = 0;
        img_icon1->base.not_show = 0;
        img_icon2->base.not_show = 0;
    }
    else if (activeIndex == 1)
    {
        img_icon0->base.not_show = 1;
        img_icon1->base.not_show = 1;
        img_icon2->base.not_show = 1;
    }
}
static void note_design(gui_obj_t *obj, void *p)
{
    GUI_UNUSED(p);
    // note_design_param_t *design_p = (note_design_param_t *)p;
    gui_list_note_t *note = (gui_list_note_t *)obj;
    uint16_t index = note->index;
    // static const char *text_array[4];
    gui_log("index: %d ring_flag_enter: %d\n", index, ring_flag_enter);
    if (index < 4)
    {
        if (index == 0)
        {
            activeIndex = 0;
            imageIcon_not_show();
            //refresh dot img
            gui_canvas_render_to_image_buffer(GUI_CANVAS_OUTPUT_RGBA, 0, 12, 96,
                                              drawCircles_cb, img_dot_data);
            gui_img_set_image_data(img_dot, img_dot_data);
            gui_img_refresh_size(img_dot);

            if (ring_flag_enter == true)
            {
                time_update_cb(NULL);
                ring_flag_enter = false;
                gui_obj_timer_t *timer = img_ring->base.timer;
                count += timer->interval_ms;
                float progress = count / (float)COUNT_MAX;
                float arc_scale = 1 + progress;
                gui_img_scale(img_ring, arc_scale, arc_scale);
                gui_img_translate(img_ring, 0.9f * arc_scale, 1.0f * arc_scale);

                // gui_obj_start_timer(GUI_BASE(img_ring));
                if ((count >= COUNT_MAX) || arc_scale > 1.0f)
                {
                    count = 0;
                    gui_obj_stop_timer(GUI_BASE(img_ring));
                }

            }
        }
        if (index == 1)
        {
            imageIcon_not_show();
            gui_obj_stop_timer(GUI_BASE(img_ring));
            activity_move_design((gui_obj_t *)obj);
        }

        else if (index == 2)
        {
            activity_exercise_design((gui_obj_t *)obj);
        }
        else if (index == 3)
        {
            activity_stand_design((gui_obj_t *)obj);
        }
        // else if(index == 4)
        // {
        //     text_array[index] = "Today";
        // }
        // else if(index == 5)
        // {

        // }
    }
    return;

}
static void activity_design(gui_view_t *view)
{
    gui_obj_t *obj = GUI_BASE(view);
    has_draw_bg = false;
    ring_flag_enter = false;
    activeIndex = 0;
    gui_log("File: %s, Function: %s\n", __FILE__, __func__);
    win_activity = gui_win_create(obj, "win_activity", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // win_menu_activity = gui_win_create(obj, "win_menu_activity", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // gui_img_create_from_mem(win_activity, "bg_move", (void *)ACTIVITY_APP_BG2_BIN, 0, 0, 0, 0);
    // draw_flag = 0;
    //create list
    int length = 502;
    uint8_t space = 0;
    gui_list_t *list = gui_list_create(view, "list", 0, 0, 0, 0, length, space, VERTICAL,
                                       note_design, NULL,
                                       false);
    gui_list_set_style(list, LIST_FADE);
    gui_list_set_note_num(list, 5);
    gui_list_set_auto_align(list, true);
    gui_list_set_inertia(list, false);
    gui_list_set_out_scope(list, length / 2);

    win_menu_activity = gui_win_create(obj, "win_menu_activity", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    win_activity_arc = gui_win_create(obj, "win_activity_arc", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // img ring
    int image_w = RADIUS * 2;
    int image_h = RADIUS * 2;
    int pixel_bytes = 4;

    size_t buffer_size = image_h * image_w * pixel_bytes + sizeof(gui_rgb_data_head_t);
    if (img_ring_data == NULL)
    {
        img_ring_data = gui_lower_malloc(buffer_size);
    }
    memset(img_ring_data, 0, buffer_size);
    img_ring = gui_img_create_from_mem(win_activity_arc, 0, (void *)img_ring_data,
                                       SCREEN_WIDTH / 2 - RADIUS, 66, 0, 0);
    gui_img_set_mode(img_ring, IMG_SRC_OVER_MODE);
    gui_img_set_quality(img_ring, true);

    //img dot
    buffer_size = 12 * 96 * pixel_bytes + sizeof(gui_rgb_data_head_t);
    if (img_dot_data == NULL)
    {
        img_dot_data = gui_lower_malloc(buffer_size);
    }
    memset(img_dot_data, 0, buffer_size);
    img_dot = gui_img_create_from_mem(win_menu_activity, "dot_img", (void *)img_dot_data,
                                      393, 82, 0, 0);
    gui_img_set_mode(img_dot, IMG_SRC_OVER_MODE);
    gui_img_set_quality(img_dot, true);

    sprintf(time_text_content, "14:21");
    time_text = gui_text_create(win_menu_activity, "date_text", -30, 33, 0, 0);
    gui_text_set(time_text, (void *)time_text_content, GUI_FONT_SRC_TTF, APP_COLOR_WHITE,
                 strlen(time_text_content), 28);
    gui_text_type_set(time_text, SF_COMPACT_TEXT_BOLD_BIN, FONT_SRC_MEMADDR);
    gui_text_mode_set(time_text, RIGHT);
    gui_text_rendermode_set(time_text, 2);

    img_icon0 = gui_img_create_from_mem(win_activity, "icon0", (void *)ACTIVITY_LEFT_CONTROL0_BIN, 19,
                                        23, 0, 0);
    img_icon1 = gui_img_create_from_mem(win_activity, "icon1", (void *)ACTIVITY_LEFT_CONTROL_BIN, 19,
                                        397, 0, 0);
    img_icon2 = gui_img_create_from_mem(win_activity, "icon2", (void *)ACTIVITY_RIGHT_CONTROL0_BIN, 326,
                                        397, 0, 0);
    time_update_cb(NULL);
    // gui_obj_create_timer(obj, 10, true, enter_timer_cb);
    gui_obj_create_timer(GUI_BASE(img_ring), 10, true, activity_timer_cb);
    gui_obj_start_timer(GUI_BASE(img_ring));
    return;
}
