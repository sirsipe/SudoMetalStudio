
#include "SMSNorthernPerkeleUI.h"
#include <iostream>
#include <string.h>

SMSNorthernPerkeleUI::SMSNorthernPerkeleUI(LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget *widget, const LV2_Feature *const *features)
    : mWrite_function(write_function),
    mController(controller)
{
    LV2UI_Resize* lv2resize = nullptr;
    void* parentWnd = nullptr;
    for (int i = 0; features[i]; ++i) {
		if (!strcmp(features[i]->URI, LV2_UI__parent)) {
			parentWnd = features[i]->data;
		} else if (!strcmp(features[i]->URI, LV2_UI__resize)) {
			lv2resize = (LV2UI_Resize*)features[i]->data;
		}
	}


    mDisplay = XOpenDisplay(NULL);
    mWnd = XCreateSimpleWindow(mDisplay, (Window)parentWnd, 0, 0, 800, 600, 0, 0, 0xffffffff);

    XMapWindow(mDisplay, mWnd);
    XSelectInput(mDisplay, mWnd, ExposureMask | KeyPressMask);

    *widget = (LV2UI_Widget)mWnd; 

}

int SMSNorthernPerkeleUI::idle()
{
    
    while(XPending(mDisplay))
    {
        XEvent ev;
        if(XNextEvent(mDisplay, &ev) == 0)
        {
            if (ev.type == Expose) 
            {
                GC gc = XCreateGC(mDisplay, mWnd, 0, NULL);
                const char *text = "TODO: Skulls, fire & blood!";
                XFontStruct* font_info = XLoadQueryFont(mDisplay, "fixed");
                XSetFont(mDisplay, gc, font_info->fid);

                // Handle expose event (drawing on the window)
                XDrawString(mDisplay, mWnd, gc, 10, 20, text, strlen(text));
                XFlush(mDisplay);

                XFreeGC(mDisplay, gc);
                XFreeFont(mDisplay, font_info);
            }
        }
    }

    return 0;
}

int SMSNorthernPerkeleUI::resize(int w, int h)
{   
    return 0;
}

SMSNorthernPerkeleUI::~SMSNorthernPerkeleUI()
{
    
}

void SMSNorthernPerkeleUI::port_event(uint32_t port_index, uint32_t buffer_size,  uint32_t format, const void *buffer)
{

}
    