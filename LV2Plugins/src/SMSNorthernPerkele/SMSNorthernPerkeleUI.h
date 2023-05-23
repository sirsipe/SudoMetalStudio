#pragma once

#include "../common/LV2Entry.h"
#include "X11/Xlib.h"
#include <png.h>

class SMSNorthernPerkeleUI
{
public:
    SMSNorthernPerkeleUI(LV2UI_Write_Function write_function, LV2UI_Controller controller,  
                        LV2UI_Widget* pWidget, const LV2_Feature* const* pFeatures);
    ~SMSNorthernPerkeleUI();

    void port_event(uint32_t port_index, uint32_t buffer_size,  uint32_t format, const void* pBuffer);
   
    int idle();
    int resize(int w, int h);

private:
    void load_png_image(FILE* fp, int* pWidth, int* pHeight, png_byte** ppcImage_data);
 
private:
    int miImage_width;
    int miImage_height;
    XImage* mpoImage;
    int miScreen;
    //bool mbHovering;
    Display* mpoDisplay;
    Window moWnd;

    LV2UI_Write_Function moWrite_function;
    LV2UI_Controller moController;
};

EXPORT_PLUGIN_UI_DESCRIPTOR_X11(SMSNorthernPerkeleUI, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/SMSNorthernPerkele#ui")
