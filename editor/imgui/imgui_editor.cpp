#include "imgui_editor.h"

ImGuiEditor::ImGuiEditor(/* args */)
{
}

ImGuiEditor::~ImGuiEditor()
{
}


void ImGuiEditor::OnDraw()
{
    // Main window
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;
    bool rootWindowOpen=true;
    if (ImGui::Begin("ImGui Docking root window", &rootWindowOpen, window_flags))
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        // bool showDemo = true;
        // ImGui::ShowDemoWindow(&showDemo);
        static bool test001Open=true;
        ImGui::Begin("test001",&test001Open);
        ImGui::Button("xxxxxxx");
        ImGui::End();

        static bool test002Open=true;
        ImGui::Begin("test002",&test002Open);
        ImGui::Button("xxxxxxx");
        ImGui::End();

        ImGui::Begin("test003");
        ImGui::Button("xxxxxxx");
        ImGui::End();

        ImGui::Begin("test004");
        ImGui::Button("xxxxxxx");
        ImGui::End();
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

