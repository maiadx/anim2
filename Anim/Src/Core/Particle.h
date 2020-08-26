#pragma once
#include "Utils/Math.h"

/* data struct used by default compute shader pipeline */
namespace Anim
{
    struct Particle
    {
        glm::vec3 Position;
        glm::vec3 Velocity;
        float Mass;
    };
}