#include "pch.h"
#include "Renderer/RenderObjects/Mesh.h"
#include "Core/AssetManager.h"
using namespace Anim;


Mesh::Mesh(const std::string& filepath)
{	
	MeshData meshData = AssetManager::Get().LoadOBJFile(filepath);
	
	this->vao = meshData.vao;
	this->numIndices = meshData.numIndices;
	this->numVertices = meshData.numVertices;
	this->material = std::make_shared<Material>();
}

Mesh::~Mesh()
{
	delete vao;

}

void Mesh::SetMaterial(SPtr<Material> material)
{
	this->material = material;
}

SPtr<Material> Mesh::GetMaterial()
{
	return material;
}

unsigned int Mesh::GetNumIndices()
{
	return this->numIndices;
}

VertexArray* Mesh::GetVao()
{
	return vao;
}

unsigned int Mesh::GetNumVertices()
{
	return this->numVertices;
}