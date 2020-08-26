#include "pch.h"
#include "Renderer/GLRenderContext.h"
#include "Renderer/Window.h"
using namespace Anim;

void GLRenderContext::Init()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Log::Error("Unable to load GLAD!");
		return;
	}
    Log::Info("Initializing OpenGL Context.");
    EnableDepthTest();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_MULTISAMPLE);    
    
}

void GLRenderContext::ShutDown()
{
    // should probably do some cleaning up here 
}

void GLRenderContext::ErrorCheck()
{
    while(GLenum error = glGetError())
    {
        std::string errorMsg = "OpenGL Error! Code: ";
        errorMsg += std::to_string(error);
        Log::Crit(errorMsg.c_str());
    }
    while(glGetError() != GL_NO_ERROR){}
}


void GLRenderContext::ClearScreen(const glm::vec3& color)
{
    glClearColor(color.x, color.y, color.z, 1.0f);    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderContext::ResizeViewport(float width, float height)
{
    glViewport(0, 0, width, height);
}

void GLRenderContext::SetBackFaceCulling(bool flag)
{
    if(flag)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    } else {
        glDisable(GL_CULL_FACE);
    }
}

void GLRenderContext::SetWireFrameMode(bool flag)
{
    if(flag)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void GLRenderContext::EnableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void GLRenderContext::DisableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
}

void GLRenderContext::DrawTriangles(unsigned int numIndices)
{
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}


void GLRenderContext::DrawLines(unsigned int numIndices)
{
    glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, 0);
}

void GLRenderContext::DrawPoints(unsigned int numIndices)
{
    glDrawElements(GL_POINTS, numIndices, GL_UNSIGNED_INT, 0);
}

void GLRenderContext::DrawTrianglesInstanced(unsigned int instanceCount)
{
    glDrawArraysInstanced(GL_TRIANGLES, 0, 1, instanceCount);
}

void GLRenderContext::DrawPointsInstanced(unsigned int instanceCount)
{
    glDrawArraysInstanced(GL_POINTS, 0, 1, instanceCount);
}
