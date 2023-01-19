/*
#include "SMSNorthernPerkeleUI.h"

SMSNorthernPerkeleUI::SMSNorthernPerkeleUI(LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget *widget)
    : mWrite_function(write_function),
    mController(controller)
{
    Display * display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);
    Window window = XCreateSimpleWindow(display, root, 0, 0, 800, 600, 0, 0, 0xffffffff);

    *widget = window; 

    XMapWindow(display, window);

}*/