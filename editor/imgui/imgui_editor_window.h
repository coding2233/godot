#ifndef IMGUI_WINDOW_H
#define IMGUI_WINDOW_H

#include "scene/main/window.h"
#include "core/io/config_file.h"
#include "editor/editor_paths.h"

#include "scene/imgui/imgui_control.h"
#include "imgui_editor.h"
#include "scene/imgui/imgui_rendering.h"


class ImGuiEditorWindow:public Window
{
	GDCLASS(ImGuiEditorWindow, Window);
private:
    String config_path;
    ImGuiRendering* imgui_rendering;
    ImGuiEditor* imgui_editor;

    /* data */
	void _input_from_window(const Ref<InputEvent> &p_event);

    void set_metadata(const String &p_section, const String &p_key, Variant p_data);
    Variant get_metadata(const String &p_section, const String &p_key, Variant p_default) const;

protected:
	void _notification(int p_what);

public:
    ImGuiEditorWindow(/* args */);
    ~ImGuiEditorWindow();

    void _frame_post_draw();
    void _frame_pre_draw();

    void popup_imgui_editor();
};




#endif