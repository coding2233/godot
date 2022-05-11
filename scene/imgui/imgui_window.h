#ifndef IMGUI_WINDOW_H
#define IMGUI_WINDOW_H

#include "scene/main/window.h"

#include "imgui_control.h"

class ImGuiWindow:public Window
{
	GDCLASS(ImGuiWindow, Window);
ImGuiControl* imgui_control;
private:
    /* data */
	void _input_from_window(const Ref<InputEvent> &p_event);

protected:
	void _notification(int p_what);

public:
    ImGuiWindow(/* args */);
    ~ImGuiWindow();

    void _frame_post_draw();
    void _frame_pre_draw();
};




#endif