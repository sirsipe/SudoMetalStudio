
#include "SMSNorthernPerkeleUI.h"
#include <iostream>
#include "res/NorthernPerkele.png.h" // Generated on MAKE

#define PI 3.14159

SMSNorthernPerkeleUI::SMSNorthernPerkeleUI(LV2UI_Write_Function write_function, LV2UI_Controller controller, 
                                            LV2UI_Widget* pWidget, const LV2_Feature* const* pFeatures)
    : 
    moWrite_function(write_function),
    moController(controller),
    mpoDisplay(nullptr),
    miImage_width(0),
    miImage_height(0),
    miScreen(0),
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

    miScreen = DefaultScreen(mpoDisplay);
    Visual* pVisual = DefaultVisual(mpoDisplay, miScreen);
    int iDepth = DefaultDepth(mpoDisplay, miScreen);
    png_byte* pImage_data;
   
    FILE* fp = fmemopen(NorthernPerkele_png, NorthernPerkele_png_len, "r");
    load_png_image(fp, &miImage_width, &miImage_height, &pImage_data);
    fclose(fp);

    mpoImage = XCreateImage(mpoDisplay, pVisual, iDepth, ZPixmap, 0, (char *)pImage_data, miImage_width, miImage_height, 32, 0);

    if (pLv2resize)
        pLv2resize->ui_resize(pLv2resize->handle, miImage_width, miImage_height);
}


SMSNorthernPerkeleUI::~SMSNorthernPerkeleUI()
{
    XFree(mpoImage->data);
    XFree(mpoImage);
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
                    XPutImage(mpoDisplay, moWnd, gc, mpoImage, 0, 0, 0, 0, miImage_width, miImage_height);
                    
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
    miImage_width = w;
    miImage_height = h;
    return 0;
}


void SMSNorthernPerkeleUI::port_event(uint32_t port_index, uint32_t buffer_size,  uint32_t format, const void *buffer)
{

}
    

void SMSNorthernPerkeleUI::load_png_image(FILE* fp, int* pWidth, int* pHeight, png_byte** ppcImage_data) 
{
    if (!fp) 
    {
        std::cout <<  "File handle not given." << std::endl;
        return;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) 
    {
        std::cout << "Error initializing libpng." << std::endl;
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) 
    {
        std::cout <<  "Error initializing PNG info." << std::endl;
        png_destroy_read_struct(&png, NULL, NULL);
        return;
    }

    if (setjmp(png_jmpbuf(png))) 
    {
        std::cout <<  "Error during PNG file read." << std::endl;
        png_destroy_read_struct(&png, &info, NULL);
        return;
    }

    png_init_io(png, fp);
    png_read_info(png, info);

    *pWidth = png_get_image_width(png, info);
    *pHeight = png_get_image_height(png, info);
    
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * (*pHeight));
    for (int y = 0; y < *pHeight; y++)
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));

    png_read_image(png, row_pointers);

    *ppcImage_data = (png_byte *)malloc((*pWidth) * (*pHeight) * 4);
    for (int y = 0; y < *pHeight; y++) {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < *pWidth; x++) {
            png_bytep px = &(row[x * 4]);
            (*ppcImage_data)[(y * (*pWidth) + x) * 4 + 0] = px[0];
            (*ppcImage_data)[(y * (*pWidth) + x) * 4 + 1] = px[1];
            (*ppcImage_data)[(y * (*pWidth) + x) * 4 + 2] = px[2];
            (*ppcImage_data)[(y * (*pWidth) + x) * 4 + 3] = px[3];
        }
    }

    for (int y = 0; y < *pHeight; y++)
        free(row_pointers[y]);
    free(row_pointers);

    png_destroy_read_struct(&png, &info, NULL);
}

