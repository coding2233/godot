#ifndef IMGUI_THEME_WINDOW
#define IMGUI_THEME_WINDOW

#include "imgui_dock_window.h"
#include "scene/resources/theme.h"
#include "editor/editor_node.h"

class ImGuiThemeWindow:public ImGuiDockWindow
{
private:
    /* data */
public:
    ImGuiThemeWindow(/* args */);
    ~ImGuiThemeWindow();

    const char* GetName() override;
    void OnDraw() override;
};



#endif