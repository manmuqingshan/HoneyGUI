#include "js_user.h"
#include "js_extern_io.h"

extern void gui_extern_event_sh_handler(gui_msg_js_t *js_msg);
extern void gui_extern_event_timer_handler(gui_msg_js_t *js_msg);
extern void gui_extern_event_wifi_handler(gui_msg_js_t *js_msg);
extern void gui_extern_event_key_handler(gui_msg_js_t *js_msg);

void gui_extern_event_js_handler(gui_msg_t *msg)
{
    gui_msg_js_t *js_msg = (gui_msg_js_t *) & (msg->cb);

    switch (js_msg->extern_event_type)
    {
    case EXTERN_EVENT_SMARTHOME:
        {
            gui_extern_event_sh_handler(js_msg);
            break;
        }
    case EXTERN_EVENT_TIMER:
        {
            gui_extern_event_timer_handler(js_msg);
            break;
        }
    case EXTERN_EVENT_WIFI:
        {
            gui_extern_event_wifi_handler(js_msg);
            break;
        }
    case EXTERN_EVENT_KEY:
        {
            gui_extern_event_key_handler(js_msg);
            break;
        }
    // case EXTERN_EVENT_XXX:


    default:
        {


            break;
        }
    }

}

