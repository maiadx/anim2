#pragma once
#include "Renderer/RenderObjects/Material.h"

namespace Anim
{
    struct SphereData
    {
        Vec3 color; 
        Mat4 transform;     /* spheres's position + size in 3D space */
    };
}