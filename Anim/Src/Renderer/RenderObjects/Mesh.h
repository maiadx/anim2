#pragma once
//#include "Core/Asset.h"
#include "Utils/Memory.h"
#include "Renderer/RenderObjects/Material.h"
#include "Renderer/Data/VertexArray.h"
namespace Anim 
{
	struct MeshData
	{
		VertexArray* Vao;
		uint32 NumIndices;
		uint32 NumVertices;
	};

	class Mesh 
	{

	protected:
		SPtr<Material> m_Material;
		MeshData m_MeshData;

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