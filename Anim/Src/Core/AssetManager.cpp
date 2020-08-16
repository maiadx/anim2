#include "pch.h"
#include "Core/AssetManager.h"
#include "Core/Log.h"
#include "Renderer/Renderer.h"
#include "Renderer/Data/VertexBuffer.h"

using namespace Anim;

/* each asset (Shader, Mesh) has its own ID to avoid loading the same data from a file twice */
unsigned int AssetManager::GenAssetID()
{
    return ++m_CurrentID;                                          /* reserve index 0 for a failed search result */
}

unsigned int AssetManager::FindAssetID(std::map<const std::string, unsigned int>& fileMap, const std::string& filepath)
{
    std::map<const std::string, unsigned int>::iterator iter;
    unsigned int assetID;

    iter = fileMap.find(filepath);
    if(iter != fileMap.end())                                       /* asset has already been loaded */
    {
        return iter->second;
    }
    return 0;                                                       /* asset has not been loaded */
}

SPtr<Mesh> AssetManager::LoadMesh(const std::string& filepath)
{
    unsigned int assetID = FindAssetID(m_MeshFilepaths, filepath);

    if(assetID != 0)
    {
        m_MeshRefs[assetID];
    }
    assetID = GenAssetID();
    m_MeshRefs.insert(std::pair<unsigned int, SPtr<Mesh>>(assetID, std::make_shared<Mesh>(filepath)));
    m_MeshFilepaths.insert(std::pair<std::string, unsigned int>(filepath, assetID));
    return m_MeshRefs[assetID];
}

SPtr<Shader> AssetManager::LoadShader(const std::string& filepath)
{
    unsigned int assetID = FindAssetID(m_ShaderFilepaths, filepath);

    if(assetID != 0)
    {
        return m_ShaderRefs[assetID];
    }
    assetID = GenAssetID();
    m_ShaderRefs.insert(std::pair<unsigned int, SPtr<Shader>>(assetID, Shader::Create(filepath)));
    m_ShaderFilepaths.insert(std::pair<std::string, unsigned int>(filepath, assetID));
    return m_ShaderRefs[assetID];
}

