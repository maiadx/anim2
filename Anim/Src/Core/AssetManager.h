#pragma once
#include "pch.h"
#include "Utils/Memory.h"
#include "Renderer/Data/Shader.h"
//#include "Renderer/RenderObjects/Shaders/ComputeShader.h"

#include "Renderer/Window.h"
#include "Renderer/Data/VertexArray.h"
#include "Renderer/RenderObjects/Mesh.h"
/* using singleton schenanagans to control memory management
   in one instance across the program, allows us to avoid loading duplicate assets with map refs to filepaths. */
namespace Anim
    {
    struct MeshData
    {
        VertexArray* vao;
        uint32 numIndices;
        uint32 numVertices;
    };

    class AssetManager
    {
        unsigned int currentIDPtr;
        std::map<unsigned int, SPtr<Shader>> shaderRefs;
        std::map<unsigned int, SPtr<Mesh>> meshRefs;
        std::map<const std::string, unsigned int> shaderFilepaths;
        std::map<const std::string, unsigned int> meshFilepaths;

        AssetManager(){}
        unsigned int GenAssetID();

        unsigned int GenerateVAO();
        void StoreDataInAttribList(unsigned int attribNum, unsigned int components, std::vector<float> data);
        void ProcessFace(int faceVertices[3][3], std::vector<unsigned int>& indices, std::vector<glm::vec2>& textures, 
                        std::vector<glm::vec3> &normals, std::vector<float> &texturesData, std::vector<float>& normalsData);
        
        std::map<unsigned int, SPtr<Shader>>* GetShaderMap();

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
        MeshData LoadOBJFile(const std::string& filepath);
        
        MeshData LoadToVAO(std::vector<float>& data, unsigned int dim);
        MeshData LoadToVAO(std::vector<float>& pos, std::vector<float>& textCoords, 
                           std::vector<float>& normals, std::vector<unsigned int>& indices);

    };
}