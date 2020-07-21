#pragma once
//#include "Core/Asset.h"
#include "Utils/Memory.h"
#include "Renderer/RenderObjects/Material.h"
#include "Renderer/Data/VertexArray.h"
namespace Anim 
{
class Mesh 
{
public:
	//Mesh();
	Mesh(const std::string& filepath);

	// Mesh(const Mesh& mesh)
	// {
	// 	LOG_WARN("Mesh Copy!");
	// 	this->vao_id = mesh.vao_id;
	// 	this->numIndices = mesh.numIndices;
	// 	this->numVertices = mesh.numVertices;
	// }

	~Mesh();
	
	//void addTexture(Texture& tex);
	void SetMaterial(SPtr<Material> material);
	SPtr<Material> GetMaterial();
	
	VertexArray* GetVao();
	unsigned int GetNumIndices();
	unsigned int GetNumVertices();
	//float getFurthest();

	
protected:
	SPtr<Material> material;
	VertexArray* vao;

	unsigned int numVertices;
	unsigned int numIndices;

private: 

};
}