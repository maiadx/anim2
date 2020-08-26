#include "Renderer/Data/GLComputeShader.h"
#include "Core/AssetManager.h"
#include "Utils/Math.h"

using namespace Anim;

GLComputeShader::GLComputeShader(std::vector<Particle>& particles, const std::string& fp, unsigned int numWG) : GLShader("/usr/share/anim2/Shaders/ComputeShaders/default"), numWorkGroups(numWG), numObjects(particles.size())
{

    GLuint compShader = BuildComponent(fp, ShaderComponentType::Compute);

    this->csProgID = glCreateProgram();
    glAttachShader(csProgID, compShader);
    glLinkProgram(csProgID);

    LinkErrorCheck(compShader, ShaderComponentType::Compute);

    Setup(particles);
}

void GLComputeShader::Setup(std::vector<Particle>& particles)
{
    this->Bind();
    loc_viewMatrix = glGetUniformLocation(this->m_ShaderID, "view");
    loc_projMatrix = glGetUniformLocation(this->m_ShaderID, "projection");

    glUseProgram(csProgID);
    glGenVertexArrays(1, &computeVaoID);
    glBindVertexArray(computeVaoID);

    glGenBuffers(1, &computeSSBO);
    glBindBuffer(GL_ARRAY_BUFFER, computeSSBO);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), &particles[0], GL_STREAM_DRAW);

    /* */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(float) * 3 ));
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(float) * 6 ));

  
    glVertexAttribDivisor(0, 1);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    
    /* */
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void GLComputeShader::BindCS()
{
    glUseProgram(csProgID);
}

void GLComputeShader::Compute()
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, computeSSBO);
    glDispatchCompute( (numObjects/numWorkGroups)+1, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    glUseProgram(m_ShaderID);
    glBindVertexArray(computeVaoID);
}




GLuint GLComputeShader::GetCSID()
{
    return csProgID;
}

GLuint GLComputeShader::GetParticleSSBO()
{
    return computeSSBO;
}

GLuint GLComputeShader::GetParticleVaoID()
{
    return computeVaoID;
}


unsigned int GLComputeShader::GetNumObjects()
{
    return numObjects;
}

void GLComputeShader::SetViewMatrix(const glm::mat4& viewMat)
{
    this->LoadMat4(loc_viewMatrix, viewMat);
}

void GLComputeShader::SetProjMatrix(const glm::mat4& projMat)
{
    this->LoadMat4(loc_projMatrix, projMat);
}
