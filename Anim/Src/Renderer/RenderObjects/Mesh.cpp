#include "pch.h"
#include "Renderer/RenderObjects/Mesh.h"
#include "Core/AssetManager.h"
using namespace Anim;


Mesh::Mesh(const std::string& filepath)
{	
	MeshData meshData = AssetManager::Get().LoadOBJFile(filepath);
	
	this->m_Vao = meshData.Vao;
	this->m_NumIndices = meshData.NumIndices;
	this->m_NumVertices = meshData.NumVertices;
	this->m_Material = std::make_shared<Material>();
}

Mesh::~Mesh()
{
	delete m_Vao;

}

void Mesh::SetMaterial(SPtr<Material> material)
{
	this->m_Material = material;
}

SPtr<Material> Mesh::GetMaterial()
{
	return m_Material;
}

unsigned int Mesh::GetNumIndices()
{
	return this->m_NumIndices;
}

VertexArray* Mesh::GetVao()
{
	return m_Vao;
}

unsigned int Mesh::GetNumVertices()
{
	return this->m_NumVertices;
}