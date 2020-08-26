#pragma once
namespace Anim
{
#define MAX_NUM_LIGHTS 4
class Light
{
    glm::vec3 m_Position;
    glm::vec3 m_Color;
    glm::vec3 m_Attenuation;

public:
    Light(const glm::vec3& pos, const glm::vec3& color);
    Light(const glm::vec3& pos, const glm::vec3& color, const glm::vec3& a);
    ~Light();

    glm::vec3& GetPosition();
    glm::vec3& GetColor();
    glm::vec3& GetAttenuation();
    
    void SetPosition(const glm::vec3& pos);
    void SetColor(glm::vec3 color);
    void SetAttenuation(const glm::vec3& a);


};
}