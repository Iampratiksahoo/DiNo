#pragma once
class DiNoApplication
{
private:
	struct GLFWwindow* _Window;
	const char* _GLSL_VERSION;

	class DiNoMainWindow* _MainWindow;
	
	
public:
	DiNoApplication();
	~DiNoApplication();
	int Run();

private:
	void Style();
};


