#pragma once
#include "Utils/Memory.h"
#include "Renderer/Data/VertexBuffer.h"
namespace Anim
{
class VertexArray
{
protected:
    unsigned int m_VaoID;
    unsigned int m_NumAttributes;

public:
    static VertexArray* Generate();
    virtual ~VertexArray(){}
    unsigned int GetVaoID();
    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void EnableAttribute(unsigned int attribNum) = 0;
    virtual void DisableAttribute(unsigned int attribNum) = 0;


};


class GLVertexArray : public VertexArray
{
public:
    GLVertexArray();
    ~GLVertexArray();
    void Bind();
    void Unbind();
    void EnableAttribute(unsigned int attribNum);
    void DisableAttribute(unsigned int attribNum);

private:

};


class VKVertexArray : public VertexArray
{
public:
    VKVertexArray();
    ~VKVertexArray();
    void Bind();
    void Unbind();
    void EnableAttribute(unsigned int attribNum);
    void DisableAttribute(unsigned int attribNum);
};
}


