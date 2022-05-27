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
        if(color_names[i].size()==0)
        {
            color_names[i].resize(200);
        }
        char *input_text=color_names[i].data();
        if(ImGui::InputText("color",input_text,200))
        {
            
        }
        color_names[i]=(std::string)input_text;
        // ImGui::SameLine();
        // ImGui::SetNextItemWidth(100);
        // ImGui::InputText("theme",test_text,200);
    }
}