#include "DiNoNode.h"
#include "imgui.h"

DiNoNode::DiNoNode(
    char p_Name[128],
    char p_Desc[1024 * 16],
    int p_INodeCount,
    int p_ONodeCount)
{
    strcpy_s(_Name, p_Name);
    strcpy_s(_Description, p_Desc);
    _INodeCount = p_INodeCount;
    _ONodeCount = p_ONodeCount;
}

DiNoNode::~DiNoNode()
{

}

void DiNoNode::Render()
{
    // Temporary node implementation
    ImGui::SetNextWindowSize(ImVec2(150, 100));
    ImGui::Begin(_Name, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking);
    ImGui::End();
}
