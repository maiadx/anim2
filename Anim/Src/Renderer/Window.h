#pragma once
#include <string>
#include <iostream>
#include <time.h>
#include "Core/Log.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvents.h"
#include "Events/WindowEvents.h"
// #define GLFW_INCLUDE_VULKAN
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Anim 
{
class Window : public EventListener
{
	Window(const Window& other) {}

	std::string m_Title;
	int m_Height;
	int m_Width;
	GLFWwindow* m_WindowContext;

	KeyEventDispatcher m_KeyDispatcher;
	MouseEventDispatcher m_MouseDispatcher;
	WindowEventDispatcher m_WindowDispatcher;

public:
	Window();
	Window(int width, int height, std::string title);

	virtual ~Window();

	void OnAttach();
	void OnEvent(const Event& e);

	GLFWwindow* GetWindow();
	void Init();
	void Update();
	void Destroy();
	void SetVisible(bool flag);

	static KeyEventDispatcher& GetKeyDispatcher();
	static MouseEventDispatcher& GetMouseDispatcher();
	static WindowEventDispatcher& GetWinEventDispatcher();

	bool IsRunning();
	int GetHeight();
	int GetWidth();
};
}
