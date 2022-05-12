#include "imgui_window.h"
#include "scene/gui/button.h"

ImGuiWindow::ImGuiWindow(/* args */)
{
	set_title(TTR("ImGui Editor"));
    set_mode(MODE_FULLSCREEN);

    config_path = EditorPaths::get_singleton()->get_config_dir().plus_file("editor_imgui.cfg");

    // set_wrap_controls(true);
	set_visible(false);
	// set_transient(true);
	// set_exclusive(true);
	// set_clamp_to_embedder(true);
    imgui_control=memnew(ImGuiControl);
    add_child(imgui_control);
    // Button *btn = memnew(Button);
    // add_child(btn);

	connect("window_input", callable_mp(this, &ImGuiWindow::_input_from_window));

    RenderingServer::get_singleton()->connect("frame_post_draw",callable_mp(this,&ImGuiWindow::_frame_post_draw));
	RenderingServer::get_singleton()->connect("frame_pre_draw",callable_mp(this,&ImGuiWindow::_frame_pre_draw));
}
		

ImGuiWindow::~ImGuiWindow()
{
}

void ImGuiWindow::_input_from_window(const Ref<InputEvent> &p_event)
{
    if (is_visible())
    {
       imgui_control->_window_input(p_event);
    }
}

void ImGuiWindow::_frame_post_draw()
{
    if (is_visible())
    {
        imgui_control->NewFrame();
    }
}

void ImGuiWindow::_frame_pre_draw()
{
     if (is_visible())
    {
        imgui_control->EndFrame();
    }
}

void ImGuiWindow::_notification(int p_what)
{
    switch (p_what)
    {
    	case NOTIFICATION_WM_SIZE_CHANGED: 
		{
				if (is_visible()) 
				{
					// _update_child_rects();
					set_metadata("editor_imgui","window_size",Rect2i(get_position(),get_size()));
				}
		} 
		break;

		case NOTIFICATION_WM_CLOSE_REQUEST: 
		{
			call_deferred(SNAME("hide"));
		} 
		break;
    
    default:
        break;
    }
}

void ImGuiWindow::popup_imgui_editor()
{
	Rect2 saved_size = get_metadata("editor_imgui", "window_size", Rect2(300,200,900,600));
	popup(saved_size);
}


// Metadata

void ImGuiWindow::set_metadata(const String &p_section, const String &p_key, Variant p_data) 
{
	Ref<ConfigFile> cf = memnew(ConfigFile);
	Error err;
	err = cf->load(config_path);
	ERR_FAIL_COND_MSG(err != OK && err != ERR_FILE_NOT_FOUND, "Cannot load editor settings from file '" + config_path + "'.");
	cf->set_value(p_section, p_key, p_data);
	err = cf->save(config_path);
	ERR_FAIL_COND_MSG(err != OK, "Cannot save editor settings to file '" + config_path + "'.");
}

Variant ImGuiWindow::get_metadata(const String &p_section, const String &p_key, Variant p_default) const 
{
	Ref<ConfigFile> cf = memnew(ConfigFile);
	Error err = cf->load(config_path);
	if (err != OK) {
		return p_default;
	}
	return cf->get_value(p_section, p_key, p_default);
}
