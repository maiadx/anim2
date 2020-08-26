#pragma once

namespace Anim
{
/* wrapper for the necessary OpenGL functions */
class GLRenderContext
{
public:
    static void Init();    
    static void ShutDown();

    static void ErrorCheck();
    static void ClearScreen(const glm::vec3& color);
    static void ResizeViewport(float width, float height);
    static void SetBackFaceCulling(bool flag);
    static void SetWireFrameMode(bool flag);

    static void EnableDepthTest();
    static void DisableDepthTest();
    
    static void DrawTriangles(unsigned int numIndices);
    static void DrawLines(unsigned int numIndices);
    static void DrawPoints(unsigned int numIndices);
    static void DrawTrianglesInstanced(unsigned int instanceCount);
    static void DrawPointsInstanced(unsigned int instanceCount);
};


}