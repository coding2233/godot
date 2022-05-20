#ifndef IMGUI_EDITOR_WINDOW_H
#define IMGUI_EDITOR_WINDOW_H

#include "scene/main/window.h"
#include "core/io/config_file.h"
#include "editor/editor_paths.h"
#include "scene/imgui/imgui_base_window.h"

#include "scene/imgui/imgui_control.h"
#include "imgui_editor.h"
#include "scene/imgui/imgui_rendering.h"


class ImGuiEditorWindow:public ImGuiBaseWindow
{
	GDCLASS(ImGuiEditorWindow, ImGuiBaseWindow);
private:
    String config_path;
    CharString ini_file_path;
    ImGuiRendering* imgui_rendering;
    ImGuiEditor* imgui_editor;

    void set_metadata(const String &p_section, const String &p_key, Variant p_data);
    Variant get_metadata(const String &p_section, const String &p_key, Variant p_default) const;

protected:
	void _notification(int p_what);
    void OnInputFromWindow(const Ref<InputEvent> &p_event) override;

public:
    ImGuiEditorWindow(/* args */);
    ~ImGuiEditorWindow();

    void _frame_post_draw();
    void _frame_pre_draw();

    void popup_imgui_editor();
};




#endif