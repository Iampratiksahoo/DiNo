#pragma once
#include <vector>

class DiNoNodeManager
{
private:
	std::vector<class DiNoNode*> _Nodes;

public:
	DiNoNodeManager();
	~DiNoNodeManager();

	void RenderNodes();
	void AddNode(class DiNoNode* Node);
	void RemoveNode(class DiNoNode* Node);

};

