#ifndef IMGUI_STYLE_WINDOW
#define IMGUI_STYLE_WINDOW

#include "imgui_dock_window.h"
#include "scene/resources/theme.h"
#include "editor/editor_node.h"

#include <string>
#include <map>


class ImGuiStyleWindow:public ImGuiDockWindow
{
private:
    /* data */
    std::string color_names[ImGuiCol_COUNT];
    std::string theme_names[ImGuiCol_COUNT];

public:
    ImGuiStyleWindow(/* args */);
    ~ImGuiStyleWindow();

     const char* GetName() override;
    void OnDraw() override;
};




#endif