#include "imgui_editor.h"

ImGuiEditor::ImGuiEditor(/* args */)
{
    show_game_view = true;

    game_viewport = memnew(SubViewport);
	game_viewport->set_disable_input(true);
    game_viewport->set_update_mode(SubViewport::UPDATE_ALWAYS);
    
    add_child(game_viewport);
}

ImGuiEditor::~ImGuiEditor()
{
}


void ImGuiEditor::OnImGui()
{
   
    

    // Main window
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(main_viewport->WorkPos);
    ImGui::SetNextWindowSize(main_viewport->WorkSize);
    ImGui::SetNextWindowViewport(main_viewport->ID);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;
    bool rootWindowOpen=true;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (ImGui::Begin("ImGui Docking root window", &rootWindowOpen, window_flags))
    {
        ImGui::PopStyleVar();

        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

        if (show_game_view)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
           
            //Set attach from show_game_view or other event...
            Node *scene_root = SceneTreeDock::get_singleton()->get_editor_data()->get_edited_scene_root();
            if(scene_root)
            {
                Camera3D *cam = scene_root->get_viewport()->get_camera_3d();
                if (cam)
                {
                    RS::get_singleton()->viewport_attach_camera(game_viewport->get_viewport_rid(), cam->get_camera());
                }
            }
           
            if(ImGui::Begin("Game",&show_game_view))
            {
                ImGui::PopStyleVar();

                ImVec2 vcp=ImVec2(ImGui::GetWindowPos().x,ImGui::GetWindowPos().y+ImGui::GetFrameHeight());
                Size2 game_view_size = Size2(ImGui::GetWindowSize().x,ImGui::GetWindowSize().y-ImGui::GetFrameHeight());
                ImVec2 vcs = ImVec2(game_view_size.x+vcp.x,game_view_size.y+vcp.y);
                game_viewport->set_size(game_view_size);
                ImGui::GetWindowDrawList()->AddImage(game_viewport->get_texture().ptr(),vcp,vcs);
            }
            ImGui::End();
        }

    }

     //Menu bar
    AppMainMenuBar();
    ImGui::End();
}



void ImGuiEditor::AppMainMenuBar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            // ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            // ImGui::MenuItem("Padding", NULL, &opt_padding);
            ImGui::Separator();

            // if (ImGui::MenuItem("Flag: NoSplit",                "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
            // if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            // if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
            // if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            // if (ImGui::MenuItem("Flag: PassthruCentralNode",    "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();

            // if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
            //     *p_open = false;
            ImGui::EndMenu();
        }

         if (ImGui::BeginMenu("Window"))
        {
            // ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Game", NULL, &show_game_view);
            ImGui::EndMenu();
        }
        // HelpMarker(
        //     "When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
        //     "- Drag from window title bar or their tab to dock/undock." "\n"
        //     "- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
        //     "- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
        //     "- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)" "\n"
        //     "This demo app has nothing to do with enabling docking!" "\n\n"
        //     "This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window." "\n\n"
        //     "Read comments in ShowExampleAppDockSpace() for more details.");

        ImGui::EndMenuBar();
    }

}


void ImGuiEditor::_notification(int p_what) 
{
	switch (p_what) 
    {
		case NOTIFICATION_RESIZED: 
			break;
        case NOTIFICATION_PROCESS:
            break;
		case NOTIFICATION_ENTER_TREE:
		case NOTIFICATION_VISIBILITY_CHANGED: {
            if (is_visible_in_tree()) 
            {
                game_viewport->set_update_mode(SubViewport::UPDATE_ALWAYS);
            } 
            else 
            {
                game_viewport->set_update_mode(SubViewport::UPDATE_DISABLED);
            }
            game_viewport->set_handle_input_locally(false);
        break;
	}
}