#include "root_image_hongkong/ui_resource.h"
#include <gui_magic_img.h>

void page_tb_clock(void *parent)
{
    gui_magic_img_create_from_mem(parent, "page0", CLOCKN_BIN, 0, 0, 0, 0);
}