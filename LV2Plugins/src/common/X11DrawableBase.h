#pragma once

#include "X11/Xlib.h"
#include <vector>
#include <memory>
#include <math.h>
#include <algorithm>

// Abstraction for anything drawable in X11. 
// Supports child items of same type with relative positioning
class X11DrawableBase
{
protected:
    
    // Must override
    virtual void DrawElement(Display* pDisplay, Window oWnd, GC gc, 
                        int x, int y, 
                        unsigned int width, unsigned int height) = 0;

protected:
    // Width and Height of this element.
    unsigned int mWidth;
    unsigned int mHeight;

private:
    std::vector<std::shared_ptr<X11DrawableBase>> moChildren;
    X11DrawableBase* mpoParent;
    int mX;
    int mY;
    
public:
    X11DrawableBase() 
        : mpoParent(nullptr), 
        mWidth(0), mHeight(0), mX(0), mY(0)
    {

    }

    ~X11DrawableBase()
    {
        mpoParent = nullptr;
        moChildren.clear();
    }

    int X() const { return mX; }
    int Y() const { return mY; }
    
    int ScreenX() const { return mpoParent ? mX + mpoParent->ScreenX() : mX; }
    int ScreenY() const { return mpoParent ? mY + mpoParent->ScreenY() : mY; }

    unsigned int Width() const { return mWidth; }
    unsigned int Height() const { return mHeight; }
    
    
    void AddChild(std::shared_ptr<X11DrawableBase> pChild, int x, int y)
    {
        pChild->mX = x;
        pChild->mY = y;
        
        pChild->mpoParent = this;
        moChildren.push_back(pChild);
        
    }

    void Draw(Display* pDisplay, Window oWnd, GC gc)
    {
        DrawElement(pDisplay, oWnd, gc, 0, 0, mWidth, mHeight);
        for(auto pChild : moChildren)
            pChild->Draw(pDisplay, oWnd, gc);
    }

};