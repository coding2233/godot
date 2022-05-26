#ifndef IMGUI_DOCK_WINDOW
#define IMGUI_DOCK_WINDOW

#include "scene/imgui/imgui.h"

class ImGuiDockWindow
{
private:
    /* data */
public:
    ImGuiDockWindow(/* args */);
    ~ImGuiDockWindow();
    bool show;
    virtual const char* GetName()=0;
    virtual void OnDraw()=0;
};



#endif