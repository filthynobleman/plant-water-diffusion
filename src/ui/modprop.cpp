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
                                     render::Transform* Transform,
                                     unsigned int PosX,
                                     unsigned int PosY,
                                     unsigned int SizeX,
                                     unsigned int SizeY)
    : ui::UIComponent(Name, PosX, PosY, SizeX, SizeY), 
      m_Transform(Transform), m_Updated(false)
{ 
    m_Material.Ambient = glm::vec3(0.1f, 0.1f, 0.3f);
    m_Material.Diffuse = glm::vec3(0.5f, 0.5f, 0.7f);
    m_Material.Specular = glm::vec3(0.1f, 0.1f, 0.1f);
    m_Material.Shininess = 1.0f;
}

ui::ModelProperties::~ModelProperties() { }

const render::Material& ui::ModelProperties::GetMaterial() const { return m_Material; }

void ui::ModelProperties::Draw()
{
    float NewScale = m_Transform->GetScale().x;
    glm::vec3 NewPos = m_Transform->GetPosition();
    glm::vec3 NewRot = m_Transform->GetEulerAngle();

    ImGui::Text("Transform");
    ImGui::InputFloat3("Model Position", (float*)&NewPos);
    if (m_Transform->GetPosition() != NewPos)
        m_Updated = true;
    ImGui::InputFloat3("Model Rotation", (float*)&NewRot);
    if (m_Transform->GetEulerAngle() != NewRot)
        m_Updated = true;
    ImGui::InputFloat("Model Scale", &NewScale);
    if (NewScale != m_Transform->GetScale().x)
        m_Updated = true;

    ImGui::Text("Material");
    ImGui::ColorEdit3("Ambient", (float*)(&(m_Material.Ambient)), ImGuiColorEditFlags_PickerHueWheel);
    ImGui::ColorEdit3("Diffuse", (float*)(&(m_Material.Diffuse)), ImGuiColorEditFlags_PickerHueWheel);
    ImGui::ColorEdit3("Specular", (float*)(&(m_Material.Specular)), ImGuiColorEditFlags_PickerHueWheel);
    ImGui::InputFloat("Shininess", &(m_Material.Shininess));

    if (m_Updated)
    {
        m_Transform->SetPosition(NewPos);
        m_Transform->SetRotation(NewRot);
        m_Transform->SetScale(NewScale);
        m_Updated = false;
    }
}