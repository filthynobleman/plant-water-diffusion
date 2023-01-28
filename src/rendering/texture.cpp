/**
 * @file        texture.cpp
 * 
 * @brief       Implements the texture part from shader.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-30
 */
#include <rendering/shader.hpp>
#include <iostream>
#include <sstream>
#include <stb_image.h>

render::Texture::Texture(int Width, int Height, GLenum Format)
    : Width(Width), Height(Height), Format(Format)
{
    GLenum InternalFormat;
    switch (Format)
    {
    case GL_RED:    InternalFormat = GL_R32F; break;
    case GL_RG:     InternalFormat = GL_RG32F; break;
    case GL_RGB:    InternalFormat = GL_RGB32F; break;
    case GL_RGBA:   InternalFormat = GL_RGBA32F; break;
    
    default:
        std::stringstream ss;
        ss << "Only accepted formats for textures are:" << std::endl;
        ss << "  - GL_RED" << std::endl;
        ss << "  - GL_RG" << std::endl;
        ss << "  - GL_RGB" << std::endl;
        ss << "  - GL_RGBA" << std::endl;
        throw std::runtime_error(ss.str());
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, GL_FLOAT, NULL);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

render::Texture::Texture(int Width, int Height, int NumChannels)
    : Width(Width), Height(Height)
{
    GLenum Format, InternalFormat;
    switch (NumChannels)
    {
    case 1:
        Format = GL_RED;
        InternalFormat = GL_R32F;
        break;
    case 2:
        Format = GL_RG;
        InternalFormat = GL_RG32F;
        break;
    case 3:
        Format = GL_RGB;
        InternalFormat = GL_RGB32F;
        break;
    case 4:
        Format = GL_RGBA;
        InternalFormat = GL_RGBA32F;
        break;
    
    default:
        std::stringstream ss;
        ss << "Number of channels must be at least 1 and at most 4. Given " << NumChannels << '.';
        throw std::runtime_error(ss.str());
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, GL_FLOAT, NULL);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}


render::Texture::Texture(const std::string& Filename)
{
    int NumChannels;
    unsigned char* img = stbi_load(Filename.c_str(), &Width, &Height, &NumChannels, 0);
    if (img == nullptr)
    {
        std::stringstream ss;
        ss << "Cannot read image from file " << Filename;
        throw std::runtime_error(ss.str());
    }

    GLenum Format, InternalFormat;
    switch (NumChannels)
    {
    case 1:
        Format = GL_RED;
        InternalFormat = GL_R32F;
        break;
    case 2:
        Format = GL_RG;
        InternalFormat = GL_RG32F;
        break;
    case 3:
        Format = GL_RGB;
        InternalFormat = GL_RGB32F;
        break;
    case 4:
        Format = GL_RGBA;
        InternalFormat = GL_RGBA32F;
        break;
    
    default:
        std::stringstream ss;
        ss << "Number of channels must be at least 1 and at most 4. Given " << NumChannels << '.';
        throw std::runtime_error(ss.str());
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);


    free(img);
}


render::Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}


int render::Texture::GetNumChannels() const
{
    switch (Format)
    {
    case GL_RED:    return 1;
    case GL_RG:     return 2;
    case GL_RGB:    return 3;
    case GL_RGBA:   return 4;
    }
    return -1;
}

void render::Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void render::Texture::Bind(int Unit) const
{
    glActiveTexture(GL_TEXTURE0 + Unit);
    Bind();
}

void render::Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void render::Texture::Unbind(int Unit) const
{
    glActiveTexture(GL_TEXTURE0 + Unit);
    Unbind();
}


void render::Texture::GetImage(float* Img) const
{
    Bind();
    glGetTexImage(GL_TEXTURE_2D, 0, Format, GL_FLOAT, Img);
    Unbind();
}

void render::Texture::GetImage(unsigned char* Img) const
{
    Bind();
    glGetTexImage(GL_TEXTURE_2D, 0, Format, GL_UNSIGNED_BYTE, Img);
    Unbind();
}

void render::Texture::SetImage(const float* Img)
{
    GLenum InternalFormat;
    switch (Format)
    {
    case GL_RED:    InternalFormat = GL_R32F; break;
    case GL_RG:     InternalFormat = GL_RG32F; break;
    case GL_RGB:    InternalFormat = GL_RGB32F; break;
    case GL_RGBA:   InternalFormat = GL_RGBA32F; break;
    
    default:
        std::stringstream ss;
        ss << "Only accepted formats for textures are:" << std::endl;
        ss << "  - GL_RED" << std::endl;
        ss << "  - GL_RG" << std::endl;
        ss << "  - GL_RGB" << std::endl;
        ss << "  - GL_RGBA" << std::endl;
        throw std::runtime_error(ss.str());
    }
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, GL_FLOAT, Img);
}

void render::Texture::SetImage(const unsigned char* Img)
{
    GLenum InternalFormat;
    switch (Format)
    {
    case GL_RED:    InternalFormat = GL_R32F; break;
    case GL_RG:     InternalFormat = GL_RG32F; break;
    case GL_RGB:    InternalFormat = GL_RGB32F; break;
    case GL_RGBA:   InternalFormat = GL_RGBA32F; break;
    
    default:
        std::stringstream ss;
        ss << "Only accepted formats for textures are:" << std::endl;
        ss << "  - GL_RED" << std::endl;
        ss << "  - GL_RG" << std::endl;
        ss << "  - GL_RGB" << std::endl;
        ss << "  - GL_RGBA" << std::endl;
        throw std::runtime_error(ss.str());
    }
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Img);
}