#ifndef IMGUI_EDITOR_H
#define IMGUI_EDITOR_H

#include "scene/imgui/imgui_control.h"

class ImGuiEditor:public ImGuiControl
{
private:
    /* data */
public:
    ImGuiEditor(/* args */);
    ~ImGuiEditor();

protected:
    void OnDraw() override;
};



#endif