.. _Tab:

====
Tab
====

The tab widget enables you to create an unlimited number of tabs in both the x and y axes of the screen. Before integrating the tab widget, you must first establish a tabview widget to house the tabs. The direction of the generated tabs is denoted by idx and idy.

For an introduction to idx and idy, please refer to: :ref:`Tabview`


Usage
-----
Create Tab Widget
^^^^^^^^^^^^^^^^^^
:cpp:any:`gui_tab_create` is used to create a tab widget, where ``idx`` and ``idy`` represent the direction of the created tab.

Set Tab Style
^^^^^^^^^^^^^^
If you want to exhibit various switching effects when switching tabs, you can utilize the :cpp:any:`gui_tab_set_style` to set it. By default, the classic style is employed. The available switching effects include the following:


.. literalinclude:: ../../../realgui/widget/gui_tabview.h
   :language: c
   :start-after: /* T_SLIDE_STYLE enum start*/
   :end-before: /* T_SLIDE_STYLE enum end*/



Example
--------
Tab
^^^^^
The tab switching style can be customized, and developers can set the tab switching style using the function :cpp:any:`gui_tab_set_style`. Available styles include ``REDUCTION``, ``CLASSIC``, ``FADE``, ``REDUCTION_FADE``, ``TAB_ROTATE``, ``TAB_CUBE``, and ``TAB_PAGE``. The ``FADE`` style adjusts the tab's opacity during the switch, while the ``REDUCTION_FADE`` style changes both the size and opacity of the tab during the transition. In this example, the first three tabs are set to the ``TAB_CUBE`` style, and the last three tabs are set to the ``REDUCTION`` style, as shown in the animation below.

.. code-block:: c

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

    static void app_hongkong_ui_design(gui_app_t *app)
    {
        gui_log("app_hongkong_ui_design\n");

        gui_tabview_t *tv = gui_tabview_create(&(app->screen), "tabview", 0, 0, 0, 0);
        gui_win_t *win = gui_win_create(&(app->screen), "window", 0, 0, 0, 0);
        gui_obj_add_event_cb(win, (gui_event_cb_t)kb_button_cb, GUI_EVENT_KB_UP_PRESSED, NULL);
        gui_tabview_enable_pre_load(tv, true);

        gui_tab_t *tb_clock = gui_tab_create(tv, "tb_clock",           0, 0, 0, 0, 0, 0);
        gui_tab_t *tb_activity = gui_tab_create(tv, "tb_activity",     0, 0, 0, 0, 1, 0);
        gui_tab_t *tb_heart = gui_tab_create(tv, "tb_heart",           0, 0, 0, 0, 2, 0);
        gui_tab_t *tb_cube = gui_tab_create(tv, "tb_cube",           0, 0, 0, 0, 3, 0);
        gui_tab_t *tb_weather = gui_tab_create(tv, "tb_weather",       0, 0, 0, 0, 5, 0);
        gui_tab_t *tb_music = gui_tab_create(tv, "tb_music",           0, 0, 0, 0, 4, 0);
        gui_tab_t *tb_ani = gui_tab_create(tv, "tb_ani",          0, 0, 0, 0, 6, 0);
        page_tb_clock(gui_tab_get_rte_obj(tb_clock));
        page_tb_activity(gui_tab_get_rte_obj(tb_activity));
        page_tb_heart(gui_tab_get_rte_obj(tb_heart));
        page_tb_cube(gui_tab_get_rte_obj(tb_cube));
        page_tb_weather(gui_tab_get_rte_obj(tb_weather));
        page_tb_music(gui_tab_get_rte_obj(tb_music));

        gui_tab_set_style(tb_clock, TAB_CUBE);
        gui_tab_set_style(tb_activity, TAB_CUBE);
        gui_tab_set_style(tb_heart, TAB_CUBE);
        gui_tab_set_style(tb_cube, REDUCTION);
        gui_tab_set_style(tb_weather, REDUCTION);
        gui_tab_set_style(tb_music, REDUCTION);
    }


.. raw:: html

   <br>
   <div style="text-align: center"><img src="https://foruda.gitee.com/images/1721901439083426379/8f8f9db8_10641540.gif" width= "400" /></div>
   <br>


Tabview Rotate
^^^^^^^^^^^^^^
Unlike individual tab style changes, the tabview widget allows you to set a uniform switching style for all tabs using the function :cpp:any:`gui_tabview_set_style`. For example, you can set all tabs to styles such as ``REDUCTION``, ``CLASSIC``, ``FADE``, ``REDUCTION_FADE``, ``TAB_ROTATE``, ``TAB_CUBE``, or ``TAB_PAGE``. The following example demonstrates how to switch to the ``TAB_ROTATE`` style, with ``CLASSIC`` being the default style.


