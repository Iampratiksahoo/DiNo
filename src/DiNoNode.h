#pragma once
class DiNoNode
{
private:
	char _Name[128];
	char _Description[1024 * 16];
	int _INodeCount;
	int _ONodeCount;
	

public:
	DiNoNode(
		char p_Name[128], 
		char p_Desc[1024 * 16],
		int p_INodeCount, 
		int p_ONodeCount);
	~DiNoNode();

	void Render();
};

