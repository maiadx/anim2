#pragma once
#include "Utils/Memory.h"
#include "Renderer/RenderObjects/Camera.h"
#include "Renderer/RenderObjects/Light.h"
#include "Core/SphereData.h"

/* Frame class: A "snapshot" of everything in the scene being rendered per frame. 
                None of the spheres are persistent between frames, so at the end of each frame they get deleted. 
*/

namespace Anim 
{
class Frame 
{
    Camera camera;
    std::array<Light, 3> lights = {Light({0,0,0}, {1,0,0}), Light({0,0,0}, {0,0,0}), Light({0,0,0}, {0,0,0})};
    std::vector<SphereData> spheres;

public:
    Frame();
    ~Frame();

    void CreateSphere(Vec3& position, Vec3& color, float scale);
    void CreateLight(const Vec3& pos, const Vec3& color, uint32_t slot);    
    void ClearFrame();
    //void ClearLights();

    std::vector<SphereData>& GetSpheres();
    std::array<Light, 3>& GetLights();
    Camera& GetCamera();
};
}