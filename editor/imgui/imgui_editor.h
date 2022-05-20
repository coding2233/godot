#ifndef IMGUI_EDITOR_H
#define IMGUI_EDITOR_H

#include "scene/gui/subviewport_container.h"
#include "scene/imgui/imgui_control.h"
#include "scene/3d/camera_3d.h"
#include "editor/scene_tree_dock.h"
#include "editor/plugins/node_3d_editor_plugin.h"
#include "editor/debugger/editor_debugger_node.h"
#include "editor/editor_paths.h"

class ImGuiEditor:public ImGuiControl
{
private:
    String config_path;

    // SubViewportContainer* viewport_container;
    SubViewport* game_viewport;
    SubViewport* scene_viewport;
    
    bool show_game_view;
    bool show_scene_view;

    /* data */
    void AppMainMenuBar();

    void set_metadata(const String &p_section, const String &p_key, Variant p_data);
    Variant get_metadata(const String &p_section, const String &p_key, Variant p_default) const;
protected:
    void _notification(int p_what);

public:
    ImGuiEditor(/* args */);
    ~ImGuiEditor();

    void OnImGui() override;
};



#endif