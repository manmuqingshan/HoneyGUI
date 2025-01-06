==================
JavaScript Syntax
==================

Win
===

- This is a container widget.
- Operations on the window widget will affect the widgets nested in the container.
- Hiding the window will hide the nested widgets.
- When the window makes graphic transformations, such as panning and scaling, the nested widgets will make consistent transformations.
- This widget can monitor multiple gestures.

Hide A Window
-------------

- This ``win`` variable is assigned the ``win`` tag ``'heat_win'``'s handle.
- The variable ``hid`` is assigned the handle of the ``hidden`` attribute of the ``win`` tag.
- The value of the ``hidden`` attribute is set to ``'hidden'`` to achieve hiding.

.. code-block:: javascript

   win.getElementById('heat_win') //win will become a handle for heat_win
   hid = win.getAttribute("hidden") //get attribute handle hid
   console.log(hid)
   if (!hid) {
       win.setAttribute("hidden", "hidden");
   }

Listen to Gestures
------------------

- The ``win.onPress`` function enables the win widget to monitor the event of the finger touching the screen. If the finger touches the screen within the area of the window, the parameter function will be executed.
- The ``win.onRelease`` function enables the win widget to monitor the event of the finger leaving the screen.
- This ``winNromalOnPressFunc`` function will be executed when the finger touches the screen.
- This ``winNromalOnReleaseFunc`` function will be executed when the finger leaves the screen.

.. code-block:: javascript

   win.getElementById('tab7Win')
   function winNromalOnPressFunc(params) {
       console.log('winNromalOnPressFunc')
   }
   win.onPress(winNromalOnPressFunc)

   function winNromalOnReleaseFunc(params) {
       console.log('winNromalOnReleaseFunc')
   }
   win.onRelease(winNromalOnReleaseFunc)

Swap Windows
------------

* The implementation logic is that clicking the current window will hide the current window and display another window.
* Click to swap windows between ``'cool_win'`` and ``'heat_win'``.
* The ``win.onClick`` function enables the win widget to monitor the event of the finger clicking the screen.
* This function ``win.removeAttribute`` is used to remove an attribute of the win tag. When the ``hidden`` attribute is removed, the widget corresponding to the ``win`` tag will be displayed.
* On a touch device, a click event is typically triggered when a user touches an element and then lifts their finger in a short time within the win area.

.. code-block:: javascript

   win.getElementById('cool_win')
   function hideCool(params) {
       console.log('hideCool')
       win.getElementById('cool_win')
       win.setAttribute("hidden", "hidden");
       win.getElementById('heat_win')
       win.removeAttribute("hidden") 
   }
   win.onClick(hideCool)
   
   win.getElementById('heat_win')
   function hideHeat(params) {
       console.log('hideHeat')
       win.getElementById('heat_win')
       win.setAttribute("hidden", "hidden");
       win.getElementById('cool_win')
       win.removeAttribute("hidden") 
   }
   win.onClick(hideHeat)

API
---

.. code-block:: javascript

    getElementById : function (win_name : string) {}
    onClick : function (callback_func) {}
    onRight : function (callback_func) {}
    onLeft : function (callback_func) {}
    onUp : function (callback_func) {}
    onDown : function (callback_func) {}
    onPress : function (callback_func) {}
    onRelease : function (callback_func) {}
    onHold : function (callback_func) {}
    getAttribute : function(attributeName : string) {},   //return attribute value //support "hidden"
    removeAttribute : function (attribute : string) {} //support "hidden"
    setAttribute :function(attributeName : string, value : any) {},  //support "hidden"

Button
======

Monitor Button Press Event
--------------------------

* Can be used to develop button press highlight effects or buttons that require quick response.
* Listen to press gesture, the function ``iconNromalOnPressFunc`` will trigger when finger touches screen within the area of the button.

.. code-block:: javascript

   icon.getElementById('iconNormal')

   function iconNromalOnPressFunc(params) {
       console.log('iconNromalOnPressFunc')
   }
   icon.onPress(iconNromalOnPressFunc)

API
---

.. code-block:: javascript

    getElementById : function (win_name : string) {},
    onClick : function (callback_func) {},
    onPress : function (callback_func) {},
    onRelease : function (callback_func) {},
    onHold : function (callback_func) {},
    getChildElementByTag : function (tag : string) {},
    write : function (text : string) {},

Text
====

Change Text Content 
-------------------

* Using ``textbox.write`` function.

.. code-block:: javascript

    textbox.getElementById('tab10text1')
    textbox.write('progress:'+seekbar.progress())

API
---

.. code-block:: javascript

    getElementById : function (win_name : string) {},
    write : function (text : string) {},
    setPosition : function (position : object) {}, //var position={x:0,y:0}

Seekbar
=======

Display Current Progress
------------------------

* Drag the progress bar and then the text shows the current progress.
* Function ``seekbar.progress`` can read and write the progress.
* Function ``seekbar.onPressing`` will listen for events where your finger is kept pressed on the screen. This parameter function will be executed in each frame, while the finger is in contact with the screen.

