#pragma once

#include "../common/LV2Entry.h"
#include "X11/Xlib.h"

class SMSNorthernPerkeleUI
{
public:
    SMSNorthernPerkeleUI(LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget *widget, const LV2_Feature *const *features);
    ~SMSNorthernPerkeleUI();
    void port_event(uint32_t port_index, uint32_t buffer_size,  uint32_t format, const void *buffer);
   
    int idle();
    int resize(int w, int h);

private:
    Display* mDisplay;
    Window mRoot;
    Window mWnd;

    LV2UI_Write_Function mWrite_function;
    LV2UI_Controller mController;
};

EXPORT_PLUGIN_UI_DESCRIPTOR_X11(SMSNorthernPerkeleUI, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/SMSNorthernPerkele#ui")
