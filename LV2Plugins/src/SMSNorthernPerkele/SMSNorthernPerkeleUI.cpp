
#include "SMSNorthernPerkeleUI.h"
#include <iostream>
#include "res/NorthernPerkele.png.h" // Generated on MAKE
#include "PNGImage.h"

//#include <memory>
#define PI 3.14159

struct Display_deleter
{
    void operator ()(Display* p)
    {
        XCloseDisplay(p);
    }
};

SMSNorthernPerkeleUI::SMSNorthernPerkeleUI(LV2UI_Write_Function write_function, LV2UI_Controller controller, 
                                            LV2UI_Widget* pWidget, const LV2_Feature* const* pFeatures)
    : 
    moWrite_function(write_function),
    moController(controller),
    mpoDisplay(nullptr),
    moWnd(0)//, mbHovering(false)
{
    LV2UI_Resize* pLv2resize = nullptr;
    void* pParentWnd = nullptr;
    for (int i = 0; pFeatures[i]; ++i) {
		if (!strcmp(pFeatures[i]->URI, LV2_UI__parent)) {
			pParentWnd = pFeatures[i]->data;
		} else if (!strcmp(pFeatures[i]->URI, LV2_UI__resize)) {
			pLv2resize = (LV2UI_Resize*)pFeatures[i]->data;
		}
	}

    mpoDisplay = XOpenDisplay(NULL);
    moWnd = XCreateSimpleWindow(mpoDisplay, (Window)pParentWnd, 0, 0, 800, 400, 0, 0, 0xffffffff);

    XMapWindow(mpoDisplay, moWnd);
    XSelectInput(mpoDisplay, moWnd, ExposureMask | KeyPressMask | PointerMotionMask);

    *pWidget = (LV2UI_Widget)moWnd; 

    mpoGUI = std::make_shared<PNGImage>(NorthernPerkele_png, NorthernPerkele_png_len);

   
    if (pLv2resize)
        pLv2resize->ui_resize(pLv2resize->handle, mpoGUI->Width(), mpoGUI->Height());
}


SMSNorthernPerkeleUI::~SMSNorthernPerkeleUI()
{
    XDestroyWindow(mpoDisplay, moWnd);
    XCloseDisplay(mpoDisplay);
}

int SMSNorthernPerkeleUI::idle()
{
    
    while(XPending(mpoDisplay))
    {
        XEvent ev;
        if(XNextEvent(mpoDisplay, &ev) == 0)
        {
            switch (ev.type)
            {
                case Expose:
                {
                    GC gc = XCreateGC(mpoDisplay, moWnd, 0, NULL);
                    mpoGUI->Draw(mpoDisplay, moWnd, gc);

                    //XPutImage(mpoDisplay, moWnd, gc, mpoImage, 0, 0, 0, 0, miImage_width, miImage_height);
                    
                    //XSetForeground(mpoDisplay, gc, BlackPixel(mpoDisplay, miScreen));
                    //XDrawArc(mpoDisplay, moWnd, gc, 100, 100, 50, 50, 0, 360*64);
                    
                    XFlush(mpoDisplay);
                    XFreeGC(mpoDisplay, gc);
                }
                break;
                case MotionNotify:
                {
                   
                  
                    //Initial testing for handling mouse events
                    /*
                    Window root, childWnd;
                    int x, y, rel_x, rel_y;
                    unsigned int maskReturn;
                    XQueryPointer(mpoDisplay, moWnd, &root, &childWnd, &x, &y, &rel_x, &rel_y, &maskReturn);
                    
                    if (rel_x > 100 && rel_x < 150 && rel_y > 100 && rel_y < 150)
                    {
                        mbHovering = true;
                        GC gc = XCreateGC(mpoDisplay, moWnd, 0, NULL);
                        XDrawArc(mpoDisplay, moWnd, gc, 110, 110, 30, 30, 0, 360*64);
                        XFlush(mpoDisplay);
                        XFreeGC(mpoDisplay, gc);
                    }
                    else if (mbHovering)
                    {
                        mbHovering = false;
                        GC gc = XCreateGC(mpoDisplay, moWnd, 0, NULL);
                        XPutImage(mpoDisplay, moWnd, gc, mpoImage, 100, 100, 100, 100, 50, 50);
                        XFlush(mpoDisplay);
                        XFreeGC(mpoDisplay, gc);
                    }*/

                }
                break;
                default:
                    break;
            }
        }
    }

    return 0;
}

int SMSNorthernPerkeleUI::resize(int w, int h)
{   

    return 0;
}


void SMSNorthernPerkeleUI::port_event(uint32_t port_index, uint32_t buffer_size,  uint32_t format, const void *buffer)
{

}
