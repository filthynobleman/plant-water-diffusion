/**
 * @file        shader.hpp
 * 
 * @brief       Declaration of a class Shader.
 * 
 * @details     This file contains the declaration of the class Shader.\n 
 *              This class represents a graphic shader for OpenGL and wraps
 *              some basic functionalities like compilation and sending
 *              uniforms.\n 
 *              The file also contains the definition of data structures for
 *              representing lights, materials and textures.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-30
 */
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

namespace render
{

/**
 * @brief       Data structure representing a light.
 * 
 * @details     This data structure encodes a very basic point light.
 */
struct Light
{
    glm::vec3 Position;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
};

/**
 * @brief       Data structure representing a material.
 * 
 * @details     This data structure encodes a very basic material.
 */
struct Material
{
    glm::vec3   Ambient;
    glm::vec3   Diffuse;
    glm::vec3   Specular;
    float       Shininess;
};


/**
 * @brief       Data structure representing a texture.
 * 
 * @details     This data structure represents a texture.\n 
 *              The structure contains informations about OpenGL location of the
 *              texture, its dimensions and the format (i.e. the channels).\n 
 *              Also, a set of methods for basic interactions are provided.
 */
struct Texture
{
    GLuint  ID;
    int     Width;
    int     Height;
    GLenum  Format;

    Texture(int Width, int Height, GLenum Format);
    Texture(int Width, int Height, int NumChannels);
    Texture(const std::string& Filename);
    ~Texture();

    int GetNumChannels() const;

    void Bind() const;
    void Bind(int Unit) const;
    void Unbind() const;
    void Unbind(int Unit) const;

    void GetImage(float* Img) const;
    void GetImage(unsigned char* Img) const;
    void SetImage(const float* Img);
    void SetImage(const unsigned char* Img);
};



/**
 * @brief       Class representing a graphics shader.
 * 
 * @details     This class represents a graphic shader.\n 
 *              The class offers methods for handling basic OpenGL functionalities
 *              on shaders, like compilation and management of uniform variables.
 */
class Shader
{
private:
    std::string m_VSource;
    std::string m_FSource;
    GLuint      m_PID;
    
    void CheckCompileErrors(GLuint SID, GLenum SType);
    void CheckLinkErrors();

public:
    Shader(const std::string& Vert, const std::string& Frag);
    ~Shader();

    void Compile();
    void Use() const;


    void SendInt(const std::string& Name, int Value);
    void SendBool(const std::string& Name, bool Value);
    void SendFloat(const std::string& Name, float Value);

    void SendVec2(const std::string& Name, const glm::vec2& Value);
    void SendVec3(const std::string& Name, const glm::vec3& Value);
    void SendVec4(const std::string& Name, const glm::vec4& Value);

    void SendMat2(const std::string& Name, const glm::mat2& Value);
    void SendMat3(const std::string& Name, const glm::mat3& Value);
    void SendMat4(const std::string& Name, const glm::mat4& Value);

    void SendLight(const std::string& Name, const Light& Value);
    void SendMaterial(const std::string& Name, const Material& Value);

};





} // namespace render
