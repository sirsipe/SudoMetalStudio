#include "PNGImage.h"
#include <iostream>

PNGImage::PNGImage()
    : X11DrawableBase(),
    mpoImage(nullptr),
    mpImage_data(nullptr)
{

}

PNGImage::PNGImage(unsigned char* pPngData, unsigned int iLen) 
    : PNGImage()
{
    LoadPNG(pPngData, iLen);
}

PNGImage::~PNGImage()
{
    FreeResources();
}

void PNGImage::LoadPNG(unsigned char* pPngData, unsigned int iLen)
{
    FreeResources();

    FILE* fp = fmemopen(pPngData, iLen, "r");
    load_png_image(fp, &mWidth, &mHeight, &mpImage_data);
    fclose(fp);
}

void PNGImage::FreeResources()
{
    if (mpImage_data)
    {
        XFree(mpImage_data);
        mpImage_data = nullptr;
    }
    if (mpoImage)
    {
        XFree(mpoImage);
        mpoImage = nullptr;
    }

    mWidth = 0;
    mHeight = 0;
 
}

void PNGImage::DrawElement(Display* pDisplay, Window oWnd, GC gc, 
                        int x, int y, 
                        unsigned int width, unsigned int height)
{
    if (!mpoImage && mpImage_data)
    {
        int iScreen = DefaultScreen(pDisplay);
        Visual* pVisual = DefaultVisual(pDisplay, iScreen);
        int iDepth = DefaultDepth(pDisplay, iScreen);
        mpoImage = XCreateImage(pDisplay, pVisual, iDepth, ZPixmap, 0, (char *)mpImage_data, mWidth, mHeight, 32, 0);
    }

    if (mpoImage)
    {
        int sX = X() >= 0 ? 0 : -X();
        int sY = Y() >= 0 ? 0 : -Y();
        int tX = ScreenX();
        int tY = ScreenY();
        int w = X() < 0 ? Width() + X() : Width();
        int h = Y() < 0 ? Height() + Y() : Height();


        XPutImage(pDisplay, oWnd, gc, mpoImage, sX, sY, tX, tY, w, h);

    }
}

void PNGImage::load_png_image(FILE* fp, unsigned int* pWidth, unsigned int* pHeight, png_byte** ppcImage_data) 
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