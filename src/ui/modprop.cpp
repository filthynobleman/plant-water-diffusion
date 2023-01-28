/**
 * @file        modprop.cpp
 * 
 * @brief       Implements modprop.hpp.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2022-11-07
 */
#include <ui/modprop.hpp>
#include <imgui.h>


ui::ModelProperties::ModelProperties(const std::string& Name, 
                                     render::Model* Model,
                                     unsigned int PosX,
                                     unsigned int PosY,
                                     unsigned int SizeX,
                                     unsigned int SizeY)
    : ui::UIComponent(Name, PosX, PosY, SizeX, SizeY), 
      m_Model(Model), m_CurScale(1.0f), m_Updated(false)
{ 
    m_CurScale = Model->Transform().GetScale().x;

    m_Material.Ambient = glm::vec3(0.1f, 0.1f, 0.3f);
    m_Material.Diffuse = glm::vec3(0.5f, 0.5f, 0.7f);
    m_Material.Specular = glm::vec3(0.1f, 0.1f, 0.1f);
    m_Material.Shininess = 1.0f;
}

ui::ModelProperties::~ModelProperties() { }

const render::Material& ui::ModelProperties::GetMaterial() const { return m_Material; }

void ui::ModelProperties::Draw()
{
    float NewScale = m_CurScale;
    ImGui::InputFloat("Model Scale", &NewScale);
    if (NewScale != m_CurScale)
    {
        m_CurScale = NewScale;
        m_Updated = true;
    }

    ImGui::Text("Material");
    ImGui::InputFloat3("Ambient", (float*)(&(m_Material.Ambient)));
    ImGui::InputFloat3("Diffuse", (float*)(&(m_Material.Diffuse)));
    ImGui::InputFloat3("Specular", (float*)(&(m_Material.Specular)));
    ImGui::InputFloat("Shininess", &(m_Material.Shininess));

    if (m_Updated)
    {
        m_Model->Transform().SetScale(NewScale);
        m_Updated = false;
    }
}