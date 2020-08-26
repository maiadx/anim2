#pragma once
#include "Renderer/RenderObjects/Material.h"

namespace Anim
{
    struct SphereData
    {
        glm::vec3 Color; 
        glm::mat4 Transform;     /* spheres's position + size in 3D space */
    };
}