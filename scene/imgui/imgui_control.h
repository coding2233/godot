#ifndef IMGUI_CONTROL_H
#define IMGUI_CONTROL_H

#include "imgui.h"
#include "imgui_internal.h"

#include "servers/rendering_server.h"
#include "core/os/keyboard.h"
#include "core/os/os.h"
#include "core/input/input.h"
#include "core/templates/vector.h"
#include "scene/gui/control.h"
#include "scene/main/window.h"
#include "scene/resources/mesh.h"
#include "core/object/gdvirtual.gen.inc"
#include "scene/main/viewport.h"

#include <vector>
#include <map>
#include <string>


class ImGuiControl : public Control 
{
	GDCLASS(ImGuiControl, Control);

protected:
    
public:
    ImGuiControl();
	~ImGuiControl();

    virtual void OnImGui();
};
#endif