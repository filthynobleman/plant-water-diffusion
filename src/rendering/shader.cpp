/**
 * @file        shader.cpp
 * 
 * @brief       Implements the shader part of shader.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-30
 */
#include <rendering/shader.hpp>
#include <sstream>
#include <stb_include.h>
#include <glm/gtc/type_ptr.hpp>

#define SHADER_INCLUDE_PATH "../shaders/"



void render::Shader::CheckCompileErrors(GLuint SID, GLenum SType)
{
    int Success;
    char Log[4096];

    glGetShaderiv(SID, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {
        glGetShaderInfoLog(SID, 4096, NULL, Log);
        std::stringstream ss;
        ss << "Error occured while compiling ";
        if (SType == GL_VERTEX_SHADER)
            ss << "vertex";
        else
            ss << "fragment";
        ss << "shader. Error log:" << std::endl;
        ss << Log;
        throw std::runtime_error(ss.str());
    }
}

void render::Shader::CheckLinkErrors()
{
    int Success;
    char Log[4096];

    glGetProgramiv(m_PID, GL_LINK_STATUS, &Success);
    if (!Success)
    {
        glGetProgramInfoLog(m_PID, 4096, NULL, Log);
        std::stringstream ss;
        ss << "Error occurred while linking program, Error log:" << std::endl;
        ss << Log;
        throw std::runtime_error(ss.str());
    }
}

render::Shader::Shader(const std::string& Vert, const std::string& Frag)
{
    char Error[256];
    
    // Read vertex shader
    char* VSource = stb_include_file((char*)(Vert.c_str()), NULL, SHADER_INCLUDE_PATH, Error);
    if (VSource == nullptr)
    {
        std::stringstream ss;
        ss << "Cannot open vertex shader " << Vert << ". Error log:" << std::endl;
        ss << Error;
        throw std::runtime_error(ss.str());
    }
    m_VSource = std::string(VSource);
    free(VSource);

    // Read fragment shader
    char* FSource = stb_include_file((char*)(Frag.c_str()), NULL, SHADER_INCLUDE_PATH, Error);
    if (FSource == nullptr)
    {
        std::stringstream ss;
        ss << "Cannot open fragment shader " << Frag << ". Error log:" << std::endl;
        ss << Error;
        throw std::runtime_error(ss.str());
    }
    m_FSource = std::string(FSource);
    free(FSource);

    // Initialize PID to zero
    m_PID = 0;
}

render::Shader::~Shader()
{
    if (m_PID != 0)
        glDeleteProgram(m_PID);
}


void render::Shader::Compile()
{
    GLuint VID, FID;
    const char* VSource = m_VSource.c_str();
    const char* FSource = m_FSource.c_str();

    VID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VID, 1, &VSource, NULL);
    glCompileShader(VID);
    CheckCompileErrors(VID, GL_VERTEX_SHADER);

    FID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FID, 1, &FSource, NULL);
    glCompileShader(FID);
    CheckCompileErrors(FID, GL_FRAGMENT_SHADER);

    m_PID = glCreateProgram();
    glAttachShader(m_PID, VID);
    glAttachShader(m_PID, FID);
    glLinkProgram(m_PID);
    CheckLinkErrors();

    glDeleteShader(VID);
    glDeleteShader(FID);
}

void render::Shader::Use() const
{
    if (m_PID == 0) return;
    glUseProgram(m_PID);
}


void render::Shader::SendInt(const std::string& Name, int Value)
{
    int Loc = glGetUniformLocation(m_PID, Name.c_str());
    if (Loc < 0)
    {
        std::stringstream ss;
        ss << "Cannot find attribute " << Name << " in shader.";
        throw std::runtime_error(ss.str());
    }
    glUniform1i(Loc, Value);
}

void render::Shader::SendBool(const std::string& Name, bool Value)
{
    int Loc = glGetUniformLocation(m_PID, Name.c_str());
    if (Loc < 0)
    {
        std::stringstream ss;
        ss << "Cannot find attribute " << Name << " in shader.";
        throw std::runtime_error(ss.str());
    }
    glUniform1i(Loc, Value);
}

void render::Shader::SendFloat(const std::string& Name, float Value)
{
    int Loc = glGetUniformLocation(m_PID, Name.c_str());
    if (Loc < 0)
    {
        std::stringstream ss;
        ss << "Cannot find attribute " << Name << " in shader.";
        throw std::runtime_error(ss.str());
    }
    glUniform1f(Loc, Value);
}


void render::Shader::SendVec2(const std::string& Name, const glm::vec2& Value)
{
    int Loc = glGetUniformLocation(m_PID, Name.c_str());
    if (Loc < 0)
    {
        std::stringstream ss;
        ss << "Cannot find attribute " << Name << " in shader.";
        throw std::runtime_error(ss.str());
    }
    glUniform2fv(Loc, 1, glm::value_ptr(Value));
}

void render::Shader::SendVec3(const std::string& Name, const glm::vec3& Value)
{
    int Loc = glGetUniformLocation(m_PID, Name.c_str());
    if (Loc < 0)
    {
        std::stringstream ss;
        ss << "Cannot find attribute " << Name << " in shader.";
        throw std::runtime_error(ss.str());
    }
    glUniform3fv(Loc, 1, glm::value_ptr(Value));
}

void render::Shader::SendVec4(const std::string& Name, const glm::vec4& Value)
{
    int Loc = glGetUniformLocation(m_PID, Name.c_str());
    if (Loc < 0)
    {
        std::stringstream ss;
        ss << "Cannot find attribute " << Name << " in shader.";
        throw std::runtime_error(ss.str());
    }
    glUniform4fv(Loc, 1, glm::value_ptr(Value));
}



void render::Shader::SendMat2(const std::string& Name, const glm::mat2& Value)
{
    int Loc = glGetUniformLocation(m_PID, Name.c_str());
    if (Loc < 0)
    {
        std::stringstream ss;
        ss << "Cannot find attribute " << Name << " in shader.";
        throw std::runtime_error(ss.str());
    }
    glUniformMatrix2fv(Loc, 1, GL_FALSE, glm::value_ptr(Value));
}

void render::Shader::SendMat3(const std::string& Name, const glm::mat3& Value)
{
    int Loc = glGetUniformLocation(m_PID, Name.c_str());
    if (Loc < 0)
    {
        std::stringstream ss;
        ss << "Cannot find attribute " << Name << " in shader.";
        throw std::runtime_error(ss.str());
    }
    glUniformMatrix3fv(Loc, 1, GL_FALSE, glm::value_ptr(Value));
}

void render::Shader::SendMat4(const std::string& Name, const glm::mat4& Value)
{
    int Loc = glGetUniformLocation(m_PID, Name.c_str());
    if (Loc < 0)
    {
        std::stringstream ss;
        ss << "Cannot find attribute " << Name << " in shader.";
        throw std::runtime_error(ss.str());
    }
    glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(Value));
}



void render::Shader::SendLight(const std::string& Name, const render::Light& Value)
{
    SendVec3(Name + ".Position", Value.Position);
    SendVec3(Name + ".Ambient", Value.Ambient);
    SendVec3(Name + ".Diffuse", Value.Diffuse);
    SendVec3(Name + ".Specular", Value.Specular);
}

void render::Shader::SendMaterial(const std::string& Name, const render::Material& Value)
{
    SendVec3(Name + ".Ambient", Value.Ambient);
    SendVec3(Name + ".Diffuse", Value.Diffuse);
    SendVec3(Name + ".Specular", Value.Specular);
    SendFloat(Name + ".Shininess", Value.Shininess);
}