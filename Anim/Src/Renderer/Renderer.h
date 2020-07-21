#pragma once 
#include "Utils/Memory.h"
#include "Renderer/Window.h"
#include "Renderer/GLRenderContext.h"
#include "Renderer/RenderObjects/Camera.h"
#include "Renderer/Data/GLComputeShader.h"
#include "Renderer/RenderObjects/Mesh.h"
#include "Core/Frame.h"

namespace Anim 
{
class Renderer 
{
    Window window;
    Frame* currentFrame;
    Mesh* sphereMesh;
    Vec3 bgColor;

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
    static Camera& GetCurrentCamera();
    static Material& GetDefaultMaterial();

    static void SetBackgroundColor(const Vec3& color);
    static void SetWindowSize(float width, float height);

    static void Begin();
    static void Submit(Frame& Frame, float dt);
    static void End();

    static void RenderSpheres(std::vector<SphereData>& spheres);
    static void RunComputeShader(GLComputeShader* cs, float dt);

};
}