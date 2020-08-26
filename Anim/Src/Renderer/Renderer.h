#pragma once 
#include "Utils/Memory.h"
#include "Renderer/Window.h"
#include "Renderer/GLRenderContext.h"
#include "Renderer/RenderObjects/Camera.h"
#include "Renderer/Data/GLComputeShader.h"
#include "Renderer/RenderObjects/Mesh.h"
#include "Core/Frame.h"

/* Renderer  : sends commands to renderAPIContext and manages state of context 
    Begin()  : clears color/depth buffer and awaits submission of scene data (Frame.h) 
    Submit() : user submits the scene, along with frame-time which is used to measure fps
    End()    : rendering to active framebuffer is complete, swaps buffers to window 
*/

namespace Anim 
{
class Renderer 
{
    Window m_Window;
    Frame* m_CurrentFrame;
    Camera* m_Camera;
    glm::vec3 m_BgColor;

    Renderer(int sWidth, int sHeight, const std::string& wTitle);

public:
    static Renderer& Instance()
    {	
        static Renderer s_instance(1920, 1080, " ");
        return s_instance;
    }
    Renderer(const Renderer& renderer) = delete;
    /* All this ^ does is ensure that we only ever have one instance of our renderer (singleton class)*/

    static Window& GetWindow();
    static Camera* GetCamera();
    static Material& GetDefaultMaterial();

    static void SetBackgroundColor(const glm::vec3& color);
    static void SetWindowSize(float width, float height);

    static void Begin();
    static void Submit(Frame& Frame, float dt);
    static void End();

    static void RenderSpheres(std::vector<SphereData>& spheres);
    static void RunComputeShader(GLComputeShader& cs, float dt);

};
}