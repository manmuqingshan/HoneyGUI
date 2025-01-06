==========
Middleware
==========

RVD exports the SaaA package. The firmware needs to parse and play it.

.. image:: https://foruda.gitee.com/images/1715938743160813708/833fbdab_10088396.png
   :alt: saaa.png
   :align: center

Package
=======

+--------------+-----------------------------------------------------+---------------------------------------------------------+
| Resource     | XML                                                 | JavaScript                                              |
+==============+=====================================================+=========================================================+
| Pictures and | Describes the initial nested tree structure and     | Customized behaviors, such as triggering behaviors of   |
| font files,  | specific parameters of the widget                   | widget gesture events, peripheral operations, printing  |
| etc.         |                                                     | logs, etc.                                              |
+--------------+-----------------------------------------------------+---------------------------------------------------------+

* Packages are in the ``root/app`` folder of File system image, and a launcher in firmware will iterate through these packages and set a start button on the screen for each package. Click the button to start the corresponding package.

Launcher
========

* The implementation of the launcher is in this file ``realgui\SaaA\frontend_launcher.c``.
* It uses a grid widget to layout the apps' button. Then it iterates the ``app`` folder, to find all XML files, which represent apps.
* The launcher gets the title and icon of the APP, and use a button widget to display them. The click event of the registration button is to start the app.

.. image:: https://foruda.gitee.com/images/1715938973907688018/ce054910_10088396.png
   :alt: launcher.png
   :align: center

XML
===

* The xml file in the APP package describes the initial nested tree structure and specific parameters of the widget.
* Using ``realgui\3rd\ezXML`` to convert xml to C language data format. Please refer to `ezXML SourceForge <https://ezxml.sourceforge.net/>`_ for details.
* The implementation of the xml parser is in this file ``realgui\DOM\XML_DOM.c``. You can read the syntax description on the ``XML syntax`` page.
* According to the syntax protocol, this function ``foreach_create`` uses a recursive strategy to traverse each tag of xml and map the tag to the widget, configure the tag's attributes to the widget.
* After the xml traversal is completed, a C-APP has actually been created in the firmware, which is no different from the result of directly using the C-APP api.
* Then the JavaScript file mentioned in xml will be executed.

.. image:: https://foruda.gitee.com/images/1727329150060233120/0353e15b_10088396.png
   :alt: xml.png
   :align: center

JavaScript
==========

* JavaScript describes Customized behaviors, such as triggering behaviors of widget gesture events, peripheral operations, printing logs, etc.
* Based on JerryScript engine on ``realgui\3rd\js`` for common syntax. Please refer to `JerryScript <https://jerryscript.net/>`_ for details.
* The implementation of the JavaScript parser is files starting with js in this folder ``realgui\SaaA``. You can read the syntax description on the ``JavaScript syntax`` page.
* ``DECLARE_HANDLER`` is used to define a function as a C language implementation of a JavaScript function.
* ``REGISTER_METHOD`` and ``REGISTER_METHOD_NAME`` are used to add a function to a javascript object, so you can call it in script.
* In a javascript file, there are some variable definitions, function definitions, and function calls. When the app starts, as mentioned above, the JavaScript file will be executed at the end of the XML parsing, and the function calls in it will be executed, mainly some initialization behaviors and the registration of event listeners.
* The callback functions of those events will not be executed until the event occurs.

.. image:: https://foruda.gitee.com/images/1727329518743167154/2b01e446_10088396.png
   :alt: js.png
   :align: center

Example
=======

Progressbar API
---------------

.. code-block:: javascript

   //Read and write the progress value of a progressbar tag called 'tag name'
   progressbar.getElementById('tag name')
   var progress = progressbar.progress(0.7)

Define A Progressbar Object
---------------------------

In fact, this object is added to the global object. Using property of the global object does not require explicitly calling the global object.

.. code-block:: c

   jerry_value_t progress = jerry_create_object();
   js_set_property(global_obj, "progressbar", progress);

Add 2 Functions to The Progressbar Object
-----------------------------------------

.. code-block:: c

   REGISTER_METHOD(progress, progress);
   REGISTER_METHOD(progress, getElementById);

Define 2 Functions
------------------

* The ``progress`` is used to write and read the progressbar's progress.
* Input formal parameters are in the array ``args``. The first in it is the progress number. If this parameter exists, which means that the progress needs to be set. Using ``jerry_get_number_value()`` to convert javascript parameter to c language variable.
* The return value is the progress you want to get, using ``jerry_create_number`` to convert c language variable to javascript variable. By the way, the form of these javascript variables in C language is an index of an unsigned integer.

.. code-block:: c

   DECLARE_HANDLER(progress)
   {
       gui_obj_t *obj = NULL;
       jerry_get_object_native_pointer(this_value, (void *)&obj, NULL);
       if (args_cnt >= 1 && jerry_value_is_number(args[0]))
       {
           gui_progressbar_set_percentage((void *)obj, jerry_get_number_value(args[0]));
       }
       float per = gui_progressbar_get_percentage((void *)obj);
       return jerry_create_number(per);
   }

* The ``getElementById`` is used to get the tag handle, refer to `getElementById on MDN <https://developer.mozilla.org/en-US/docs/Web/API/Document/getElementById>`_ for more usage.
* Input formal parameter is the tag's specified name. Using ``js_value_to_string`` to convert JS form name to C form char array, and get the pointer handle, and assign value to tag. It is a little different from standard function definitions, which return the new instantiate tag.

