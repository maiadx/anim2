#pragma once
#include "Utils/Math.h"

/* data struct used by default compute shader pipeline */
namespace Anim
{
    struct Particle
    {
        Vec3 Position;
        Vec3 Velocity;
        float Mass;
    };
}