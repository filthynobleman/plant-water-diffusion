/**
 * @file        model.cpp
 * 
 * @brief       Implements model.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-31
 */
#include <rendering/model.hpp>
#include <unordered_map>
#include <glm/gtx/hash.hpp>





render::Model::Model(const io::Mesh& Mesh,
                     const std::string& VertShader,
                     const std::string& FragShader)
{
    if (Mesh.NormalsTri.size() == 0)
        InitWithoutNormals(Mesh);
    else
        InitWithNormals(Mesh);

    
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 m_Verts.size() * sizeof(render::Vertex),
                 m_Verts.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(glm::ivec3) * m_Tris.size(),
                 m_Tris.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 
                          3, 
                          GL_FLOAT, 
                          GL_FALSE, 
                          sizeof(render::Vertex),
                          (void*)offsetof(render::Vertex, Position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,
                          2,
                          GL_FLOAT,
                          GL_FALSE, 
                          sizeof(render::Vertex),
                          (void*)offsetof(render::Vertex, UV));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(render::Vertex),
                          (void*)offsetof(render::Vertex, Normal));
    glEnableVertexAttribArray(2);

    Unbind();


    m_Shader = new render::Shader(VertShader, FragShader);
    assert(m_Shader != nullptr);
    Shader().Compile();
}


render::Model::~Model()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_VBO);

    delete m_Shader;
}


render::Shader& render::Model::Shader() { return *m_Shader; }
render::Transform& render::Model::Transform() { return m_Trans; }

void render::Model::Bind() { glBindVertexArray(m_VAO); }
void render::Model::Unbind() { glBindVertexArray(0); }

void render::Model::Draw(const render::Camera& Camera)
{
    glm::mat4 Model = Transform().GetTransformationMatrix();
    glm::mat3 ModelInv = glm::mat3(glm::inverse(glm::transpose(Model)));
    glm::mat4 View = Camera.GetViewMatrix();
    glm::mat4 Proj = Camera.GetProjectionMatrix();

    Shader().Use();
    Shader().SendMat4("Model", Model);
    Shader().SendMat3("ModelInv", ModelInv);
    Shader().SendMat4("View", View);
    Shader().SendMat4("Projection", Proj);
    Bind();
    glDrawElements(GL_TRIANGLES, 3 * m_Tris.size(), GL_UNSIGNED_INT, 0);
    Unbind();
}

void render::Model::Draw(const render::Camera& Camera, const render::Transform& RelativeTo)
{
    glm::mat4 Model = Transform().GetTransformationMatrix();
    Model = RelativeTo.GetTransformationMatrix() * Model;
    glm::mat3 ModelInv = glm::mat3(glm::inverse(glm::transpose(Model)));
    glm::mat4 View = Camera.GetViewMatrix();
    glm::mat4 Proj = Camera.GetProjectionMatrix();

    Shader().Use();
    Shader().SendMat4("Model", Model);
    Shader().SendMat3("ModelInv", ModelInv);
    Shader().SendMat4("View", View);
    Shader().SendMat4("Projection", Proj);
    Bind();
    glDrawElements(GL_TRIANGLES, 3 * m_Tris.size(), GL_UNSIGNED_INT, 0);
    Unbind();
}