.. code-block:: c

   DECLARE_HANDLER(getElementById)
   {
       if (args_cnt != 1 || !jerry_value_is_string(args[0]))
       {
           return jerry_create_undefined();
       }
       jerry_value_t global_obj = jerry_get_global_object();
       jerry_value_t app_property = js_get_property(global_obj, "app");
       gui_app_t *app = NULL;
       jerry_get_object_native_pointer(app_property, (void *)&app, NULL);
       gui_obj_t *widget = NULL;
       char *a = js_value_to_string(args[0]);
       gui_obj_tree_get_widget_by_name(&app->screen, a, &widget);
       gui_free(a);
       jerry_set_object_native_pointer(this_value, widget, NULL);
       jerry_release_value(global_obj);
       jerry_release_value(app_property);
       return jerry_create_undefined();
   }

Light Control
-------------

This page shows how the UI switch corresponds to the peripheral switch.

.. code-block:: javascript

   //IO P1_1 is set to low level
   var P1_1 = 9
   var LED1 = new Gpio(P1_1, 'out');
   LED1.writeSync(0)

Light Switch Data
-----------------

+----------------+--------------+--------------------------------------------------------+
| Data           | Value type   | Brief                                                  |
+================+==============+========================================================+
| gpio           | number       | index of light                                         |
+----------------+--------------+--------------------------------------------------------+
| direction      | out / in     | direction of signal                                    |
+----------------+--------------+--------------------------------------------------------+
| write value    | number       | 0 for turning off / 1 for turning on                  |
+----------------+--------------+--------------------------------------------------------+

- Refer to `onoff npm package usage <https://www.npmjs.com/package/onoff#usage>`_ for more information.

GPIO Light Switch
-----------------

- Get gpio index, direction, and write value.
- Use gpio driver ``drv_pin_mode()`` & ``drv_pin_write()`` to operate it.

MATTER Light Switch
-------------------

- Get gpio index, and write value.
- Transform data to matter protocol.
- Use ``matter_send_msg_to_app()`` to operate lights.

MESH Light Switch
-----------------

- Get gpio index, and write value.
- Transform data to mesh protocol.
- Use ``matter_send_msg_to_app()`` to operate lights.

The following code example is the ``writeSync``'s control light implementation for RTL87X2G. First get gpio value and direction value, then use specify driver API to operate light.

.. code-block:: c

   #ifdef RTL87x2G
   #define ENABLE_MATTER_SWITCH
   #define ENABLE_MESH_SWITCH
   #define ENABLE_GPIO_SWITCH
   #endif

   #if defined ENABLE_GPIO_SWITCH
   #include "rtl_gpio.h"
   #include "rtl_rcc.h"
   #include "drv_gpio.h"
   #include "drv_i2c.h"
   #include "drv_touch.h"
   #include "drv_lcd.h"
   #include "touch_gt911.h"
   #include "string.h"
   #include "trace.h"
   #include "utils.h"
   #endif

   #if defined ENABLE_MESH_SWITCH
   #include "app_msg.h"
   T_IO_MSG led_msg = {.type = IO_MSG_TYPE_LED_ON};
   T_IO_MSG led_off_msg = {.type = IO_MSG_TYPE_LED_OFF};
   #endif

   #if defined ENABLE_MATTER_SWITCH
   #endif

   DECLARE_HANDLER(writeSync)
   {
       gui_log("enter writeSync:%d\n", args[0]);
       if (args_cnt >= 1 && jerry_value_is_number(args[0]))
       {
           int write_value = jerry_get_number_value(args[0]);
           int gpio = -1;
           jerry_value_t v1;
           jerry_value_t v2;
           v1 = js_get_property(this_value, "gpio");
           v2 = js_get_property(this_value, "direction");
           gpio = jerry_get_number_value(v1);
           jerry_release_value(v1);
           char *direction = js_value_to_string(v2);
           jerry_release_value(v2);
           int mode = 0;

           if (gpio >= 0)
           {
               gui_log("gpio%d, %d, %d", gpio, mode, write_value);

               /**
                * GPIO
                */
               #ifdef ENABLE_GPIO_SWITCH
               if (!strcmp(direction, "out"))
               {
                   mode = PIN_MODE_OUTPUT;
               }
               else if (!strcmp(direction, "in"))
               {
                   mode = PIN_MODE_INPUT;
               }
               drv_pin_mode(gpio, mode);
               drv_pin_write(gpio, write_value);
               #endif

               /**
                * MESH
                */
               #ifdef ENABLE_MESH_SWITCH
               extern bool app_send_msg_to_apptask(T_IO_MSG *p_msg);
               if(write_value == 0){
                   led_msg.u.param = 0x64+gpio;
                   app_send_msg_to_apptask(&led_msg);}
               else
               {
                   led_off_msg.u.param = 0x64+gpio;
                   app_send_msg_to_apptask(&led_off_msg);
               }
               #endif

               /**
                * MATTER
                */
               #ifdef ENABLE_MATTER_SWITCH
               if (gpio >= 0)
               {
                   extern bool matter_send_msg_to_app(uint16_t sub_type, uint32_t param);
                   uint32_t param = gpio << 8 | write_value;
                   if (gpio != 49052)
                   {
                       //single
                       matter_send_msg_to_app(0, param);
                   }
                   else
                   {
                       //group
                       matter_send_msg_to_app(1, param);
                   }
               #endif
           }

           gui_free(direction);
       }
       return jerry_create_undefined();
   }