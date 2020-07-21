#include "pch.h"
#include "Renderer/Renderer.h"

using namespace Anim;

Renderer::Renderer(int sWidth, int sHeight, const std::string& wTitle) : window(sWidth, sHeight, wTitle)
{
    bgColor = {0,0,0};
    GLRenderContext::Init();
    sphereMesh = new Mesh("/usr/share/anim2/Models/volleyball.obj");
}

Window& Renderer::GetWindow()
{
    return Instance().window;
}

Camera& Renderer::GetCurrentCamera()
{
    return Instance().currentFrame->GetCamera();
}

void Renderer::SetBackgroundColor(const Vec3& color)
{
    Instance().bgColor = color;
}

void Renderer::Begin()
{
    GLRenderContext::ClearScreen(Instance().bgColor);
}

void Renderer::Submit(Frame& Frame, float dt)
{
    Instance().currentFrame = &Frame;
    Instance().currentFrame->GetCamera().Update(dt);
    RenderSpheres(Frame.GetSpheres());\
}

void Renderer::End()
{
    Instance().window.Update();
}

void Renderer::RenderSpheres(std::vector<SphereData>& spheres)
{
    Frame* frame = Instance().currentFrame;
    Camera camera = frame->GetCamera();
    
    Mesh& sphereMesh = *Instance().sphereMesh;
    sphereMesh.GetMaterial()->Bind();
    
    VertexArray* vao = sphereMesh.GetVao();

    sphereMesh.GetMaterial()->LoadViewMatrix(camera.GetViewMatrix());
    sphereMesh.GetMaterial()->LoadProjectionMatrix(camera.GetProjectionMatrix());
    sphereMesh.GetMaterial()->LoadLights(frame->GetLights());

    for(uint32 i = 0; i < spheres.size(); i++)
    {
        sphereMesh.GetMaterial()->LoadModelMatrix(spheres[i].transform);
        sphereMesh.GetMaterial()->LoadColor(spheres[i].color);
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
void Renderer::RunComputeShader(GLComputeShader* cs, float dt)
{
    Frame* currentFrame = Instance().currentFrame;

    float forceRadii = 5;
    cs->BindCS();
    cs->LoadFloat(glGetUniformLocation(cs->GetCSID(), "timestep"), dt);
    cs->LoadFloat(glGetUniformLocation(cs->GetCSID(), "forceRadii"), forceRadii);
    
    cs->Compute();

    cs->SetProjMatrix(currentFrame->GetCamera().GetProjectionMatrix());
    cs->SetViewMatrix(currentFrame->GetCamera().GetViewMatrix());
    
    GLRenderContext::DrawPointsInstanced(cs->GetNumObjects());
    
    glBindVertexArray(0);
    cs->Unbind();
}




