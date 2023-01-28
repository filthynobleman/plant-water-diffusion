/**
 * @file        model.hpp
 * 
 * @brief       Declaration of class Model.
 * 
 * @details     This file contains the declaration of the class Model.\n 
 *              This class represents a 3D model, and provides methods for
 *              easy interaction with OpenGL routines.
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

#include <rendering/transform.hpp>
#include <rendering/camera.hpp>
#include <rendering/shader.hpp>
#include <io/mesh.hpp>

#include <vector>

namespace render
{

/**
 * @brief       A data structure representing a vertex of a model.
 * 
 * @details     This data structure contains all the informations for representing
 *              a vertex of a 3D model.\n 
 *              The structure encodes informations about the position in 3D space of
 *              a vertex, the coordinates in parametric space of the corrsponding
 *              UV vertex and the surface normal at that point.
 */
struct Vertex
{
    glm::vec3 Position;
    glm::vec2 UV;
    glm::vec3 Normal;

    Vertex(const glm::vec3& Position, const glm::vec2& UV, const glm::vec3& Normal);
    Vertex(const Vertex& Vert);
    Vertex& operator=(const Vertex& Vert);
    ~Vertex();

    float operator[](int i) const;
    float& operator[](int i);

    float operator()(int i) const;
    float& operator()(int i);
};

    
/**
 * @brief       A class representing a 3D model.
 * 
 * @details     This class represents a 3D model for OpenGL rendering.\n
 *              A Model object is created starting from the content in an
 *              io::Mesh.
 */
class Model
{
private:
    Transform               m_Trans;
    std::vector<Vertex>     m_Verts;
    std::vector<glm::ivec3> m_Tris;

    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;

    Shader* m_Shader;

    void InitWithNormals(const io::Mesh& Mesh);
    void InitWithoutNormals(const io::Mesh& Mesh);

public:
    Model(const io::Mesh& Mesh, 
          const std::string& VertShader = "../shaders/default.vert",
          const std::string& FragShader = "../shaders/default.frag");
    ~Model();

    Shader& Shader();
    Transform& Transform();
    void Bind();
    void Unbind();
    void Draw(const Camera& Cam);
    void Draw(const Camera& Cam, const render::Transform& RelativeTo);
};


} // namespace render