.. code-block:: javascript

   seekbar.getElementById('tab10Seek1')
   function seekbarOnPress(params) {
       console.log('seekbarOnPress')
   }
   seekbar.onPress(seekbarOnPress)
   function seekbarOnrelease(params) {
       console.log('seekbarOnrelease')
   }
   seekbar.onRelease(seekbarOnrelease)
   function seekbarOnPressing(params) {
       console.log('seekbarOnPressing')
       textbox.getElementById('tab10text1')
       textbox.write('progress:'+seekbar.progress())
   }
   seekbar.onPressing(seekbarOnPressing)

A Seekbar Animation That Increases From 0 to 100%
-------------------------------------------------

* The seekbar will display an animation that continuously progresses from start to finish and then loops back to the start, creating a perpetually moving progress bar.
* This function ``seekbar.setAnimate`` sets the frame animation of the seekbar, and the parameters passed are the frame animation callback and animation duration properties.
* Define an object ``curtainAnimateTiming`` to specify the timing properties for an animation. ``duration`` sets the duration of one cycle of the animation in milliseconds. ``iterations`` is the number of times the animation should repeat, and -1 indicates the animation should repeat indefinitely.

.. code-block:: javascript

   var curtainAnimateTiming = {
       duration: 2000,      // The duration of the animation in milliseconds (2000ms = 2 seconds)
       iterations: -1,      // The number of times the animation should repeat
                            // -1 indicates the animation should repeat indefinitely
   };
   var curtain_open = 0;
   seekbar.getElementById('curtain_bar')
   function curtainFrame(params) {
       animate= seekbar.animateProgress()
       seekbar.setAttribute("progress", animate)
   }
   seekbar.setAnimate(curtainFrame, curtainAnimateTiming)
   seekbar.palyAnimate()

API
---

.. code-block:: javascript

    getElementById : function (win_name : string) {},
    progress : function (progressToSet : number){},//get or set progress//return progress
    onPress : function (callback_func) {}, //gesture press
    onPressing : function (callback_func) {},//gesture pressing
    onRelease : function (callback_func) {},//gesture release
    setAnimate : function (frameCallback : function, config : object) {},// frameCallback function will be executed once every frame // var curtainAnimateTiming = {duration: 2000,iterations:1,}
    setAttribute :function(attributeName : string, value : any) {},  //support "hidden"
    getAttribute : function(attributeName : string) {},   //return attribute value //support "hidden"
    palyAnimate : function () {}, //Start animation

Switch
======

Listen to 2 Gestures
--------------------

* The switch control has two events, namely, being triggered by being turned on and being triggered by being turned off.
* This function ``sw.onOn`` is used to register the turned on event.
* This function ``sw.onOff`` is used to register the turned off event.

.. code-block:: javascript

   sw.getElementById('tab8Switch')
   function swOnOnFunc(params) {
       console.log('swOnOnFunc')
   }
   sw.onOn(swOnOnFunc)
   function swOnOffFunc(params) {
       console.log('swOnOffFunc')
   }
   sw.onOff(swOnOffFunc)
   sw.turnOn();

Turn on A Led (P1_1)
--------------------

.. code-block:: javascript

   var P1_1 = 9
   var LED1 = new Gpio(P1_1, 'out');
   function led1OnFunc(params) {
       console.log('led1OnFunc')
       LED1.writeSync(0)
   }
   sw.getElementById('living_switch')
   sw.turnOn()

- This is the ``writeSync``'s control gpio led implementation for RTL87X2G.
- First get gpio value and direction value, then use specify driver api to operate led.
- Refer to `onoff npm package usage <https://www.npmjs.com/package/onoff#usage>`_ for more information.

.. code-block:: c

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
   #ifdef RTL8762G

           if (!strcmp(direction, "out"))
           {
               mode = PIN_MODE_OUTPUT;
           }
           else if (!strcmp(direction, "in"))
           {
               mode = PIN_MODE_INPUT;
           }
           if (gpio >= 0)
           {
               gui_log("gpio%d, %d, %d", gpio, mode, write_value);
               drv_pin_mode(gpio, mode);
               drv_pin_write(gpio, write_value);

API
---

.. code-block:: javascript

    getElementById : function (win_name : string) {},
    onOn : function (func) {},
    onOff : function (func) {},
    onPress : function (func) {},
    turnOn : function (func) {},//turn on the switch
    turnOff : function (func) {},//turn off the switch

Image
=====

API
---

.. code-block:: javascript

    getElementById : function (widget_name : string) {},
    rotation : function (degree:number, centerX:number, centerY:number) {},
    scale : function (scaleRateX:number, scaleRateY:number) {},
    setMode : function (modeIndex:number) {},

App
===

API
---

.. code-block:: javascript

    open : function (appXML : string) {},
    close : function () {},

Progressbar
===========

API
---

.. code-block:: javascript

    getElementById : function (widget_name : string) {},
    progress : function (progressToSet : number):{},//get or set progress//return progress

Tab
===

API
---

.. code-block:: javascript

    getElementById : function (widget_name : string) {},
    jump : function (tabIndex : number) {}, //jump to horizontal tab 
    OnChange : function (func) {},//Listen for events where the index value changes
    getCurTab : function () {},//return x,y,z property