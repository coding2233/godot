#include "imgui_control.h"
#include "editor/editor_paths.h"

ImGuiControl::ImGuiControl()
{
    set_position(Vector2(0, 0));	
    set_anchors_and_offsets_preset(PRESET_WIDE,PRESET_MODE_KEEP_SIZE,0);
    // set_as_top_level(true);
}

ImGuiControl::~ImGuiControl()
{

}

void ImGuiControl::OnImGui()
{
	// bool showDemo = true;
    // ImGui::ShowDemoWindow(&showDemo);
}