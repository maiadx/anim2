#pragma once
#include <string>
#include <iostream>
#include <time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Anim
{
class Window 
{
public:
	Window();
	Window(int width, int height, std::string title);
	~Window();

	void Init();
	void Update();
	void PollEvents();
	void Destroy();
	void SetVisible(bool flag);

    void SetSize(int width, int height);
    void OnWindowResize(int width, int height);
    bool IsRunning();

	GLFWwindow* GetWindowContext();
    int GetHeight();
	int GetWidth();

private:
	GLFWwindow* window;
	GLFWimage winIcon[1];                                       /* window icon for taskbar */

	int width, height;
	std::string title;
};
}