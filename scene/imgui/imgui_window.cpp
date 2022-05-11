#include "imgui_window.h"
#include "scene/gui/button.h"

ImGuiWindow::ImGuiWindow(/* args */)
{
	set_title(TTR("ImGui Editor"));
    set_mode(MODE_FULLSCREEN);

    // set_wrap_controls(true);
	set_visible(false);
	// set_transient(true);
	// set_exclusive(true);
	// set_clamp_to_embedder(true);
    imgui_control=memnew(ImGuiControl);
    add_child(imgui_control);
    Button *btn = memnew(Button);
    btn->set_text("Buttonnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn");
    add_child(btn);

	connect("window_input", callable_mp(this, &ImGuiWindow::_input_from_window));

    RenderingServer::get_singleton()->connect("frame_post_draw",callable_mp(this,&ImGuiWindow::_frame_post_draw));
	RenderingServer::get_singleton()->connect("frame_pre_draw",callable_mp(this,&ImGuiWindow::_frame_pre_draw));
}
		

ImGuiWindow::~ImGuiWindow()
{
}

void ImGuiWindow::_input_from_window(const Ref<InputEvent> &p_event)
{
    imgui_control->_window_input(p_event);
}

void ImGuiWindow::_frame_post_draw()
{
    imgui_control->NewFrame();
}

void ImGuiWindow::_frame_pre_draw()
{
    imgui_control->EndFrame();
}

void ImGuiWindow::_notification(int p_what)
{
    switch (p_what)
    {
    case NOTIFICATION_WM_SIZE_CHANGED: {
			if (is_visible()) {
				// _update_child_rects();
			}
		} break;

		case NOTIFICATION_WM_CLOSE_REQUEST: {
			// _cancel_pressed();
	        call_deferred(SNAME("hide"));
		} break;
    
    default:
        break;
    }
}