#include "imgui_editor_window.h"
#include "scene/gui/button.h"

ImGuiEditorWindow::ImGuiEditorWindow(/* args */)
{
	set_title(TTR("ImGui Editor"));
    set_mode(MODE_FULLSCREEN);

    config_path = EditorPaths::get_singleton()->get_config_dir().plus_file("editor_imgui.cfg");

    // set_wrap_controls(true);
	set_visible(false);
	// set_transient(true);
	// set_exclusive(true);
	// set_clamp_to_embedder(true);

	imgui_rendering = memnew(ImGuiRendering);
	add_child(imgui_rendering);
    imgui_editor=memnew(ImGuiEditor);
    imgui_rendering->add_child(imgui_editor);
    // Button *btn = memnew(Button);
    // add_child(btn);

	connect("window_input", callable_mp(this, &ImGuiEditorWindow::_input_from_window));

    RenderingServer::get_singleton()->connect("frame_post_draw",callable_mp(this,&ImGuiEditorWindow::_frame_post_draw));
	RenderingServer::get_singleton()->connect("frame_pre_draw",callable_mp(this,&ImGuiEditorWindow::_frame_pre_draw));
}
		

ImGuiEditorWindow::~ImGuiEditorWindow()
{
}

void ImGuiEditorWindow::_input_from_window(const Ref<InputEvent> &p_event)
{
    if (is_visible())
    {
       imgui_rendering->ReceiveInput(p_event);
    }
}

void ImGuiEditorWindow::_frame_post_draw()
{
    if (is_visible())
    {
		imgui_rendering->NewFrame();
    }
}

void ImGuiEditorWindow::_frame_pre_draw()
{
    if (is_visible())
    {
        imgui_rendering->EndFrame();
    }
}

void ImGuiEditorWindow::_notification(int p_what)
{
    switch (p_what)
    {
    	case NOTIFICATION_WM_SIZE_CHANGED: 
		{
				if (is_visible()) 
				{
					// _update_child_rects();
					// Size2i window_size=get_size();
					// set_metadata("editor_imgui","window_size",Rect2i(get_position(),window_size));
				}
		} 
		break;

		case NOTIFICATION_WM_CLOSE_REQUEST: 
		{
			set_metadata("editor_imgui","window_size",Rect2i(get_position(),get_size()));
			call_deferred(SNAME("hide"));
		} 
		break;
    
    default:
        break;
    }
}

void ImGuiEditorWindow::popup_imgui_editor()
{
	Rect2 saved_size = get_metadata("editor_imgui", "window_size", Rect2(300,200,900,600));
	popup(saved_size);
}


// Metadata

void ImGuiEditorWindow::set_metadata(const String &p_section, const String &p_key, Variant p_data) 
{
	Ref<ConfigFile> cf = memnew(ConfigFile);
	Error err;
	err = cf->load(config_path);
	ERR_FAIL_COND_MSG(err != OK && err != ERR_FILE_NOT_FOUND, "Cannot load editor settings from file '" + config_path + "'.");
	cf->set_value(p_section, p_key, p_data);
	err = cf->save(config_path);
	ERR_FAIL_COND_MSG(err != OK, "Cannot save editor settings to file '" + config_path + "'.");
}

Variant ImGuiEditorWindow::get_metadata(const String &p_section, const String &p_key, Variant p_default) const 
{
	Ref<ConfigFile> cf = memnew(ConfigFile);
	Error err = cf->load(config_path);
	if (err != OK) {
		return p_default;
	}
	return cf->get_value(p_section, p_key, p_default);
}
