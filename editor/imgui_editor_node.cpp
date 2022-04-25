#include "imgui_editor_node.h"
#include "editor/editor_node.h"
#include "scene/imgui/imgui_canvas.h"

ImGuiEditorNode::ImGuiEditorNode(/* args */)
{
    ImGuiCanvas *imgui_canvs= memnew(ImGuiCanvas);
    add_child(imgui_canvs);
}

ImGuiEditorNode::~ImGuiEditorNode()
{
}

void ImGuiEditorNode::_notification(int p_what)
{
    auto log = EditorNode::get_log();
    if (log)
    {
        log->add_message("ImGuiEditorNode::_notification p_what ");
    }
}