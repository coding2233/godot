#include "imgui_style_window.h"

ImGuiStyleWindow::ImGuiStyleWindow(/* args */)
{
}

ImGuiStyleWindow::~ImGuiStyleWindow()
{
}

const char* ImGuiStyleWindow::GetName()
{
    return "Style";
}


void ImGuiStyleWindow::OnDraw()
{
    ImGuiStyle& style = ImGui::GetStyle();
    for (int i = 0; i < ImGuiCol_COUNT; i++)
    {
        const ImVec4& col = style.Colors[i];
        const char* name = ImGui::GetStyleColorName(i);
        ImGui::Text(name);
        ImGui::SameLine();
        ImGui::ColorButton(name,col);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        std::string &color_name = color_names[i];
        std::string &theme_name = theme_names[i];
        if (color_name.size()==0)
        {
            color_name.resize(100);
            theme_name.resize(100);
        }
        ImGui::InputText(vformat("color##stype_input_color_%s",name).ascii().get_data(),color_name.data(),100);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::InputText(vformat("theme##stype_input_theme_%s",name).ascii().get_data(),theme_name.data(),100);
        ImGui::SameLine();
        if(ImGui::Button("Set Style"))
        {
            ImGuiStyle& style = ImGui::GetStyle();
            Ref<Theme> editor_theme =EditorNode::get_singleton()->get_gui_base()->get_theme();
            Color color = editor_theme->get_color(color_name.data(),theme_name.data());
            ImVec4 imVec4(color.r,color.g,color.b,color.a);
            style.Colors[i]=imVec4;
        }
    }
}