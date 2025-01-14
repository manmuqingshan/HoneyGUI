多级菜单 (Multi level)
======================
该控件可用于需要管理复杂层次结构的GUI应用程序，例如嵌套的菜单结构和分层显示对象。使用此控件，开发人员可以灵活地管理和操作多层子窗口，实现特定层次和顺序对象的隐藏和显示，从而增强界面的动态性和交互性。

用法
-----
创建控件
~~~~~~~~

创建函数为 :cpp:any:`gui_multi_level_create`。此函数创建并初始化一个新的 :cpp:any:`gui_multi_level_t` 控件实例。

跳转到（层次，索引）
~~~~~~~~~~~~~~~~~~
函数为 :cpp:any:`gui_multi_level_jump`。此函数便于跳转到多层GUI结构中的特定层次和索引。

示例
-----

.. raw:: html

   <br>
   <div style="text-align: center"><img src="https://docs.realmcu.com/HoneyGUI/image/widgets/multi_level.gif" width= "400" /></div>
   <br>


- 在0~2层级中创建多级菜单，根据嵌套结构。

.. literalinclude:: ../../../realgui/example/screen_454_454/gui_menu/apps_in_menu.c
   :language: c
   :start-after: /* Create multi levels in 0~2 level*/
   :end-before: /* GUI_APP_ENTRY(APP_SETTING) end */

- `ui_design_xx`  函数将在显示特定（层次，索引）多层窗口时创建显示内容。


.. literalinclude:: ../../../realgui/example/screen_454_454/gui_menu/apps_in_menu.c
   :language: c
   :start-after: /* define of ui_design_0 of (0,0)*/
   :end-before: /* define of ui_design_1_0 of (1,0)*/

API
---

.. doxygenfile:: gui_multi_level.h