# Menu Cellular

The menu cellular widget display a icons set as a honeycomb shape menu.

## Usage

### Create Menu Cellular Widget

Creating function is [gui_menu_cellular_create(void *parent, int icon_size, uint32_t *icon_array[], int array_size)](#gui_menu_cellular_create). Users need to enter icons set's image file array.
### Config Offset

Function is [gui_menu_cellular_offset(gui_obj_t *menu_cellular, int offset_x, int offset_y)](#gui_menu_cellular_create). Users are able to adjust horizontal and vertical offset for better dispaly.

## Example
<details> <summary>code</summary>

```eval_rst

.. literalinclude:: ../../../realgui/example/screen_454_454/gui_menu/apps_in_menu.c
   :language: c
   :start-after: /*Define APP_MENU's entry func */
   :end-before: /*Define APP_MENU's entry func end*/
```
</details>
<br>
<div style="text-align: center"><img src="https://docs.realmcu.com/HoneyGUI/image/widgets/menu_cellular.gif"  /></div>
<br>



<span id = "gui_menu_cellular_create">

## API

</span>

```eval_rst

.. doxygenfile:: gui_menu_cellular.h

```