void render::Model::InitWithNormals(const io::Mesh& Mesh)
{
    // Each vertex uniquely identified by its position, UV and normal
    std::unordered_map<glm::ivec3, int> VUnique;
    for (int i = 0; i < Mesh.NTris(); ++i)
    {
        glm::ivec3 Tri;
        for (int j = 0; j < 3; ++j)
        {
            glm::ivec3 VData;
            VData.x = Mesh.Verts3DTri[i][j];
            VData.y = Mesh.VertsUVTri[i][j];
            VData.z = Mesh.NormalsTri[i][j];

            if (VUnique.find(VData) == VUnique.end())
                VUnique.insert({ VData, VUnique.size() });
            
            Tri[j] = VUnique[VData];
        }
        m_Tris.push_back(Tri);
    }

    // Create array of dummy vertices
    for (int i = 0; i < VUnique.size(); ++i)
        m_Verts.push_back(render::Vertex(glm::vec3(0), glm::vec2(0), glm::vec3(0)));
    // Fill the array with proper data
    std::unordered_map<glm::ivec3, int>::const_iterator it;
    for (it = VUnique.begin(); it != VUnique.end(); it++)
    {
        glm::ivec3 VData = it->first;
        Eigen::Vector3d EPos = Mesh.Verts3D[VData.x];
        Eigen::Vector2d EUV = Mesh.VertsUV[VData.y];
        Eigen::Vector3d ENorm = Mesh.Normals[VData.z]; 
        glm::vec3 Pos(EPos[0], EPos[1], EPos[2]);
        glm::vec2 UV(EUV[0], EUV[1]);
        glm::vec3 Norm(ENorm[0], ENorm[1], ENorm[2]);
        m_Verts[it->second] = { Pos, UV, Norm };
    }
}


void render::Model::InitWithoutNormals(const io::Mesh& Mesh)
{
    // First, compute normal for each triangle
    std::vector<Eigen::Vector3d> TriNorms;
    for (int i = 0; i < Mesh.NTris(); ++i)
    {
        // Get vertices
        Eigen::Vector3d V[3];
        for (int j = 0; j < 3; ++j)
            V[j] = Mesh.Verts3D[Mesh.Verts3DTri[i][j]];
        // Compute edges
        Eigen::Vector3d E[3];
        for (int j = 0; j < 3; ++j)
            E[j] = V[(j + 1) % 3] - V[j];
        // Compute normal
        Eigen::Vector3d N(0.0, 0.0, 0.0);
        for (int j = 0; j < 3; ++j)
            N += E[j].cross(E[(j + 1) % 3]);
        TriNorms.push_back(N.normalized());
    }

    // Each vertex uniquely identified by its position and UV
    std::unordered_map<glm::ivec2, int> VUnique;
    for (int i = 0; i < Mesh.NTris(); ++i)
    {
        glm::ivec3 Tri;
        for (int j = 0; j < 3; ++j)
        {
            glm::ivec2 VData;
            VData.x = Mesh.Verts3DTri[i][j];
            VData.y = Mesh.VertsUVTri[i][j];

            if (VUnique.find(VData) == VUnique.end())
                VUnique.insert({ VData, VUnique.size() });
            
            Tri[j] = VUnique[VData];
        }
        m_Tris.push_back(Tri);
    }

    // Create array of vertex normals
    std::vector<Eigen::Vector3d> VertNorms(VUnique.size(), Eigen::Vector3d(0.0, 0.0, 0.0));
    // Each triangle contributes with its normal to adjacent vertices
    for (int i = 0; i < Mesh.NTris(); ++i)
    {
        for (int j = 0; j < 3; ++j)
            VertNorms[Mesh.Verts3DTri[i][j]] += TriNorms[i];
    }
    // Normalize
    for (int i = 0; i < VertNorms.size(); ++i)
        VertNorms[i].normalize();

    // Create array of dummy vertices
    for (int i = 0; i < VUnique.size(); ++i)
        m_Verts.push_back(render::Vertex(glm::vec3(0), glm::vec2(0), glm::vec3(0)));
    // Fill the array with proper data
    std::unordered_map<glm::ivec2, int>::const_iterator it;
    for (it = VUnique.begin(); it != VUnique.end(); it++)
    {
        glm::ivec2 VData = it->first;
        Eigen::Vector3d EPos = Mesh.Verts3D[VData.x];
        Eigen::Vector2d EUV = Mesh.VertsUV[VData.y];
        Eigen::Vector3d ENorm = VertNorms[it->second];
        glm::vec3 Pos(EPos[0], EPos[1], EPos[2]);
        glm::vec2 UV(EUV[0], EUV[1]);
        glm::vec3 Norm(ENorm[0], ENorm[1], ENorm[2]);
        m_Verts[it->second] = { Pos, UV, Norm };
    }
}