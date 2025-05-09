/**
 \internal
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file gui_obj_tree.h
  * @brief  object tree operations
  * @details tree operations related functions and structures
  * @author howie_wang@realsil.com.cn
  * @date 2025/03/07
  * @version 1.0
  ***************************************************************************************
    * @attention
  * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
  ***************************************************************************************
 \endinternal
  */

/*============================================================================*
 *               Define to prevent recursive inclusion
 *============================================================================*/
#ifndef __GUI_OBJ_TREE_H__
#define __GUI_OBJ_TREE_H__



#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                        Header Files
 *============================================================================*/
#include "guidef.h"
#include "gui_obj_type.h"


/*============================================================================*
 *                         Types
 *============================================================================*/


/*============================================================================*
 *                         Functions
 *============================================================================*/

/**
  * @brief free the widget tree recursively,from the root to the leaves.Preorder traversal.
  * @param obj the root of the widget tree.
  * <b>Example usage</b>
  * \code{.c}
  * static void app_main_task(gui_app_t *app)
  * {
  *    gui_obj_tree_free(&app->screen);
  *
  * }
  *
  * \endcode
  */
void gui_obj_tree_free(void *obj);

/**
  * @brief free the widget tree recursively, without the root. Preorder traversal.
  * @param obj the root of the widget tree.
  */
void gui_obj_child_free(gui_obj_t *object);

/**
  * @brief print the widget tree recursively,from the root to the leaves.Preorder traversal.
  * @param obj the root of the widget tree.
  * <b>Example usage</b>
  * \code{.c}
  * static void app_main_task(gui_app_t *app)
  * {
  *    gui_obj_tree_print(&app->screen);
  *
  * }
  *
  * \endcode
  */
void gui_obj_tree_print(gui_obj_t *obj);

/**
  * @brief get count of one type on tree.
  * @param obj the root of the widget tree.
  * @param type widget type.
  * @param count count result.
  */
void gui_obj_tree_count_by_type(gui_obj_t *obj, T_OBJ_TYPE type, int *count);

/**
  * @brief show or hide the widget.
  * @param obj the root of the widget tree.
  * @param enable true for show, false for hide.
  */
void gui_obj_tree_show(gui_obj_t *obj, bool enable);

/**
  * @brief show the root of this_widget tree.
  * @param obj the root of the widget tree.
  * @return gui_obj_t*.
  */
gui_obj_t *gui_obj_tree_get_root(gui_obj_t *obj);

/**
  * @brief get child type.
  * @param obj the root of the widget tree.
  * @param child_type type of obj widget.
  * @return gui_obj_t*.
  */
gui_obj_t *gui_obj_get_child_handle(gui_obj_t *obj, T_OBJ_TYPE child_type);

/**
 * @brief get widget in tree by name.
 *
 * @param obj tree.
 * @param name widget name.
 * @param output widget.
 */
void gui_obj_tree_get_widget_by_name(gui_obj_t *obj, const char *name, gui_obj_t **output);

/**
 * @brief get widget in tree by type.
 *
 * @param root tree.
 * @param type widget type.
 * @param output widget.
 * @return void.
 */
void gui_obj_tree_get_widget_by_type(gui_obj_t *root, T_OBJ_TYPE type, gui_obj_t **output);

/**
 * @brief print name by bfs order.
 *
 * @param root tree.
 */
void gui_obj_tree_print_bfs(gui_obj_t *root);

/**
 * @brief tree print mermaid.
 *
 * @param obj Pointer to the GUI object root.
 */
void gui_obj_tree_print_mmd(gui_obj_t *obj);

/**
 * @brief Retrieve a widget from the GUI object tree by type and index.
 *
 * This function searches the GUI object tree starting from the root and retrieves
 * a widget of the specified type and index.
 *
 * @param root Pointer to the root of the GUI object tree.
 * @param type The type of the object to find.
 * @param output Pointer to where the found object should be stored.
 * @param index The index of the object to retrieve.
 */
void gui_obj_tree_get_widget_by_type_and_index(gui_obj_t *root, T_OBJ_TYPE type, gui_obj_t **output,
                                               int index);

/**
 * @brief Get an array of widget objects from the GUI object tree by type.
 *
 * This function searches the GUI object tree starting from the root and
 * retrieves an array of widget objects of the specified type.
 *
 * @param root Pointer to the root of the GUI object tree.
 * @param type The type of the object to find.
 * @param output_array Pointer to an array where the found objects should be stored.
 * @param length Pointer to an integer where the length of the array should be stored.
 *
 * @return 0 if successful, -1 if not successful.
 */
int gui_obj_tree_get_widget_array_by_type(gui_obj_t *root,
                                          T_OBJ_TYPE type,
                                          gui_obj_t ***output_array,
                                          int *length);

#ifdef __cplusplus
}
#endif

#endif
