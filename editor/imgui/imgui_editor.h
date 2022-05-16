#ifndef IMGUI_EDITOR_H
#define IMGUI_EDITOR_H

#include "scene/gui/subviewport_container.h"
#include "scene/imgui/imgui_control.h"
#include "scene/3d/camera_3d.h"
#include "editor/scene_tree_dock.h"

class ImGuiEditor:public ImGuiControl
{
private:
    // SubViewportContainer* viewport_container;
    SubViewport* game_viewport;
    
    bool show_game_view;

    /* data */
    void AppMainMenuBar();

protected:
    void _notification(int p_what);

public:
    ImGuiEditor(/* args */);
    ~ImGuiEditor();

    void OnImGui() override;
};



#endif