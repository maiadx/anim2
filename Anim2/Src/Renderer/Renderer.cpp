#include "pch.h"
#include "Renderer/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>
#include <iostream>

using namespace Anim;

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Init()
{
    GetInstance();
    //     /* loads the OpenGL driver */
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))                                             /* loads OpenGL functions + extensions */
    {
	    std::cerr << "Unable to initialize OpenGL(Glad)!" << std::endl;  
    } else {
        std::cout << "Initialized OpenGL context." << std::endl;
    }
    InitGui();

    BeginFrame();
    EndFrame();

}

void Renderer::Shutdown()
{
    EndFrame();
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    GetInstance().window.Destroy();
}

void Renderer::InitGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

    ImGui_ImplGlfw_InitForOpenGL(GetInstance().window.GetWindowContext(), true);
    ImGui_ImplOpenGL3_Init("#version 430");                                                            /* using opengl shader lang (GLSL) v4.5, which supports most modern hardware */
    
    /* --- style elements --- */
    ImGui::GetStyle().WindowRounding = 0.0f;
    ImGui::GetStyle().WindowBorderSize = 0.0f;

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg]               = ImVec4(0.12f, 0.12f, 0.12f, 0.96f);                     /* theme configuration: overrides default values for some gui components */
    colors[ImGuiCol_Border]                 = ImVec4(0.87f, 0.22f, 0.22f, 0.50f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.28f, 0.61f, 0.44f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.23f, 0.42f, 0.60f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.15f, 0.48f, 0.61f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.15f, 0.48f, 0.61f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.68f, 0.68f, 0.68f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.80f, 0.80f, 0.80f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.80f, 0.80f, 0.80f, 0.67f);



}

Window& Renderer::GetWindow()
{
    return GetInstance().window;
}


void Renderer::BeginFrame()
{
    glClearColor(0.24f, 0.24f, 0.24f, 1.0f);                                /* rgba clear color */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                     /* clear frame color and depth buffers for next series of draw calls */

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags win_flags = 0;
    win_flags |= ImGuiWindowFlags_NoTitleBar;
    //ImGui::ShowDemoWindow();          /* imgui examples window */
  
    ImGui::Begin("gui 1",(bool *)0,  win_flags);
}

void Renderer::EndFrame()
{
    ImGui::End();
    ImGui::Render();            
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    GetInstance().window.Update();
}

void DrawSphere(glm::vec3 position, glm::vec3 color)
{

}

void DrawPoint(glm::vec3 position, glm::vec3 color)
{

}

void Renderer::DrawPlot(Plot& plot)
{
    float average = 0.0f;
    for (int n = 0; n < plot.data.size(); n++)
        average += plot.data[n];
    average /= (float)plot.data.size();
    char overlay[32];
    sprintf(overlay, "avg %f", average);
    ImGui::PlotLines(plot.name.c_str(), &plot.data[0], plot.data.size(), 0, (const char *)__null, -10, 10, ImVec2(0, 50));


}



// /* initializes GLFW context, loads OpenGL */
// void InitWindow()
// {
// 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);										// Version of GLSL (4.5)
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);	
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                      /* ensures intel compatibility */
// 	glfwInit();
    
//     if (!glfwInit())	
// 	    std::cerr << "GLFW failed to initialize!" << std::endl;

//     s_width = 600;
//     s_height = 600;
// 	s_window = glfwCreateWindow(s_width, s_height, "Newt", NULL, NULL);	                 /* Create a window */

// 	if (!s_window)
// 		std::cerr << "Window creation failed!" << std::endl;


// 	glfwMakeContextCurrent(s_window);
// 	glfwSwapInterval(1);				                                                                /* enables V-sync - if supported */													
// 	glfwWindowHint(GLFW_SAMPLES, 2);                                                                    /* anti-aliasing 2x */
//     glfwSetErrorCallback(WindowErrorCallback);                                                          /* print errors using our own callback function above */
// 	glfwSetFramebufferSizeCallback(s_window, WindowResizeCallback);             


// }

// /* now that we've created a window, we need to init the gui library (ImGui) */
// void Init()
// {
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO();
//     io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

//     ImGui_ImplGlfw_InitForOpenGL(s_window, true);
//     ImGui_ImplOpenGL3_Init("#version 430");                                                            /* using opengl shader lang (GLSL) v4.5, which supports most modern hardware */
    
//     /* --- style elements --- */
//     ImGui::GetStyle().WindowRounding = 0.0f;
//     ImGui::GetStyle().WindowBorderSize = 0.0f;

//     ImVec4* colors = ImGui::GetStyle().Colors;
//     colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.96f);                                    /* theme configuration: overrides default values for some gui components */
//     colors[ImGuiCol_Border]                 = ImVec4(0.87f, 0.22f, 0.22f, 0.50f);
//     colors[ImGuiCol_FrameBg]                = ImVec4(0.28f, 0.61f, 0.44f, 0.54f);
//     colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.23f, 0.42f, 0.60f, 1.00f);
//     colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.15f, 0.48f, 0.61f, 1.00f);
//     colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.15f, 0.48f, 0.61f, 1.00f);
// }



// void ShutDown()
// {
// 	ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();
// }