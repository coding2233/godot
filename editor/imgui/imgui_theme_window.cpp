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

        ImGui::Text("----------------------------");

        List<StringName> font_type_list;
        theme->get_font_type_list(&font_type_list);
        for (StringName font_type:font_type_list)
        {
            ImGui::Text((String()+font_type).ascii().ptr());
            List<StringName> font_list;
            theme->get_font_list(font_type,&font_list);
            for (StringName font_name:font_list)
            {
                ImGui::SameLine();
                ImGui::Text((String()+font_name).ascii().ptr());
            }
        }
    }
}