# 规格常见问题

## 图形

| 平台  | 8762D  |8772F   |87X2D |PC   |8763E|
|---|---|---|---|---|---|
| RGB565  |  是 | 是  | 是  | 是  | 是  |
|  RGB888 | 否  | 是  |  是 |  是 | 否  |
|  ARGB8888 |  否 | 是  |  是 | 是  | 否  |
|  SVG | 否  | 是   |  否 |  是  | 否  |
| TTF | 否  | 是   |  否 |  是 | 否  |
| DOT字体  |  是 | 是  | 是  | 是  |是  |
|  矢量图形 | 否  | 是   |  否 |  是  |否 |
|  线性渐变 | 否  | 是   |  否 |  是  |否 |
|  径向渐变 | 否  | 否   |  否 |  是  |否 |

## 内存使用量

### 8772F示例

```eval_rst
.. raw:: html

    <iframe src="https://drive.google.com/file/d/1qpLBVJRt2gnRR_cpuXc9L06VjqwvpzS0/preview" width="640" height="480" allow="autoplay"></iframe>
```

该示例的内存消耗统计如下：
| 模块 | 占用  |
|---|---|
| 控件  |  14.56KB |
| 帧缓冲区  |  屏幕宽度 *像素字节数* 行数 |
| 线程堆栈  |  10KB |

### 控件内存使用量

| 控件 | 内存(字节)系统芯片 | 内存(字节)模拟器 |
|---|---|---|
|对象(obj) | 52| 88|
|图像(img) | 112|178|
|窗口(win) | 72|112|
|页面(page) | 124|184|
|选项卡(tab) | 88|136|
|选项卡视图(tabview) | 100|160|
|按钮(button) | 88|160|
|文本框(text) | 100|176|
|滚动文本框(scroll_text) | 120|200|
|应用(app) | 92|152|
|画布-圆弧(canvas_arc) | 156|264|
|画布-矩形(canvas_rect) | 64|104|
|画布(canvas) | 60|104|
|卡片(card) | 72|112|
|卡片视图(cardview) | 124|176|
|调色盘(colorwheel) | 72|112|
|立方体(cube) | 748|928|
|窗帘(curtain) | 60|96|
|窗帘视图(curtainview) | 120|168|
|画廊(gallery) | 112|184|
|网格(grid) | 100|144|
|动态图像(img_live) | 84|144|
|范围图像(img_scope) | 124|192|
|stb图像(stb_img) | 76|144|
|键盘(kb) | 108|192|
|地图(map) | 196|272|
|细胞菜单(menu_cellular) | 76|120|
|多级菜单(multi_level) | 60|104|
|页面列表(pagelist) | 96|160|
|页面列表视图(pagelistview) | 64|112|
|透视(perspective) | 736|920|
|进度条(progressbar) | 80|136|
|二维码和条形码(qbcode) | 84|136|
|滚轮(scroll_wheel) | 388|696|
|进度条(seekbar) | 128|216|
|简单图像(simple_img) | 68|120|
|可缩放矢量图形(svg) | 96|144|
|轮盘(turn_table) | 128|192|
|监视渐变点(watch_gradient_spot) | 60|96|
|波(wave) | 72|112|
|轮形列表(wheel_list) | 64|112|