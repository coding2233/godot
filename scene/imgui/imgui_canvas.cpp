#include "imgui_canvas.h"

ImGuiCanvas::ImGuiCanvas(/* args */)
{
}

ImGuiCanvas::~ImGuiCanvas()
{
}


void ImGuiCanvas::_notification(int p_what)
{
	switch (p_what)
	{
	case NOTIFICATION_DRAW:
        bool showWindow;
        showWindow=true;
		ImGui::Begin("ImGuiCanvas",&showWindow);
        ImGui::Button("Hello button");
        ImGui::End();
		break;
	
	default:
		break;
	}
}