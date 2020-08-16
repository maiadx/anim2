#pragma once
//#include "Core/Asset.h"
#include "Utils/Memory.h"
#include "Renderer/RenderObjects/Material.h"
#include "Renderer/Data/VertexArray.h"
namespace Anim 
{
class Mesh 
{

protected:
	SPtr<Material> m_Material;
	VertexArray* m_Vao;

	unsigned int m_NumVertices;
	unsigned int m_NumIndices;

public:
	Mesh(const std::string& filepath);
	~Mesh();
	
	void SetMaterial(SPtr<Material> material);
	SPtr<Material> GetMaterial();
	
	VertexArray* GetVao();
	unsigned int GetNumIndices();
	unsigned int GetNumVertices();
	
};
}