#pragma once
class DiNoMainWindow
{
private:
	class DiNoNodeManager* _NodeManager;

	int _ParentWidth, _ParentHeight;
	int _ParentPosX, _ParentPosY;
	int _MainWindowFlags;

	//Popup window parameters
	bool _TriggerNewNodePopup;

	void MenuItems();

public:
	DiNoMainWindow();
	~DiNoMainWindow();
	void Render(struct GLFWwindow* _Window);

private:
	void TriggerNewNodePopupWindow(bool* p_open);
	void CreateNewNode();
};