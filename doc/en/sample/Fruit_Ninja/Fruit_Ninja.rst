.. _Fruit Ninja:

==============
Fruit Ninja
==============

This example demonstrates how to develop a simple "Fruit Ninja" APP, from which you can learn and understand the basic methods and processes of developing a UI application. Earn points by cutting fruits until you cut a bomb and the game is over. Watch the demo video below to see its full functionality.

.. raw:: html

   <br>
   <div style="text-align: center"><img src="https://foruda.gitee.com/images/1723621216978994553/76b62adc_10737458.gif" width= "450" /></div>
   <br>

.. _Requirements:

Requirements
-------------
Refer to the Installation section of :ref:`Get Started` .

.. _Source File:

Source File
------------
To help learn and be familiar with the development, you can find all source files you may need in path ``realgui\example\screen_454_454``. The source file for this demostration is ``app_fruit_ninja_box2d.cpp``, you can find it in the path mentioned for more details.

.. _Configurations:

Configurations
---------------

.. code-block:: c
   
   #define SCREEN_WIDTH 454    // Set according to the screen width
   #define SCREEN_HEIGHT 454   // Set according to the screen height
   #define HEIGHT_OFFSET 100   // Set the screen height offset for refreshing fruit from the bottom of the screen

.. _Usage Steps:

Usage Steps
------------

Step 1:  Declare the app ui design function
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C

   /** 
   * @brief Start Fruit Ninja APP by creating a window,
   *        setting the animation function of the window 
   *        and initializing some variables.
   * @param obj The parent widget where the APP's window is nested.
   */
   void fruit_ninja_design(gui_obj_t *obj)

   void app_fruit_ninja_design(gui_obj_t *obj)
   {
      app_fruit_ninja::fruit_ninja_design(obj);
   }

Step 2:  Call function
~~~~~~~~~~~~~~~~~~~~~~~~~
.. code-block:: c

   extern void app_fruit_ninja_design(gui_obj_t *obj);
   app_fruit_ninja_design(GUI_APP_ROOT_SCREEN);

.. _Design Ideas:

Design Ideas
-------------
+ In this app, box2d was used to create solids to simulate the movement of objects in a gravitational environment, given parameters such as the initial velocity of the x-axis and y-axis during initialization.

   .. code-block:: c

      /* Add dynamic bodys */
      b2BodyDef ballBodyDef;
      ballBodyDef.type = b2_dynamicBody;
      ballBodyDef.position.Set(4, SCREEN_HEIGHT + HEIGHT_OFFSET * P2M);
      ballBodyDef.angularVelocity = -314;    //-PI rad/s
      ballBodyDef.linearVelocity.Set(10, -20); // Move up
      body_st = world.CreateBody(&ballBodyDef);

+ The radius of the solid is set to a small value in order to minimize the effect of objects colliding with each other, since mutual collisions are detrimental to the gameplay.

   .. code-block:: c

      /* Creat body shape and attach the shape to the Body */
      b2CircleShape circleShape;
      circleShape.m_radius = 0.2; // Small radius reducing the impact of collisions

+ The position and rotation angle of the fruits (and bomb) are updated in the callback function using the solid's center point mapping and displayed in the image component. The position and initial velocity of the solid is reset when the position of the fruit is outside the display interface.

   .. code-block:: c

      /* Get the position of the ball then set the image location and rotate it on the GUI */
      b2Vec2 position = body_st->GetPosition();
      if (position_refresh((int)(position.x * M2P - RADIUS_ST), (int)(position.y * M2P - RADIUS_ST),
                           img_strawberry, body_st))
      {
         gui_img_set_attribute(img_strawberry, "img_strawberry", FRUIT_NINJA_STRAWBERRY_BIN,
                                 img_strawberry->base.x, img_strawberry->base.y);
         fruit_cut_flag[0] = false;
         gui_img_set_location(img_cut_arry[0], 0, SCREEN_HEIGHT + HEIGHT_OFFSET);
      }

+ Cutting fruit uses the structure touch_info, detecting the touch point release indicates the completion of a cut (to get the initial point of the touch screen and the displacement of the x-axis and y-axis), and the content of the cut will be judged.

   .. code-block:: c

      /* Cutting judgment */
      GUI_TOUCHPAD_IMPORT_AS_TP // Get touchpoint
      if (tp->released)
      {
         bool bomb_flag = cutting_judgment(win, img_strawberry, img_banana, img_peach, img_watermelon,
                                             img_bomb, tp, img_cut_arry, fruit_cut_flag);
      }

+ If there are two intersection points between the cut line and the picture rectangle, it means that the cut is valid. 

   .. code-block:: c

      line_has_two_intersections_with_rectangle(img_coordinate, img_w, img_h, tp_start, tp_end,
                                                                  img_rotate_angle);

+ Note that when calculating the intersection point, the rotated endpoint information of the picture needs to be brought into the calculation of the rotation angle to be consistent with the display, so that the accuracy of the cutting judgment can be improved.

   .. code-block:: c
      
      /* Calculate the rectangle's four rotated points */
      Point rotated_rect_min = rotate_point(rect_min, center, angle); // Left-up
      Point rotated_rect_max = rotate_point(rect_max, center, angle); // Right-down
      Point rotated_rect_p2 = rotate_point(rect_p2, center, angle); // Left-down
      Point rotated_rect_p3 = rotate_point(rect_p3, center, angle); // Right-top

+ Update the fruit picture to two pictures after cutting (corresponding to two gui_img_t pointers) and count the score. Multiple different objects can be cut in a single cut.

   .. code-block:: c

      /* Refresh half-cut fruits position */
      if (fruit_cut_flag[0])
      {
         gui_img_set_location(img_cut_arry[0],  GUI_BASE(img_strawberry)->x + 10,
                                 GUI_BASE(img_strawberry)->y + 10);
         gui_img_rotation(img_cut_arry[0], gui_img_get_transform_degrees(img_strawberry),
         gui_img_get_width(img_cut_arry[0]) / 2,
         gui_img_get_height(img_cut_arry[0]) / 2);
      }

+ Note that a flag can be used to mark the cut status of the fruit to prevent scoring errors as well as to facilitate updating the position of the cut picture.

+ When the cut fruit moves outside the display it will reset the position and initial velocity of the solid and restore the cutting effect.

   .. code-block:: c
      
      gui_img_set_attribute(img_strawberry, "img_strawberry", FRUIT_NINJA_STRAWBERRY_BIN,
                                       img_strawberry->base.x, img_strawberry->base.y);
      fruit_cut_flag[0] = false;
      gui_img_set_location(img_cut_arry[0], 0, SCREEN_HEIGHT + HEIGHT_OFFSET);


