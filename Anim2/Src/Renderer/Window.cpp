#include "pch.h"
#include "Renderer/Window.h"

/*
	Rendering context: manages the window, initialization of rendering environment. 
*/
using namespace Anim;

static Window* windowInstance;

/* /// GLFW Callbacks /// */
void WindowResizeHandler(GLFWwindow* window, int width, int height)
{
	windowInstance->OnWindowResize(width, height);
}	

static void ErrorCallback(int code, const char* message)
{
	std::string error(message);
	std::cerr << "ERROR: GLFW window error code: " << code << std::endl;
	std::cerr << error << std::endl;
}
/* /// End Callbacks /// */

Window::Window()
{
	this->width = 550;
	this->height = 600;
	this->title = " ";
    Init();
}

Window::Window(int width, int height, const std::string title) : width(width), height(height), title(title)
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
	glfwDestroyWindow(window);
}

void Window::Init()
{
    windowInstance = this;

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);										/* Version of GLSL shader language (4.5) */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);						/* ensures intel iGPU compatibilty */
	glfwInit();

	if (!glfwInit())	
	{
		std::cerr << "GLFW failed to initialize!" << std::endl;
	}

	this->window = glfwCreateWindow(width, height, this->title.c_str(), NULL, NULL);	

	if (!window)
	{
		std::cerr << "Window creation failed!" << std::endl;
	}
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);																	/* enables v-sync */
	glfwWindowHint(GLFW_SAMPLES, 2);														/* enables 2x anti-aliasing */

	glfwSetErrorCallback(ErrorCallback);
	glfwSetFramebufferSizeCallback(window, WindowResizeHandler);
}

void Window::Update()
{
	glfwSwapBuffers(window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::SetSize(int width, int height)
{
    // add some stuff here to force GLFW window to new size and make sure stored width + height values are updated in Newt as well.
}

/* todo: whenever user resizes window -> make sure aspect ratio for camera is also updated */
void Window::OnWindowResize(int width, int height)
{
    this->width = width;
    this->height = height;
	// renderer call for camera update?
}

bool Window::IsRunning()
{
	return !glfwWindowShouldClose(this->window);
}

/* Get the GLFW window context */
GLFWwindow* Window::GetWindowContext()
{
	return this->window;
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}
