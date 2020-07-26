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
	SPtr<Material> material;
	VertexArray* vao;

	unsigned int numVertices;
	unsigned int numIndices;

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