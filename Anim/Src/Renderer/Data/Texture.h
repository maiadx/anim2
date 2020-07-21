#pragma once
#include "Utils/Memory.h"
namespace Anim
{
enum class TextureType : unsigned char
{
	Diffuse, Specular, Normal, Displacement
};

class Texture
{
public:
    static SPtr<Texture> Create(TextureType texType, bool transparency);
    //virtual ~Texture(){}
    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void Load(unsigned char** imageData, int width, int height) = 0;
    
protected:
    bool containsTransparency;
    TextureType textureType;
};


class GLTexture : public Texture
{
public:
    GLTexture(TextureType texType, bool transparency);
    ~GLTexture();

    void Bind() override;
    void Unbind() override;
    void Load(unsigned char** imageData, int width, int height) override;

private:
    unsigned int textureID;

};
}


