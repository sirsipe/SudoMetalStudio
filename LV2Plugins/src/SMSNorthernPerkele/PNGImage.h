#pragma once
#include "../common/X11DrawableBase.h"
#include <png.h>

class PNGImage : public X11DrawableBase
{
public:
    PNGImage();
    ~PNGImage();
    PNGImage(unsigned char* pngData, unsigned int iLen);

    void LoadPNG(unsigned char* pngData, unsigned int iLen);

private:
    void FreeResources();
    void load_png_image(FILE* fp, unsigned int* pWidth, unsigned int* pHeight, png_byte** ppcImage_data);
    
protected:
    virtual void DrawElement(Display* pDisplay, Window oWnd, GC gc, 
                        int x, int y, 
                        unsigned int width, unsigned int height) override;
private:
    png_byte* mpImage_data;
    XImage* mpoImage;

    
};