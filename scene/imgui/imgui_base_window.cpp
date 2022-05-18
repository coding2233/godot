#include "imgui_base_window.h"

ImGuiBaseWindow::ImGuiBaseWindow(/* args */)
{
	connect("window_input", callable_mp(this, &ImGuiBaseWindow::_input_from_window));
}

ImGuiBaseWindow::~ImGuiBaseWindow()
{
}


void ImGuiBaseWindow::_input_from_window(const Ref<InputEvent> &p_event)
{
    OnInputFromWindow(p_event);
}


void ImGuiBaseWindow::OnInputFromWindow(const Ref<InputEvent> &p_event)
{
   
}