.. code-block:: c

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

    static void app_hongkong_ui_design(gui_app_t *app)
    {
        gui_log("app_hongkong_ui_design\n");

        gui_tabview_t *tv = gui_tabview_create(&(app->screen), "tabview", 0, 0, 0, 0);
        gui_win_t *win = gui_win_create(&(app->screen), "window", 0, 0, 0, 0);
        gui_obj_add_event_cb(win, (gui_event_cb_t)kb_button_cb, GUI_EVENT_KB_UP_PRESSED, NULL);
        gui_tabview_set_style(tv, TAB_ROTATE);
        gui_tabview_enable_pre_load(tv, true);

        gui_tab_t *tb_clock = gui_tab_create(tv, "tb_clock",           0, 0, 0, 0, 0, 0);
        gui_tab_t *tb_activity = gui_tab_create(tv, "tb_activity",     0, 0, 0, 0, 1, 0);
        gui_tab_t *tb_heart = gui_tab_create(tv, "tb_heart",           0, 0, 0, 0, 2, 0);
        gui_tab_t *tb_cube = gui_tab_create(tv, "tb_cube",           0, 0, 0, 0, 3, 0);
        gui_tab_t *tb_weather = gui_tab_create(tv, "tb_weather",       0, 0, 0, 0, 5, 0);
        gui_tab_t *tb_music = gui_tab_create(tv, "tb_music",           0, 0, 0, 0, 4, 0);
        gui_tab_t *tb_ani = gui_tab_create(tv, "tb_ani",          0, 0, 0, 0, 6, 0);
        page_tb_clock(gui_tab_get_rte_obj(tb_clock));
        page_tb_activity(gui_tab_get_rte_obj(tb_activity));
        page_tb_heart(gui_tab_get_rte_obj(tb_heart));
        page_tb_cube(gui_tab_get_rte_obj(tb_cube));
        page_tb_weather(gui_tab_get_rte_obj(tb_weather));
        page_tb_music(gui_tab_get_rte_obj(tb_music));
    }


.. raw:: html

   <br>
   <div style="text-align: center"><img src="https://foruda.gitee.com/images/1721902043698157443/1cb14773_10641540.gif" width= "400" /></div>
   <br>

Tabview Loop
^^^^^^^^^^^^^^
In a tabview, you can use the function :cpp:any:`gui_tabview_loop_x` to determine whether the tabs should loop continuously in the x-direction. Similarly, :cpp:any:`gui_tabview_loop_y` determines whether the tabs should loop continuously in the y-direction. The loop parameter is a boolean that specifies whether to enable the looping feature. If set to true, the tabs will loop continuously; if set to false, they will not.


.. code-block:: c

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

    static void app_hongkong_ui_design(gui_app_t *app)
    {
        gui_log("app_hongkong_ui_design\n");

        gui_tabview_t *tv = gui_tabview_create(&(app->screen), "tabview", 0, 0, 0, 0);
        gui_win_t *win = gui_win_create(&(app->screen), "window", 0, 0, 0, 0);
        gui_obj_add_event_cb(win, (gui_event_cb_t)kb_button_cb, GUI_EVENT_KB_UP_PRESSED, NULL);
        gui_tabview_set_style(tv, TAB_CUBE);
        gui_tabview_enable_pre_load(tv, true);
        gui_tabview_loop_x(tv, true);

        gui_tab_t *tb_clock = gui_tab_create(tv, "tb_clock",           0, 0, 0, 0, 0, 0);
        gui_tab_t *tb_activity = gui_tab_create(tv, "tb_activity",     0, 0, 0, 0, 1, 0);
        gui_tab_t *tb_heart = gui_tab_create(tv, "tb_heart",           0, 0, 0, 0, 2, 0);
        gui_tab_t *tb_cube = gui_tab_create(tv, "tb_cube",           0, 0, 0, 0, 3, 0);
        gui_tab_t *tb_weather = gui_tab_create(tv, "tb_weather",       0, 0, 0, 0, 5, 0);
        gui_tab_t *tb_music = gui_tab_create(tv, "tb_music",           0, 0, 0, 0, 4, 0);
        gui_tab_t *tb_ani = gui_tab_create(tv, "tb_ani",          0, 0, 0, 0, 6, 0);
        page_tb_clock(gui_tab_get_rte_obj(tb_clock));
        page_tb_activity(gui_tab_get_rte_obj(tb_activity));
        page_tb_heart(gui_tab_get_rte_obj(tb_heart));
        page_tb_cube(gui_tab_get_rte_obj(tb_cube));
        page_tb_weather(gui_tab_get_rte_obj(tb_weather));
        page_tb_music(gui_tab_get_rte_obj(tb_music));
    }

.. raw:: html

   <br>
   <div style="text-align: center"><img src="https://docs.realmcu.com/HoneyGUI/image/widgets/tabview_loop.gif" width= "400" /></div>
   <br>



API
----

.. doxygenfile:: gui_tab.h

