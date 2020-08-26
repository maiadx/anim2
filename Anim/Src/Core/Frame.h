#pragma once
#include "Utils/Memory.h"
#include "Renderer/RenderObjects/Camera.h"
#include "Renderer/RenderObjects/Light.h"
#include "Core/SphereData.h"
#include "Renderer/RenderObjects/Mesh.h"

/* Frame class: A "snapshot" of everything in the scene being rendered per user-submitted frame. 
                None of the spheres are persistent between frames, so the vector gets cleared after the frame is rendered. 
*/

namespace Anim 
{
    class Frame 
    {
        std::vector<SphereData> m_Spheres;
        std::array<Light, 3> m_Lights = {Light({1000, 1000,1000}, {1,1,1}), Light({0,0,0}, {0,0,0}), Light({0,0,0}, {0,0,0})};
    
    public:
        Frame();
        ~Frame();

        void CreateSphere(glm::vec3& position, glm::vec3& color, float scale);
        void CreateLight(const glm::vec3& pos, const glm::vec3& color, uint32 slot);    
        void ClearFrame();

        std::vector<SphereData>& GetSpheres();
        std::array<Light, 3>& GetLights();
    };
}