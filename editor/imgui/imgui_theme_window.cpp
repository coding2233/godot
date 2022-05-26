#include "imgui_theme_window.h"

ImGuiThemeWindow::ImGuiThemeWindow(/* args */)
{
}

ImGuiThemeWindow::~ImGuiThemeWindow()
{
}


const char* ImGuiThemeWindow::GetName()
{
    return "Theme";
}

void ImGuiThemeWindow::OnDraw()
{
    // Ref<Theme> theme =get_theme().is_valid()?get_theme():Theme::get_default();
    Ref<Theme> theme =EditorNode::get_singleton()->get_gui_base()->get_theme();
    if(theme.is_valid())
    {
        List<StringName> theme_type_list;
        theme->get_color_type_list(&theme_type_list);
        for(StringName theme_type : theme_type_list)
        {
            ImGui::Text((String()+theme_type).ascii().ptr());
            List<StringName> theme_type_color_list;
            theme->get_color_list(theme_type,&theme_type_color_list);
            for(StringName theme_color_type : theme_type_color_list)
            {
                ImGui::SameLine();
                // ImGui::Text(theme_color_type.ascii().ptr);
                Color theme_color = theme->get_color(theme_color_type,theme_type);
                ImGui::ColorButton((String()+theme_color_type).ascii().ptr(),ImVec4(theme_color.r,theme_color.g,theme_color.b,theme_color.a));
            }
        }
    }

    ImGui::Text("--------------------------------------------------------");

    ImGuiStyle& style = ImGui::GetStyle();
    for (int i = 0; i < ImGuiCol_COUNT; i++)
    {
        const ImVec4& col = style.Colors[i];
        const char* name = ImGui::GetStyleColorName(i);
        ImGui::ColorButton(name,col);
    }
}