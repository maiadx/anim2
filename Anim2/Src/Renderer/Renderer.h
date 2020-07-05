#pragma once
#include "Renderer/Window.h"
#include "Renderer/Data/Plot.h"
#include <glm/glm.hpp>

namespace Anim
{
class Renderer
{
public:    
    static void Init();
    static void InitGui();
    static void Shutdown();
    static Window& GetWindow();
    
    static void BeginFrame();
    static void EndFrame();

    static void DrawSphere(glm::vec3 position, glm::vec3 color);
    static void DrawPoint();
    static void DrawPlot(Plot& plot);
    //void DrawGizmo();
    //void DrawLine();
    //void DrawCircle();

private:
    /* creates a single instance of the Renderer */
    static Renderer& GetInstance()
    {
        static Renderer instance;
        return instance;
    }
    Renderer();
    ~Renderer();

    Window window;
    //Camera camera;
    //Shader* activeShader;

};
}