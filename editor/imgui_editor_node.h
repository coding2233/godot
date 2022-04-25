#ifndef IMGUI_EDITOR_NODE
#define IMGUI_EDITOR_NODE

#include "scene/main/node.h"
#include "editor/editor_log.h"

class ImGuiEditorNode:public Node
{
    GDCLASS(ImGuiEditorNode, Node);
private:
    /* data */
public:
    ImGuiEditorNode(/* args */);
    ~ImGuiEditorNode();

    void _notification(int p_what);
};




#endif