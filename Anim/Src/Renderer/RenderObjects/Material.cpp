#include "pch.h"
#include "Renderer/RenderObjects/Material.h"
#include "Core/AssetManager.h"
#include "Renderer/Renderer.h"
using namespace Anim;

Material::Material()
{
    shader = AssetManager::Get().LoadShader("/usr/share/anim2/Shaders/basic");
    baseColor = glm::vec3(0.5,0.5,0.5);
    reflectivity = 0.3f;
    shineDamper = 0.8f;
    CacheUniforms();
}

Material::~Material()
{

}

SPtr<Shader> Material::GetShader()
{
    return shader;
}

void Material::CacheUniforms()
{
    loc_baseColor = shader->GetUniformLocation("baseColor");
    loc_shineDamper = shader->GetUniformLocation("shineDamper");
    loc_baseColor = shader->GetUniformLocation("baseColor");

	loc_modelMatrix = shader->GetUniformLocation("model");
	loc_viewMatrix = shader->GetUniformLocation("view");
	loc_projectionMatrix = shader->GetUniformLocation("projection");

    for(int i = 0; i < NUM_LIGHTS; i++)
	{
		std::string location("lightPosition["+std::to_string(i)+"]");
		loc_lightPositions[i] = shader->GetUniformLocation(location); 
		location = std::string("lightColor["+std::to_string(i)+"]");
		loc_lightColors[i] = shader->GetUniformLocation(location);
		location = std::string("attenuations["+std::to_string(i)+"]");
		loc_attenuations[i] = shader->GetUniformLocation(location);
	}

}

void Material::Bind()
{
    shader->Bind();
    shader->LoadFloat(loc_reflectivity, reflectivity);
    shader->LoadFloat(loc_shineDamper, shineDamper);
    shader->LoadFloat3(loc_baseColor, baseColor);
}
void Material::Unbind()
{
    shader->Unbind();
}

void Material::SetBaseColor(const glm::vec3& baseColor)
{
    this->baseColor = baseColor;
}

void Material::LoadColor(const glm::vec3& color)
{
	this->baseColor = color;
	shader->LoadFloat3(loc_baseColor, color);
}

float Material::GetReflectivity()
{
    return reflectivity;
}

void Material::SetReflectivity(float reflectivity)
{
    this->reflectivity = reflectivity;
}

float Material::GetShineDamper()
{
    return shineDamper;
}

void Material::SetShineDamper(float shineDamper)
{
    this->shineDamper = shineDamper;
}

void Material::LoadLights(std::array<Light, 3>& lights)
{
    for(int i = 0; i < 3; i++)
    {
        shader->LoadFloat3(loc_lightPositions[i], lights[i].GetPosition());
	    shader->LoadFloat3(loc_lightColors[i], lights[i].GetColor());
	    shader->LoadFloat3(loc_attenuations[i], lights[i].GetAttenuation());
    }

}

void Material::LoadModelMatrix(const glm::mat4& modelMat)
{
    shader->LoadMat4(loc_modelMatrix, modelMat);
}

void Material::LoadProjectionMatrix(const glm::mat4& projectionMat)
{
    shader->LoadMat4(loc_projectionMatrix, projectionMat);
}

void Material::LoadViewMatrix(const glm::mat4& viewMat)
{
    shader->LoadMat4(loc_viewMatrix, viewMat);
}
