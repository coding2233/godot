#include "imgui_editor_node.h"
#include "editor/editor_node.h"

ImGuiEditorNode::ImGuiEditorNode(/* args */)
{
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