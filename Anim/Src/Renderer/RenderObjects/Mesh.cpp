#include "pch.h"
#include "Renderer/RenderObjects/Mesh.h"
#include "Core/AssetManager.h"
using namespace Anim;


Mesh::Mesh(const std::string& filepath)
{	
	m_MeshData = AssetManager::Get().LoadOBJFile(filepath);
	

	this->m_Material = std::make_shared<Material>();
}

Mesh::~Mesh()
{
	delete m_MeshData.Vao;

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
	return this->m_MeshData.NumIndices;
}

VertexArray* Mesh::GetVao()
{
	return m_MeshData.Vao;
}

unsigned int Mesh::GetNumVertices()
{
	return this->m_MeshData.NumVertices;
}