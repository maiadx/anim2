#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* The point of aliasing glm types is to allow for the possibility of swapping math libraries in the future 
    for platform-specific optimized ones, but it also looks nicer. :)
*/

namespace Math 
{
inline float Max(float a, float b)
{
    if(a > b)
        return a;
    return b;
}

inline float Min(float a, float b)
{
    if(a < b)
        return a;
    return b;
}

inline float ToRadians(float degrees)
{
    return degrees * (M_PI/180.0f);
}

/* rotation needs to be in degrees */
static const glm::mat4 CreateTransformationMatrix(glm::vec3& translation, glm::vec3& rotation, float scale)
{
    glm::mat4 transform = glm::mat4(1.0f);                               /* identity matrix */
    transform = glm::translate(transform, translation);                 /* apply translation */
    
    transform = glm::rotate(transform, ToRadians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, ToRadians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, ToRadians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    transform = glm::scale(transform, glm::vec3(scale, scale, scale));

    return transform;
}

static glm::mat4 GenerateViewMatrix(const glm::vec3& cameraPosition, const glm::vec3& cameraAngle)
{
    glm::mat4 viewMat = glm::mat4(1.0f);                                                         /* (in radians) */
    viewMat = glm::rotate(viewMat, cameraAngle.x, glm::vec3(1.0f, 0.0f, 0.0f));                  /* pitch */
    viewMat = glm::rotate(viewMat, cameraAngle.y, glm::vec3(0.0f, 1.0f, 0.0f));                  /* yaw   */
    viewMat = glm::rotate(viewMat, cameraAngle.z, glm::vec3(0.0f, 0.0f, 1.0f));                  /* roll  */
    
    glm::vec3 negativeCamPos = glm::vec3(-cameraPosition.x, -cameraPosition.y, -cameraPosition.z);
    
    viewMat = glm::translate(viewMat, negativeCamPos);
    return viewMat;
}
}