# Return

The bubble-shaped curve that can be dragged out on the left side of the screen is used to perform a return operation.

## Usage

### Create A Return Widget

Creating function is [gui_return_create(void *parent, const uint32_t *frame_array[], int array_size, void *return_cb, gui_obj_t *ignore_gesture_widget)](#gui_return_create). Users need to enter curve animation frame images file array ,and the return operation function.

## Example

```eval_rst

.. literalinclude:: ../../../realgui/example/screen_454_454/gui_menu/apps_in_menu.c
   :language: c
   :start-after: /*Define gui_app_return_array*/
   :end-before: /*Define gui_app_return_array end*/

.. literalinclude:: ../../../realgui/example/screen_454_454/gui_menu/apps_in_menu.c
   :language: c
   :start-after: /*gui_return_create*/
   :end-before: /*gui_return_create end*/

```
<br>
<div style="text-align: center"><img src="https://docs.realmcu.com/HoneyGUI/image/widgets/return.gif"  /></div>
<br>


```eval_rst

.. note::
  Please refer to ``realgui\example\screen_454_454\gui_menu\apps_in_menu.c`` for details.

```


<span id = "gui_return_create">

## API

</span>

```eval_rst

.. doxygenfile:: gui_return.h

```
