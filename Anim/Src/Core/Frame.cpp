#include "pch.h"
#include "Core/Frame.h"
#include "Core/AssetManager.h"
#include "Utils/Math.h"

using namespace Anim;

Frame::Frame() 
{
   
}

Frame::~Frame()
{
    ClearFrame();           /* clean up any left over spheres */
}

void Frame::CreateSphere(Vec3& position, Vec3& color, float scale)
{
    SphereData sphere;
    Vec3 rotation = {0,0,0};
    sphere.transform = Math::CreateTransformationMatrix(position, rotation, scale);
    sphere.color = color;
    spheres.emplace_back(sphere);
}

void Frame::CreateLight(const Vec3& pos, const Vec3& color, uint32_t slot)
{
    lights[slot] = Light(pos, color);
}

void Frame::ClearFrame()
{
    spheres.clear();
}

std::vector<SphereData>& Frame::GetSpheres()
{
    return spheres;
}

std::array<Light, 3>& Frame::GetLights()
{
    return lights;
}

