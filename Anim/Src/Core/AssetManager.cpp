#include "pch.h"
#include "Core/AssetManager.h"
#include "Core/Log.h"
#include "Renderer/Renderer.h"
#include "Renderer/Data/VertexBuffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
using namespace Anim;

unsigned int AssetManager::GenAssetID()
{
    return ++currentIDPtr;                                           /* id = 0 is reserved for an ID search failure */
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
    unsigned int assetID = FindAssetID(meshFilepaths, filepath);

    if(assetID != 0)
    {
        meshRefs[assetID];
    }
    assetID = GenAssetID();
    meshRefs.insert(std::pair<unsigned int, SPtr<Mesh>>(assetID, std::make_shared<Mesh>(filepath)));
    meshFilepaths.insert(std::pair<std::string, unsigned int>(filepath, assetID));
    return meshRefs[assetID];
}

SPtr<Shader> AssetManager::LoadShader(const std::string& filepath)
{
    unsigned int assetID = FindAssetID(shaderFilepaths, filepath);

    if(assetID != 0)
    {
        return shaderRefs[assetID];
    }
    assetID = GenAssetID();
    shaderRefs.insert(std::pair<unsigned int, SPtr<Shader>>(assetID, Shader::Create(filepath)));
    shaderFilepaths.insert(std::pair<std::string, unsigned int>(filepath, assetID));
    return shaderRefs[assetID];
}

SPtr<Texture> AssetManager::LoadTexture(const std::string& filepath, TextureType texType)
{
    unsigned int assetID = FindAssetID(textureFilepaths, filepath);

    if(assetID != 0)
    {
        return textureRefs[assetID];
    }
    assetID = GenAssetID();
    SPtr<Texture> texture = Texture::Create(texType, false);
    texture->Bind();
    LoadTextureFile(texture, filepath, texType);
    texture->Unbind();
    textureRefs.insert(std::pair<unsigned int, SPtr<Texture>>(assetID, Texture::Create(texType, false)));
    textureFilepaths.insert(std::pair<std::string, unsigned int>(filepath, assetID));
    return textureRefs[assetID];
}

// SPtr<CubeMap> AssetManager::LoadCubeMap(const std::string& filepath, TextureType texType)
// {
//    unsigned int assetID = FindAssetID(cubeMapFilepaths, filepath);
//     if(assetID != 0)
//     {
//         return cubeMapRefs[assetID];
//     }

//     std::array<std::string, 6> mapFaceFilepaths;
//     mapFaceFilepaths[0] = filepath + "/right.png";
//     mapFaceFilepaths[1] = filepath + "/left.png";
//     mapFaceFilepaths[2] = filepath + "/top.png";
//     mapFaceFilepaths[3] = filepath + "/bottom.png";
//     mapFaceFilepaths[4] = filepath + "/front.png";
//     mapFaceFilepaths[5] = filepath + "/back.png";
    
//     assetID = GenAssetID();
//     cubeMapRefs.insert(std::pair<unsigned int, std::unique_ptr<CubeMap>>(assetID, std::make_unique<CubeMap>(mapFaceFilepaths, texType)));
//     return cubeMapRefs[assetID];
// }

// unsigned int AssetManager::GenerateVAO()
// {
//     unsigned int vaoID;
//     VertexArray::GenArray
//     glGenVertexArrays(1, &vaoID);
//     glBindVertexArray(vaoID);
//     return vaoID;
// }

