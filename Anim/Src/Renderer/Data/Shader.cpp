#include "pch.h"
#include "Renderer/Data/Shader.h"
#include "Renderer/Renderer.h"
#include "Core/AssetManager.h"
#include <glad/glad.h>
using namespace Anim;

Shader* Shader::Create(const std::string& fp)
{
    return new GLShader(fp);
}

GLShader::GLShader(const std::string& fp)
{
	GLuint vertID = BuildComponent(fp, ShaderComponentType::Vertex);
	GLuint fragID = BuildComponent(fp, ShaderComponentType::Fragment);
	m_ShaderID = glCreateProgram();

	glAttachShader(m_ShaderID, vertID);
	glAttachShader(m_ShaderID, fragID);

	glBindAttribLocation(m_ShaderID, 0, "position");
	glBindAttribLocation(m_ShaderID, 1, "normal");

	//LOG_WARN("Linking shader...");
	glLinkProgram(m_ShaderID);
	LinkErrorCheck(vertID, ShaderComponentType::Vertex);
	LinkErrorCheck(fragID, ShaderComponentType::Fragment);
}

GLShader::~GLShader()
{
	glDeleteProgram(m_ShaderID);
}

void GLShader::Bind()
{
	glUseProgram(m_ShaderID);
}

void GLShader::Unbind()
{
	glUseProgram(0);
}

unsigned int GLShader::BuildComponent(const std::string& fp, ShaderComponentType componentType)
{
	unsigned int componentID;
	GLenum shaderTypeGL;
	switch(componentType)
	{
	case ShaderComponentType::Vertex:
		shaderTypeGL = GL_VERTEX_SHADER; 
		break;	
	case ShaderComponentType::Fragment:
		shaderTypeGL = GL_FRAGMENT_SHADER; 
		break;	
	case ShaderComponentType::Geometry:
		shaderTypeGL = GL_GEOMETRY_SHADER; 
		break;	
	case ShaderComponentType::Compute:
		shaderTypeGL = GL_COMPUTE_SHADER; 
		break;	
	};
	componentID = glCreateShader(shaderTypeGL);
	std::string source = AssetManager::Get().ReadShaderComponentFile(fp, componentType).c_str();
	char const* srcPtr = source.c_str();
	glShaderSource(componentID, 1, &srcPtr, NULL);
	glCompileShader(componentID);
	return componentID;
}

void GLShader::Compile()
{


}

void GLShader::BindAttribute(unsigned int attribID, const std::string& varName)
{
	glBindAttribLocation(m_ShaderID, attribID, varName.c_str());
}

unsigned int GLShader::GetUniformLocation(const std::string& varName)
{
    return glGetUniformLocation(m_ShaderID, varName.c_str());
}


void GLShader::LoadInt(unsigned int loc, int value)
{
    glUniform1i(loc, (int)value);
}

void GLShader::LoadBool(unsigned int loc, bool flag)
{
	glUniform1i(loc, flag);
}

void GLShader::LoadFloat(unsigned int loc, float value)
{
	glUniform1f(loc, value);
}

void GLShader::LoadFloat2(unsigned int loc, const glm::vec2& vec)
{
	glUniform2fv(loc, 1, &vec[0]);
}	

void GLShader::LoadFloat3(unsigned int loc, const glm::vec3& vec)
{
	glUniform3fv(loc, 1, &vec[0]);
}

void GLShader::LoadFloat4(unsigned int loc, const glm::vec4& vec)
{
	glUniform4fv(loc, 1, &vec[0]);
}

void GLShader::LoadMat2(unsigned int loc, const glm::mat2& mat)
{
	glUniformMatrix2fv(loc, 1, GL_FALSE, &mat[0][0]);
}

void GLShader::LoadMat3(unsigned int loc, const glm::mat3& mat)
{
	glUniformMatrix3fv(loc, 1, GL_FALSE, &mat[0][0]);
}

void GLShader::LoadMat4(unsigned int loc, const glm::mat4& mat)
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
}


bool GLShader::LinkErrorCheck(unsigned int id, ShaderComponentType componentType)
{
    int errorLength;
	GLint linkStatus;
	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &linkStatus);
	glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &errorLength);

	if (errorLength > 0)
	{
		std::vector<char> errorMsg(errorLength + 1);
		glGetShaderInfoLog(id, errorLength, NULL, &errorMsg[0]);
		std::string message(errorMsg.begin(), errorMsg.end());
		std::string shaderTypeName;

        switch(componentType)
        {
        case ShaderComponentType::Vertex:
			shaderTypeName = "Vertex";
            break;
        case ShaderComponentType::Fragment:
			shaderTypeName = "Fragment";
            break;
        case ShaderComponentType::Geometry:
			shaderTypeName = "Geometry";
            break;
        case ShaderComponentType::Compute:
			shaderTypeName = "Compute";
            break;
        };
		Log::Error("Error trying to link Shader!");
		printf(message.c_str());
		//Log::Error(message.c_str());
		return true;
	}
	return false;
}
