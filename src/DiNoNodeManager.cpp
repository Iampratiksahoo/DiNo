#include "DiNoNodeManager.h"
#include "DiNoNode.h"

DiNoNodeManager::DiNoNodeManager()
{

}

DiNoNodeManager::~DiNoNodeManager()
{
	for (DiNoNode* Node : _Nodes)
		delete Node;
}

void DiNoNodeManager::AddNode(DiNoNode* Node)
{
	_Nodes.push_back(Node);
}

void DiNoNodeManager::RemoveNode(DiNoNode* Node)
{
	_Nodes.erase(std::remove(_Nodes.begin(), _Nodes.end(), Node), _Nodes.end());
}

void DiNoNodeManager::RenderNodes()
{
	for (DiNoNode* Node : _Nodes)
		Node->Render();
}
