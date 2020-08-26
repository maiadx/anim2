#pragma once
#include "Utils/Memory.h"
#include "Renderer/Data/Shader.h"
#include "Renderer/RenderObjects/Light.h"

/* Material: Holds a reference to a Shader Program it can bind/unbind.
             Caches shader uniform locations and values */
namespace Anim 
{
class Material
{
    SPtr<Shader> shader;
	glm::vec3 baseColor;
    float reflectivity;
    float shineDamper;

    /* uniform caching - where each variable is stored inside the glsl shader */
	uint32_t loc_modelMatrix;
	uint32_t loc_projectionMatrix;
	uint32_t loc_viewMatrix;

	uint32_t loc_baseColor;
	uint32_t loc_reflectivity;
	uint32_t loc_shineDamper;

    static const int NUM_LIGHTS = 3;
	uint32_t loc_lightPositions[NUM_LIGHTS];
	uint32_t loc_lightColors[NUM_LIGHTS];
	uint32_t loc_attenuations[NUM_LIGHTS];

public:
    Material();
    ~Material();

    SPtr<Shader> GetShader();
    void CacheUniforms();
    void Bind();
    void Unbind();

    glm::vec3& GetBaseColor();
    void SetBaseColor(const glm::vec3& baseColor);
    void LoadColor(const glm::vec3& color);

    float GetReflectivity();
    void SetReflectivity(float reflectivity);
    float GetShineDamper();    
    void SetShineDamper(float shineDamper);

    void LoadLights(std::array<Light, 3>& lights);

    void LoadModelMatrix(const glm::mat4& modelMat);
    void LoadProjectionMatrix(const glm::mat4& projectionMat);
    void LoadViewMatrix(const glm::mat4& viewMat);
};
}