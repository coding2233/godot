#ifndef IMGUI_CANVAS_H
#define IMGUI_CANVAS_H

#include "native_imgui.h"

class ImGuiCanvas: public ImGuiControl
{
	GDCLASS(ImGuiCanvas, ImGuiControl);
private:
    /* data */
public:
    ImGuiCanvas();
    ~ImGuiCanvas();

    void _notification(int p_what);

};


#endif