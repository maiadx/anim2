#include "pch.h"
#include "Renderer/Renderer.h"

using namespace Anim;

static Mesh* s_sphereMesh;

Renderer::Renderer(int sWidth, int sHeight, const std::string& wTitle) : m_Window(sWidth, sHeight, wTitle)
{
    GLRenderContext::Init();
    m_BgColor = {0,0,0};
    m_Camera = new Camera({0,0,0},{0,0,0});
    s_sphereMesh = new Mesh("/usr/share/anim2/Models/volleyball.obj");
}

Window& Renderer::GetWindow()
{
    return Instance().m_Window;
}

Camera* Renderer::GetCamera()
{
    return Instance().m_Camera;
}

void Renderer::SetBackgroundColor(const glm::vec3& color)
{
    Instance().m_BgColor = color;
}

void Renderer::Begin()
{
    GLRenderContext::ClearScreen(Instance().m_BgColor);
}

void Renderer::Submit(Frame& frame, float dt)
{
    Instance().m_CurrentFrame = &frame;
    Instance().m_Camera->Update(dt);
    RenderSpheres(frame.GetSpheres());
}

void Renderer::End()
{
    Instance().m_Window.Update();
}

void Renderer::RenderSpheres(std::vector<SphereData>& spheres)
{
    Frame frame = *Instance().m_CurrentFrame;
    Camera camera = *Instance().m_Camera;
    
    Mesh& sphereMesh = *s_sphereMesh;
    sphereMesh.GetMaterial()->Bind();
    
    VertexArray* vao = sphereMesh.GetVao();

    sphereMesh.GetMaterial()->LoadViewMatrix(camera.GetViewMatrix());
    sphereMesh.GetMaterial()->LoadProjectionMatrix(camera.GetProjectionMatrix());
    sphereMesh.GetMaterial()->LoadLights(frame.GetLights());

    for(uint32 i = 0; i < spheres.size(); i++)
    {
        sphereMesh.GetMaterial()->LoadModelMatrix(spheres[i].Transform);
        sphereMesh.GetMaterial()->LoadColor(spheres[i].Color);
        vao->Bind();
        vao->EnableAttribute(0);
        vao->EnableAttribute(1);

        GLRenderContext::DrawTriangles(sphereMesh.GetNumIndices());

        vao->DisableAttribute(1);
        vao->DisableAttribute(0);
        vao->Unbind();
    }
    sphereMesh.GetMaterial()->Unbind();
}

/* Compute Shaders are WIP */
void Renderer::RunComputeShader(GLComputeShader& cs, float dt)
{
    Frame* currentFrame = Instance().m_CurrentFrame;

    float forceRadii = 5;
    cs.BindCS();
    cs.LoadFloat(glGetUniformLocation(cs.GetCSID(), "timestep"), dt);
    cs.LoadFloat(glGetUniformLocation(cs.GetCSID(), "forceRadii"), forceRadii);
    
    cs.Compute();

    cs.SetProjMatrix(Instance().m_Camera->GetProjectionMatrix());
    cs.SetViewMatrix(Instance().m_Camera->GetViewMatrix());
    
    GLRenderContext::DrawPointsInstanced(cs.GetNumObjects());
    
    glBindVertexArray(0);
    cs.Unbind();
}




