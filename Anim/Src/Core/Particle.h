#pragma once
#include "Utils/Math.h"

/* data struct used by default compute shader pipeline */
namespace Anim
{
    struct Particle
    {
        Vec3 position;
        Vec3 velocity;
        float mass;
    };
}