void AssetManager::StoreDataInAttribList(unsigned int attribNum, unsigned int dimensions, std::vector<float> data)
{
    unsigned int VboID;
    glGenBuffers(1, &VboID);
    glBindBuffer(GL_ARRAY_BUFFER, VboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attribNum, dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);           /* check correct stride value for float array */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::map<unsigned int, SPtr<Shader>>* AssetManager::GetShaderMap()
{
    return &m_ShaderRefs;
}

/* loads a single vertex buffer object to VAO */
MeshData AssetManager::LoadToVAO(std::vector<float>& positions, unsigned int dim)
{
    VertexArray* vao = VertexArray::Generate();                                                                            /* should I be calling 'new' here? */
    vao->Bind();
    VertexBuffer* vbo = VertexBuffer::Create(VertexBufferDataType::ARRAY_BUFFER, VertexBufferUsageType::STATIC_DRAW);
    vbo->Bind();
    vbo->StoreDataInAttribute(0, dim, positions);
    vbo->Unbind();
    vao->Unbind();
    
    delete vbo;
    MeshData meshData;

    meshData.Vao = vao;
    meshData.NumVertices = positions.size()/dim;
    meshData.NumIndices = positions.size()/dim;
    
    return meshData;
}

/* used for .obj file loading */
MeshData AssetManager::LoadToVAO(std::vector<float>& positions, std::vector<float>& texCoordinates,
                                                               std::vector<float>& normals, std::vector<unsigned int>& indices)
{
    VertexArray* vao = VertexArray::Generate();
    vao->Bind();

    VertexBuffer* positionsBuffer = VertexBuffer::Create(VertexBufferDataType::ARRAY_BUFFER, VertexBufferUsageType::STATIC_DRAW);
    VertexBuffer* normalsBuffer = VertexBuffer::Create(VertexBufferDataType::ARRAY_BUFFER, VertexBufferUsageType::STATIC_DRAW);
    VertexBuffer* texCoordsBuffer = VertexBuffer::Create(VertexBufferDataType::ARRAY_BUFFER, VertexBufferUsageType::STATIC_DRAW);

    VertexBuffer* indexBuffer = VertexBuffer::Create(VertexBufferDataType::ELEMENT_BUFFER, VertexBufferUsageType::STATIC_DRAW);
    indexBuffer->Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    indexBuffer->Unbind();

    positionsBuffer->Bind();
    positionsBuffer->StoreDataInAttribute(0, 3, positions);
    positionsBuffer->Unbind();

    normalsBuffer->Bind();
    normalsBuffer->StoreDataInAttribute(1, 3, normals);
    normalsBuffer->Unbind();

    texCoordsBuffer->Bind();
    texCoordsBuffer->StoreDataInAttribute(0, 3, positions);
    texCoordsBuffer->Unbind();

    unsigned int numIndices = indices.size();
    vao->Unbind();
    delete positionsBuffer;
    delete normalsBuffer;
    delete texCoordsBuffer;
    
    MeshData meshData; 
    meshData.Vao = vao;
    meshData.NumIndices = numIndices;
    meshData.NumVertices = positions.size()/3;
    return meshData;
}   

std::string AssetManager::ReadShaderComponentFile(const std::string& filepath, ShaderComponentType shaderType)
{
    // GLuint shaderID = 0;//glCreateShader(shaderType);
    std::string fileExt;

    switch(shaderType)
    {
    case ShaderComponentType::Vertex:
        fileExt = ".vert";
        break;
    case ShaderComponentType::Fragment:
        fileExt = ".frag";
        break;
    case ShaderComponentType::Geometry:
        fileExt = ".geom";
        break;
    case ShaderComponentType::Compute:
        fileExt = ".comp";
        break;
    };

    std::string fullFilePath = filepath + fileExt;
    std::string source;

	std::ifstream sourceStream(fullFilePath, std::ios::in);
	if (sourceStream.is_open())
	{
		std::stringstream src;
		src << sourceStream.rdbuf();
		source = src.str();
		sourceStream.close();
	}
	else {
	    Log::Error((("Compiling glsl shader file: ") + fullFilePath).c_str());
        return "[file not found]";
	}

	//LOG_INFO("Compiling shader file: {}", fullFilePath);
	//glShaderSource(shaderID, 1, &srcPtr, NULL);
	//glCompileShader(shaderID);
    //Renderer::Get().GetRenderAPI()->CompileShader();
	//Log::Info((("Compiling glsl shader file: ") + fullFilePath).c_str());
    return source;
}

/* 
    .obj wavefront importer : treats each face as having one normal (in blender: smooth surface), 
    where the mesh requires double vertices along any given texture coordinate seam for correct indices 
*/

void AssetManager::ProcessFace(int faceVertices[3][3], std::vector<unsigned int> &indices, std::vector<glm::vec2> &textures, 
                               std::vector<glm::vec3> &normals, std::vector<float> &texturesData, std::vector<float> &normalsData )
{
    for(int i = 0; i < 3; i++)
    {
        int currentVertPtr = faceVertices[i][0] - 1;
        indices.push_back(currentVertPtr);
        
        glm::vec2 currentTexCoord = textures[faceVertices[i][1]-1];
        texturesData[currentVertPtr*2] = currentTexCoord.x;
        texturesData[currentVertPtr*2 +1] = currentTexCoord.y;

        glm::vec3 currentNormal = normals[faceVertices[i][2]-1];
        normalsData[currentVertPtr * 3] = currentNormal.x;
        normalsData[currentVertPtr * 3 +1] = currentNormal.y;
        normalsData[currentVertPtr * 3 +2] = currentNormal.z;
    }
}

MeshData AssetManager::LoadOBJFile(const std::string& filepath)
{
    std::string line;                            /* per line .obj info */
    std::ifstream openFile(filepath.c_str());
    if(!openFile.is_open())
    {
        Log::Error(("Error loading file: " + filepath).c_str());
        return {0,0,0};
    }
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;
    std::vector<unsigned int> indices;
    
    std::vector<float> verticesData;
    std::vector<float> texturesData;
    std::vector<float> normalsData;
    
    vertices.reserve(1000);
    normals.reserve(1000);
    textures.reserve(1000);
    indices.reserve(300);

    std::vector<std::string> lineData;
    
    while(!openFile.eof())
    {
        std::getline(openFile, line);
        std::stringstream ss(line);
        std::string token;
        while(std::getline(ss, token, ' '))
        {
            lineData.emplace_back(token);                              
        }
        
        if(lineData[0] == "v")
        {
            glm::vec3 vert(atof(lineData[1].c_str()), atof(lineData[2].c_str()), atof(lineData[3].c_str()));
            vertices.emplace_back(vert);
        }
        else if (lineData[0] == "vt")
        {
            glm::vec2 texCoord(atof(lineData[1].c_str()), atof(lineData[2].c_str()));
            textures.emplace_back(texCoord);
        }
        else if(lineData[0] == "vn")                
        {
            glm::vec3 norm(atof(lineData[1].c_str()), atof(lineData[2].c_str()), atof(lineData[3].c_str()));
            normals.emplace_back(norm);
        }
        else if(lineData[0] == "f")
        {
            /* current lineData needs to be read in the next step */
            break;
        }
        lineData.clear();
    }
    /* Next Phase -> faces */
    
    verticesData.reserve(vertices.size() * 3);
    normalsData.resize(vertices.size() * 3);
    texturesData.resize(vertices.size() * 2);

    lineData.clear();

    while(!openFile.eof())    
    {
        std::stringstream ss(line);
        std::string token;
        while(std::getline(ss, token, ' '))
        {
            lineData.push_back(token);                              /* split line by ' '  */
        }

        if(lineData[0] == "f")
        {
            int faceVertices[3][3];

            for(unsigned int i = 0; i < 3; i++)
            {
                std::stringstream ssVert(lineData[i+1]);
                std::string tokVert;

                for(int j = 0; j < 3; j++)
                {
                    std::getline(ssVert, tokVert, '/');             /* split face vertices by '/'  */
                    faceVertices[i][j] = atoi(tokVert.c_str());
                }
            }

            ProcessFace(faceVertices, indices, textures, normals, texturesData, normalsData);
        }
        lineData.clear();
        std::getline(openFile, line);
    }
    openFile.close();
    /* done parsing .obj */

    for(glm::vec3 vertex : vertices)
    {
        verticesData.push_back(vertex.x);
        verticesData.push_back(vertex.y);
        verticesData.push_back(vertex.z);
    }
    MeshData meshData = LoadToVAO(verticesData, texturesData, normalsData, indices);
    meshData.NumVertices = vertices.size();
    return meshData;
}