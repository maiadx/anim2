#pragma once
#include "Utils/Memory.h"
#include "Utils/Math.h"
namespace Anim
{
enum class ShaderComponentType { Vertex, Fragment, Geometry, Compute };

class Shader
{
protected:
    virtual bool LinkErrorCheck(unsigned int id, ShaderComponentType componentType) = 0;

public:
    static Shader* Create(const std::string& fp);
    virtual ~Shader(){}

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void Compile() = 0;

    virtual void BindAttribute(unsigned int attribID, const std::string& varName) = 0;
    virtual unsigned int GetUniformLocation(const std::string& varName) = 0;

	virtual void LoadInt(unsigned int loc, int value) = 0;
	virtual void LoadBool(unsigned int loc, bool flag) = 0;
	virtual void LoadFloat(unsigned int loc, float value) = 0;
	virtual void LoadFloat2(unsigned int loc, const glm::vec2& vec) = 0;	
	virtual void LoadFloat3(unsigned int loc, const glm::vec3& vec) = 0;
	virtual void LoadFloat4(unsigned int loc, const glm::vec4& vec) = 0;
	virtual void LoadMat2(unsigned int loc, const glm::mat2& mat) = 0;
	virtual void LoadMat3(unsigned int loc, const glm::mat3& mat) = 0;
	virtual void LoadMat4(unsigned int loc, const glm::mat4& mat) = 0;


 

};

class GLShader : public Shader
{
protected:
	unsigned int m_ShaderID;
	
	unsigned int BuildComponent(const std::string& fp, ShaderComponentType componentType);
    bool LinkErrorCheck(unsigned int id, ShaderComponentType componentType);

public:
	GLShader(const std::string& fp);
	~GLShader();

    void Bind();
    void Unbind();
    void Compile();
    void BindAttribute(unsigned int attribID, const std::string& varName);
    unsigned int GetUniformLocation(const std::string& varName);

	void LoadInt(unsigned int loc, int value);
	void LoadBool(unsigned int loc, bool flag);
	void LoadFloat(unsigned int loc, float value);
	void LoadFloat2(unsigned int loc, const glm::vec2& vec);	
	void LoadFloat3(unsigned int loc, const glm::vec3& vec);
	void LoadFloat4(unsigned int loc, const glm::vec4& vec);
	void LoadMat2(unsigned int loc, const glm::mat2& mat);
	void LoadMat3(unsigned int loc, const glm::mat3& mat);
	void LoadMat4(unsigned int loc, const glm::mat4& mat);

};
}