void AssetManager::StoreDataInAttribList(unsigned int attribNum, unsigned int dimensions, std::vector<float> data)
{
    unsigned int VboID;
    glGenBuffers(1, &VboID);
    glBindBuffer(GL_ARRAY_BUFFER, VboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attribNum, dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);           /* check correct stride value for float array */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//void AssetManager::StoreDataInAttribList(unsigned int attribNum, unsigned int)

// static void bindIBO(std::vector<unsigned int> &indices)
// {
//     unsigned int iboID;
//     glGenBuffers(1, &iboID);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

// }

std::map<unsigned int, SPtr<Texture>>* AssetManager::GetTextureMap()
{
    return &textureRefs;
}

std::map<unsigned int, SPtr<Shader>>* AssetManager::GetShaderMap()
{
    return &shaderRefs;
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
    meshData.vao = vao;
    meshData.numVertices = positions.size()/dim;
    meshData.numIndices = positions.size()/dim;
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
    meshData.vao = vao;
    meshData.numIndices = numIndices;
    meshData.numVertices = positions.size()/3;
    return meshData;
}   

std::array<GLint, 4> AssetManager::LoadShaderFile(const std::string& filepath)
{
    std::string glslVersion; 
    std::array<GLint, 4> shaderIDs = {-1, -1, -1, -1};                     /* flags for what stages exist in shader */

    std::string vertSrc, fragSrc, geomSrc, compSrc;
    std::string* activeSrc;
    std::string line;                                           
    std::ifstream openFile(filepath.c_str());
    
    if(!openFile.is_open())
    {
        Log::Error(("Error loading glsl shader: " + filepath).c_str());
        return shaderIDs;
    }

    std::getline(openFile, line);
    glslVersion = line;                                                 /* first line MUST be the glsl version */
    vertSrc += glslVersion;
    fragSrc += glslVersion;
    geomSrc += glslVersion;
    compSrc += glslVersion;

    while(!openFile.eof())
    {
        std::getline(openFile, line);
        std::stringstream ss(line);
        std::string token;

        if(line.at(0) == '.')
        {
            if(line.find(".vert") != std::string::npos)
            {
                //shaderIDs[0] = glCreateShader(GL_VERTEX_SHADER);
                activeSrc = &vertSrc;
            } else if(line.find(".frag") != std::string::npos)
            {
                //shaderIDs[1] = glCreateShader(GL_FRAGMENT_SHADER);
                activeSrc = &fragSrc;
            } else if(line.find(".geom") != std::string::npos)
            {
                //shaderIDs[2] = glCreateShader(GL_GEOMETRY_SHADER);
                activeSrc = &geomSrc;
            } else if(line.find(".comp") != std::string::npos)
            {
                //shaderIDs[3] = glCreateShader(GL_COMPUTE_SHADER);
                activeSrc = &compSrc;
            }
            continue;
        } else if(activeSrc == nullptr)
            continue;

        *activeSrc += line;
        *activeSrc += "\n";
    }
    openFile.close();

	Log::Error((("Compiling glsl shader file: ") + filepath).c_str());

    const char* srcPtr;
    unsigned int i;
    if(shaderIDs[0] != -1)
    {
        srcPtr = vertSrc.c_str();
        // glShaderSource(shaderIDs[0], 1, &srcPtr, NULL);
        // glCompileShader(shaderIDs[0]);
    }
    if(shaderIDs[1] != -1)
    {
        srcPtr = fragSrc.c_str();
        // glShaderSource(shaderIDs[1], 1, &srcPtr, NULL);
        // glCompileShader(shaderIDs[1]);
    }
    if(shaderIDs[2] != -1)
    {
        srcPtr = fragSrc.c_str();
        // glShaderSource(shaderIDs[2], 2, &srcPtr, NULL);
        // glCompileShader(shaderIDs[2]);
    }    
    if(shaderIDs[3] != -1)
    {    
        srcPtr = fragSrc.c_str();
        // glShaderSource(shaderIDs[1], 1, &srcPtr, NULL);
        // glCompileShader(shaderIDs[1]);
    }

    
    return shaderIDs;
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

void AssetManager::LoadTextureFile(SPtr<Texture>& texture, const std::string& filepath, TextureType texType)
{
    int width, height, channels;
    unsigned int id;
	// glGenTextures(1, &id);
	// glBindTexture(format, id);
    // SPtr<GLTexture> texture =  std::make_shared<GLTexture>(texType, false);
    texture->Bind();
	unsigned char* imageData = stbi_load((filepath.c_str()), &width, &height, &channels, 0);
	if (imageData)
	{
        texture->Load(&imageData, width, height);

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		//LOG_CLI_INFO(("Loaded Texture from location: " + filepath).c_str());
		//glGenerateMipmap(GL_TEXTURE_2D);

		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// if(texType == TextureType::Diffuse || texType == TextureType::Specular)
        // {
        //     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
        //     // if(gladIsSupported("GL_EXT_texture_filter_anisotropic") || GLEW_EXT_texture_filter_anisotropic)
        //     // {
                
        //     // } else {
        //     //     LOG_WARN("anisotropic filtering is not available!");
        //     //     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1);
        //     // }
        // }
    }
	else
	{
		Log::Error((("Failed to load image: ") + filepath).c_str());
        stbi_image_free(imageData);
	    return LoadTextureFile(texture, "./Resources/Textures/planet.png", texType);
	}
    stbi_image_free(imageData);
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
    meshData.numVertices = vertices.size();
    return meshData;
}

