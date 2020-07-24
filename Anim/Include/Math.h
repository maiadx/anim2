#ifndef ANIM_MATH_HEADER
#define ANIM_MATH_HEADER


typedef struct
{
    float x,y,z;
} Vec3;


void Add(Vec3* result, Vec3* other)
{
    result->x += other->x;
    result->y += other->y;
    result->z += other->z;
}

void Sub(Vec3* result, Vec3* other)
{
    result->x -= other->x;
    result->y -= other->y;
    result->z -= other->z;
}

float Dot(Vec3* vecA, Vec3* vecB)
{
    return (vecA->x * vecB->x) + 
           (vecA->y * vecB->y) +
           (vecA->z * vecB->z);
}

// void Cross(Vec3* result, Vec3* other)
// {

// }




#endif