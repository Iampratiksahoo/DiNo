#include "DiNoMainWindow.h"
#include "DiNoNodeManager.h"
#include "DiNoNode.h"

#include "DiNoDEFINATIONS.h"

#include <string>
#include "imgui.h"
#include "GLFW/glfw3.h"

DiNoMainWindow::DiNoMainWindow() :
    _ParentWidth(0),
    _ParentHeight(0),
    _ParentPosX(0),
    _ParentPosY(0)
{
    _MainWindowFlags =  ImGuiWindowFlags_None           | 
                        ImGuiWindowFlags_NoTitleBar     | 
                        ImGuiWindowFlags_NoResize       | 
                        ImGuiWindowFlags_NoTitleBar     | 
                        ImGuiWindowFlags_NoScrollbar    | 
                        ImGuiWindowFlags_NoCollapse     | 
                        ImGuiWindowFlags_NoBackground   |
                        ImGuiWindowFlags_NoBringToFrontOnFocus;

    _NodeManager = new DiNoNodeManager();
    _TriggerNewNodePopup = false;
    //Testing the node class
}

DiNoMainWindow::~DiNoMainWindow()
{
    delete _NodeManager;
}


void DiNoMainWindow::Render(GLFWwindow* _Window)
{
    /*
    * Get the size and position of the Parent window
    * This size and position can be set each frame for the main window
    */
    glfwGetWindowSize(_Window, &_ParentWidth, &_ParentHeight);
    glfwGetWindowPos(_Window, &_ParentPosX, &_ParentPosY);

    // Set the fetched parameters for the current frame 
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(_ParentWidth), static_cast<float>(_ParentHeight)));
    ImGui::SetNextWindowPos(ImVec2(static_cast<float>(_ParentPosX), static_cast<float>(_ParentPosY)));

    if(ImGui::Begin(MAIN_WINDOW_TITLE, NULL, _MainWindowFlags))
    {
        if (ImGui::BeginPopupContextWindow())
        {
            MenuItems();
            ImGui::EndPopup();
        }

        //ImGui::ShowDemoWindow();
        if(_TriggerNewNodePopup) TriggerNewNodePopupWindow(&_TriggerNewNodePopup);

        // Render everything inside the application here
        _NodeManager->RenderNodes();
    }
    ImGui::End();
}


void DiNoMainWindow::MenuItems()
{
    if (ImGui::MenuItem("New Node"))
    {
        CreateNewNode();
    }
}


void DiNoMainWindow::TriggerNewNodePopupWindow(bool* p_open)
{
#pragma region Style
    // Cache the default style to reassign after popup creation
    ImGuiStyle CacheStyle = ImGui::GetStyle();

    // Get the current style reference
    ImGuiStyle& style = ImGui::GetStyle();

    // Make style changes
    style.WindowRounding = 10.f;
    style.FrameRounding = 4.f;
    style.Colors[ImGuiCol_TitleBg] = ImVec4(POPUP_WINDOW_TITLE_BG);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(POPUP_WINDOW_TITLE_BG_ACTIVE);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(POPUP_WINDOW_TITLE_BG_COLLAPSED);
#pragma endregion


#pragma region SizeAndPositionParameters
    // Relative height ratio of the popup window
    int ratio = 2;
    // Setting the size of the popup to be half the size of the actual window
    ImVec2 PopupSize = ImVec2(static_cast<float>(_ParentWidth / ratio), static_cast<float>(_ParentHeight / ratio));

    // Get the Center of the parent window
    ImVec2 ParentCenter = ImVec2(static_cast<float>(_ParentPosX + _ParentWidth / 2), static_cast<float>(_ParentPosY + _ParentHeight / 2));

    // Adjust the ParentCenter data so that the center of the child and parent are equal
    ImVec2 ChildDelta = ImVec2(static_cast<float>(_ParentWidth / (ratio * 2)), static_cast<float>(_ParentHeight / (ratio * 2)));

    // Subtracting the ChildDelta from the ParentCenter to get the pos of the popup for which the Popup center == ParentCenter
    ImVec2 PopupPos = ImVec2(ParentCenter.x - ChildDelta.x, ParentCenter.y - ChildDelta.y);
#pragma endregion

#pragma region WindowParameters

    int PopupFlags = 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoDocking | 
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoScrollbar | 
        ImGuiWindowFlags_NoScrollWithMouse;

#pragma endregion



    ImGui::SetNextWindowSize(PopupSize);
    ImGui::SetNextWindowPos(PopupPos);

    // Create the window
    ImGui::Begin("##NEW_NODE_POPUP", p_open, PopupFlags);

#pragma region InputFields

    static char u_NodeName[128] = "";
    ImGui::Text("Node Name");
    ImGui::SetNextItemWidth(PopupSize.x - 15);
    ImGui::InputTextWithHint("##NEW_NODE_NAME", "Enter node name", u_NodeName, IM_ARRAYSIZE(u_NodeName));

    static char u_NodeDesc[1024 * 16] = "";
    ImGui::Text("Node Description");
    ImGui::SetNextItemWidth(PopupSize.x - 15);
    ImGui::InputTextMultiline("##NEW_NODE_DESCRIPTION", u_NodeDesc, IM_ARRAYSIZE(u_NodeDesc));

    static int u_INodeCount = 1;
    ImGui::Text("Input Nodes");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("##INPUT_NODE_COUNT", &u_INodeCount);

    ImGui::SameLine(300);
    static int u_ONodeCount = 1;
    ImGui::Text("Output Node");
    ImGui::SameLine(400);
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("##OUTPUT_NODE_COUNT", &u_ONodeCount);

    // Perform checks for the Input and Output Node ranges
    if (u_INodeCount < MINIMUM_INPUT_NODES) u_INodeCount = MINIMUM_INPUT_NODES;
    if (u_ONodeCount < MINIMUM_OUTPUT_NODES) u_ONodeCount = MINIMUM_OUTPUT_NODES;

#pragma endregion

    

    style.FrameRounding = 2.f;
    if (ImGui::Button("Create Node"))
    {
        /*
        * using strcmp to check if the NodeName is empty?
        * strcmp() returns 0 if the two strings are equal, and returns non-zero if the strings are unequal
        */
        if (strcmp(u_NodeName, ""))
        {
            // Creating and adding a new node with the name that user provides
            DiNoNode* NewNode = new DiNoNode(u_NodeName, u_NodeDesc, u_INodeCount, u_ONodeCount);
               
            // Add the node to the list of nodes to be rendered
            _NodeManager->AddNode(NewNode);

            //Debug
            printf("Node Name: %s\nNode Description: %s\nInput Nodes: %d\nOutput Nodes: %d\n\n", u_NodeName, u_NodeDesc, u_INodeCount, u_ONodeCount);

            /*
            * Reset the variables data
            * comment this line if you want the data from previous nodes to persist while creating a new node
            */
            strcpy_s(u_NodeName, "");
            strcat_s(u_NodeDesc, "");
            u_INodeCount = 1;
            u_ONodeCount = 1;

            // Close the popup
            _TriggerNewNodePopup = false;
        }
        else
        {
            
        }
    }

    ImGui::End();

    // Reset style to the Application Style
    style = CacheStyle;
}

void DiNoMainWindow::CreateNewNode()
{
    // Trigger opens the popup window to get the details of the new node.
    _TriggerNewNodePopup = true;
}
