#include "pch.h"
#include "VertexArray.h"
#include "Renderer/Renderer.h"
using namespace Anim;


VertexArray* VertexArray::Generate()
{
    return new GLVertexArray();
}

unsigned int VertexArray::GetVaoID()
{
    return m_VaoID;
}




GLVertexArray::GLVertexArray()
{
    glGenVertexArrays(1, &m_VaoID);
}

GLVertexArray::~GLVertexArray()
{
    glDeleteVertexArrays(1, &m_VaoID);
}

void GLVertexArray::Bind()
{
    glBindVertexArray(m_VaoID);
}

void GLVertexArray::Unbind()
{
    glBindVertexArray(0);
}

void GLVertexArray::EnableAttribute(unsigned int attribNum)
{
    glEnableVertexAttribArray(attribNum);
}

void GLVertexArray::DisableAttribute(unsigned int attribNum)
{
    glDisableVertexAttribArray(attribNum);
}


VKVertexArray::VKVertexArray()
{

}

VKVertexArray::~VKVertexArray()
{

}

void VKVertexArray::Bind()
{

}

void VKVertexArray::Unbind()
{

}

void VKVertexArray::EnableAttribute(unsigned int attribNum)
{

}

void VKVertexArray::DisableAttribute(unsigned int attribNum)
{

}