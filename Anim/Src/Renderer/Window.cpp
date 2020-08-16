#include "pch.h"
#include "Renderer/Window.h"
#include <imgui.h>

using namespace Anim;

/* These get passed to glfw callbacks to capture IO events */
static KeyEventDispatcher* s_keyDispatcher;
static MouseEventDispatcher* s_mouseDispatcher;
static WindowEventDispatcher* s_winDispatcher;

/* /// GLFW Callbacks /// */

static void KeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(!ImGui::GetIO().WantCaptureKeyboard)										/* check that gui isn't using keyboard input */
	{
		if(action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			s_keyDispatcher->Notify(KeyPressEvent(key, 0));						/* todo: key repeat counting */
		} else {
			s_keyDispatcher->Notify(KeyReleaseEvent(key));
		}
	}
}

static void MousePositionHandler(GLFWwindow* window, double xPos, double yPos)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	s_mouseDispatcher->Notify(MouseMoveEvent(xPos - width/2, yPos - height/2));
	//LOG_CRIT("Mouse is moving!");
}

static void MouseButtonHandler(GLFWwindow* window, int button, int action, int mods)
{
	if(!ImGui::GetIO().WantCaptureMouse)
	{
		if(action == GLFW_PRESS)
		{
			switch(button)
			{
			case GLFW_MOUSE_BUTTON_1:
				s_mouseDispatcher->Notify(MousePressEvent(MouseCode::M_BUTTON_LEFT));
				break;
			case GLFW_MOUSE_BUTTON_3:
				s_mouseDispatcher->Notify(MousePressEvent(MouseCode::M_BUTTON_MID));
				break;
			case GLFW_MOUSE_BUTTON_2:
				s_mouseDispatcher->Notify(MousePressEvent(MouseCode::M_BUTTON_RIGHT));
				break;
			default:								/* discard all other mouse codes */
				break;
			}
		} else {					
			switch(button)
			{
			case GLFW_MOUSE_BUTTON_LEFT:
					s_mouseDispatcher->Notify(MouseReleaseEvent(MouseCode::M_BUTTON_LEFT));
					break;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				s_mouseDispatcher->Notify(MouseReleaseEvent(MouseCode::M_BUTTON_MID));
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				s_mouseDispatcher->Notify(MouseReleaseEvent(MouseCode::M_BUTTON_RIGHT));
				break;
			default:								
				break;
			}
		}
	}
}

static void MouseScrollHandler(GLFWwindow* window, double x_offset, double y_offset)
{
	if(!ImGui::GetIO().WantCaptureMouse)
		s_mouseDispatcher->Notify(MouseScrollEvent(x_offset, y_offset));
}

void WindowResizeHandler(GLFWwindow* window, int width, int height)
{
	s_winDispatcher->Notify(WindowResizeEvent(width, height));
}	

static void ErrorCallback(int code, const char* message)
{
	std::string error(message);
	//LOG_ERR("GLFW window error code: " + code);
	Log::Crit(error.c_str());
}
/* /// End Callbacks /// */


Window::Window()
{
	this->m_Width = 1920;
	this->m_Height = 1080;
	this->m_Title = " ";
	Init();
}

Window::Window(int width, int height, const std::string title) : m_Width(width), m_Height(height), m_Title(title)
{
	Init();
}

Window::~Window()
{
	Destroy();
}
/* closes current glfw window */
void Window::Destroy()
{
	// ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();
	glfwDestroyWindow(m_WindowContext);
}



void Window::Init()
{
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);										// Version of GLSL (4.5)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwInit();

	if (!glfwInit())	
	{
		Log::Error("GLFW failed to initialize!");
	}

	this->m_WindowContext = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);	// third argument makes window full screen if:

	if (!m_WindowContext)
	{
		Log::Error("Window creation failed!");
	}
	glfwMakeContextCurrent(m_WindowContext);

	glfwSwapInterval(1);																	/* limits fps to native refresh rate */
	glfwWindowHint(GLFW_SAMPLES, 8);				

	s_keyDispatcher = &this->m_KeyDispatcher;
	s_mouseDispatcher = &this->m_MouseDispatcher;				
	s_winDispatcher = &this->m_WindowDispatcher;

	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(m_WindowContext, KeyboardHandler);
	glfwSetMouseButtonCallback(m_WindowContext, MouseButtonHandler);
	glfwSetCursorPosCallback(m_WindowContext, MousePositionHandler);
	glfwSetScrollCallback(m_WindowContext, MouseScrollHandler);
	glfwSetFramebufferSizeCallback(m_WindowContext, WindowResizeHandler);

}

void Window::OnAttach()
{
	
}

void Window::OnEvent(const Event& e)
{
	// if(e.getType() == EventType::WINDOW_RESIZE)
	// {
	// 	const WindowEvent& win_event = ((const WindowEvent&)e);
	// }
}

void Window::Update()
{
	glfwSwapBuffers(m_WindowContext);
	glfwPollEvents();
}

KeyEventDispatcher& Window::GetKeyDispatcher()
{
	return *s_keyDispatcher;
}

MouseEventDispatcher& Window::GetMouseDispatcher()
{
	return *s_mouseDispatcher;
}

WindowEventDispatcher& Window::GetWinEventDispatcher()
{
	return *s_winDispatcher;
}

bool Window::IsRunning()
{
	return !glfwWindowShouldClose(m_WindowContext);
}

int Window::GetWidth()
{
	return m_Width;
}

int Window::GetHeight()
{
	return m_Height;
}

GLFWwindow* Window::GetWindow()
{
	return m_WindowContext;
}

