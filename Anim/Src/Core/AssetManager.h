#pragma once
#include "pch.h"
#include "Utils/Memory.h"
#include "Renderer/Data/Shader.h"
//#include "Renderer/RenderObjects/Shaders/ComputeShader.h"

#include "Renderer/Window.h"
#include "Renderer/Data/VertexArray.h"
#include "Renderer/RenderObjects/Mesh.h"

/* using singleton schenanagans to control file-loading,
    allows us to avoid loading duplicate assets with map refs to filepaths. */

namespace Anim
{
    class AssetManager
    {
        unsigned int m_CurrentID;                                  /* non-uuid incrementing ID for each asset */
        std::map<unsigned int, SPtr<Shader>> m_ShaderRefs;
        std::map<unsigned int, SPtr<Mesh>> m_MeshRefs;
        std::map<const std::string, unsigned int> m_ShaderFilepaths;
        std::map<const std::string, unsigned int> m_MeshFilepaths;

        AssetManager(){}                                            /* default ctor for singleton instance */

        unsigned int GenAssetID();
        unsigned int GenerateVAO();
        void StoreDataInAttribList(unsigned int attribNum, unsigned int components, std::vector<float> data);

        void ProcessFace(int faceVertices[3][3], std::vector<unsigned int>& indices, std::vector<glm::vec2>& textures, 
                        std::vector<glm::vec3> &normals, std::vector<float> &texturesData, std::vector<float>& normalsData);
        
        std::map<unsigned int, SPtr<Shader>>* GetShaderMap();                   /* todo: use this to display currently active shader programs in Gui */

        
        
        MeshData LoadToVAO(std::vector<float>& data, unsigned int dim);
        MeshData LoadToVAO(std::vector<float>& pos, std::vector<float>& textCoords, 
                           std::vector<float>& normals, std::vector<unsigned int>& indices);

    public:
        static AssetManager& Get()
        {   
            static AssetManager s_instance;
            return s_instance;
        }
        AssetManager(const AssetManager& assetManager) = delete;

        unsigned int FindAssetID(std::map<const std::string, unsigned int>& fileMap, const std::string& filepath);
        SPtr<Shader> LoadShader(const std::string& filepath);

        //SPtr<ComputeShader> LoadComputeShader(const std::string& fp);
        
        std::array<GLint,4> LoadShaderFile(const std::string& filepath);
        std::string ReadShaderComponentFile(const std::string& filepath, ShaderComponentType shaderType);

        SPtr<Mesh> LoadMesh(const std::string& filepath);
        MeshData LoadOBJFile(const std::string& filepath);                      /* loads .obj (wavefront) file format */


    };
}