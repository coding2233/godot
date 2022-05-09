#include "imgui_window.h"

ImGuiWindow::ImGuiWindow(/* args */)
{
    add_child(memnew(ImGuiControl));
}

ImGuiWindow::~ImGuiWindow()
{
}