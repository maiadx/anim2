#include "pch.h"
#include "Renderer/RenderObjects/Light.h"
//#include <glm/glm.hpp>

using namespace Anim;

Light::Light(const glm::vec3& position, const glm::vec3& color) : m_Position(position), m_Color(color)
{
    this->m_Attenuation = glm::vec3(1.0f,0.0f,0.0f);
}

Light::Light(const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation) : m_Position(position), m_Color(color), m_Attenuation(attenuation) {}

Light::~Light()
{

}

glm::vec3& Light::GetPosition()
{
    return m_Position;
}

glm::vec3& Light::GetColor()
{
    return m_Color;
}

glm::vec3& Light::GetAttenuation()
{
    return m_Attenuation;
}

void Light::SetPosition(const glm::vec3& position)
{
    m_Position = position;
}

void Light::SetColor(glm::vec3 color)
{
    m_Color = color;
}

void Light::SetAttenuation(const glm::vec3& attenuation)
{
    m_Attenuation = attenuation;
}