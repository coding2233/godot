#ifndef IMGUI_WINDOW_H
#define IMGUI_WINDOW_H

#include "scene/main/window.h"
#include "imgui_control.h"

class ImGuiWindow:public Window
{
	GDCLASS(ImGuiWindow, Window);

private:
    /* data */
public:
    ImGuiWindow(/* args */);
    ~ImGuiWindow();
};




#endif