.. _选项卡容器 (Tabview):

=====================
选项卡容器 (Tabview)
=====================

选项卡容器控件 (Tabview) 是一个用于存储选项卡 (Tab) 的容器，并根据用户选择切换并显示不同的选项卡。如下图所示，每个矩形表示不同的选项卡控件，9个选项卡控件共同组成选项卡容器，其中蓝色区域代表当前显示区域。``idx`` 表示X轴上的索引，``idy`` 表示Y轴上的索引。


.. figure:: https://foruda.gitee.com/images/1727058851305177488/b3542c64_13408154.png
   :align: center
   :width: 600px

   选项卡分布


用法
-----
创建选项卡容器
~~~~~~~~~~~~~~
使用 :cpp:any:`gui_tabview_create` 函数可以创建一个选项卡容器。

选项卡切换
~~~~~~~~~~~
在使用过程中，默认情况下选项卡页的切换一般是通过左右或者上下滑动进行，如果用户希望快速切换到某一个指定的选项卡页时，就需要使用 :cpp:any:`gui_tabview_jump_tab` 这个函数来实现。该函数可以实现跳转到指定选项卡页的功能，并通过 ``idx`` 和 ``idy`` 来指定选项卡页的位置。

设置选项卡切换风格
~~~~~~~~~~~~~~~~~~
开发者可以使用 :cpp:any:`gui_tabview_set_style` 来设置所需的选项卡容器样式。默认情况下，使用的是经典样式 ``CLASSIC``。具体的切换风格请参考下列枚举：


.. literalinclude:: ../../../realgui/widget/gui_tabview/gui_tabview.h
   :language: c
   :start-after: /* T_SLIDE_STYLE enum start*/
   :end-before: /* T_SLIDE_STYLE enum end*/



设置选项卡循环显示
~~~~~~~~~~~~~~~~~~~
选项卡容器循环功能是一项巧妙的特性，可以让用户轻松地遍历所有已创建的选项卡页。通过使用 :cpp:any:`gui_tabview_loop_x` 启用x反向的循环显示功能，:cpp:any:`gui_tabview_loop_y` 启用y反向的循环显示功能，如图a所示，可以看到蓝色的外框表示当前屏幕的可视选项卡控件。箭头的方向表示选项卡切换的方向。当向左滑动时，一旦所有选项卡都移至可见范围的左侧，再次左滑将从最左侧已创建的选项卡开始循环。相反，如图b所示，当再次向右滑动时，显示将从最右侧的选项卡开始循环。


.. figure:: https://foruda.gitee.com/images/1737357436952016270/569e58cc_13408154.png
   :align: center
   :width: 400px

   图 a


.. figure:: https://foruda.gitee.com/images/1737357500617800758/e845c1e5_13408154.png
   :align: center
   :width: 400px

   图 b


示例
-----
请参考该章节：:ref:`选项卡 (Tab)`


API
-----

.. doxygenfile:: gui_tabview.h

