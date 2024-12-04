.. _幕布容器 (Curtainview):

======================
幕布容器 (Curtainview)
======================

幕布容器控件 (Curtainvew) 可容纳多个幕布控件。在创建的幕布控件上可以放置应用程序相关的信息，例如应用程序菜单或应用程序等信息。该控件可以根据需要进行扩展，并可以根据需要进行自定义。如下图所示，幕布容器控件由五个幕布组成，分别在上/下/右/左/中五个方向进行排列。

.. figure:: https://foruda.gitee.com/images/1727088694333469506/7c243250_13408154.png
   :align: center
   :width: 400px

   幕布分布

用法
-----
创建幕布容器控件
~~~~~~~~~~~~~~~~
使用 :cpp:any:`gui_curtainview_create` 函数创建一个可以容纳幕布控件的容器。

回调函数
~~~~~~~~
幕布扩展完成后，可以使用 :cpp:any:`gui_curtainview_set_done_cb` 函数来实现某些回调事件。

示例
-----
请参考该章节：:ref:`幕布 (Curtain)`

API
-----

.. doxygenfile:: gui_curtainview.h

