#ifndef IMGUI_CONTROL_H
#define IMGUI_CONTROL_H

#include "imgui.h"

#include "servers/rendering_server.h"
#include "core/os/keyboard.h"
#include "core/os/os.h"
#include "core/input/input.h"
#include "core/templates/vector.h"
#include "scene/gui/control.h"
#include "scene/main/window.h"

#include <vector>
#include <map>
#include <string>
class ImGuiControl : public Control 
{
	GDCLASS(ImGuiControl, Control);

    static ImGuiContext *context;
    ImageTexture imgtex; // This can't be static, and thats fine. as texture count is static, it will behave like it
	static uint32_t texture_count;
	static RenderingServer *rendering_server;

    static int mouse_wheel;
    static uint32_t curr_pos;
	static uint32_t limit;
    static char *charbuff;
    static std::vector<char *> strings;
	static std::vector<int> pos_strings;

    Vector<Vector<ArrayMesh*>> mesh_dict;
	Vector<Vector<RID>> child_dict;

    unsigned int FixKey(Key kc);
    void Render();
    void Draw();

protected:
    virtual void input(const Ref<InputEvent> &p_event) override;
public:
    ImGuiControl();
	~ImGuiControl();

	void NewFrame();
    void EndFrame();
};
#endif