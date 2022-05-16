#ifndef IMGUI_RENDERING_H
#define IMGUI_RENDERING_H

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
#include "scene/main/node.h"
#include "editor/editor_paths.h"
#include "imgui_control.h"

#include <vector>
#include <map>
#include <string>

class ImGuiRendering :public Control
{
	GDCLASS(ImGuiRendering, Control);

private:
    RenderingServer *rendering_server;

    ImGuiContext *context;
    ImageTexture font_imgtex;

    int mouse_wheel;
    uint32_t curr_pos;
	uint32_t limit;
    char *charbuff;
    std::vector<char *> strings;
	std::vector<int> pos_strings;

    Vector<Vector<ArrayMesh*>> mesh_dict;
	Vector<Vector<RID>> child_dict;
	Vector<RID> child_dict_parent;

    bool new_frame_rendering;

    void Prepare();
    void Render();
    void Draw();
    unsigned int FixKey(Key kc);
    
public:
    ImGuiRendering(/* args */);
    ~ImGuiRendering();

    void NewFrame();
    void EndFrame();

    void ReceiveInput(const Ref<InputEvent> &p_event);
};



#endif