#ifndef IMGUI_BASE_WINDOW_H
#define IMGUI_BASE_WINDOW_H

#include "scene/main/window.h"

class ImGuiBaseWindow:public Window
{
	GDCLASS(ImGuiBaseWindow, Window);

private:
	void _input_from_window(const Ref<InputEvent> &p_event);
protected:
    virtual void OnInputFromWindow(const Ref<InputEvent> &p_event);
public:
    ImGuiBaseWindow(/* args */);
    ~ImGuiBaseWindow();
};



#endif