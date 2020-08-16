#pragma once
#include "Renderer/RenderObjects/Material.h"

namespace Anim
{
    struct SphereData
    {
        Vec3 Color; 
        Mat4 Transform;     /* spheres's position + size in 3D space */
    };
}