/**
 * @file        lightprop.cpp
 * 
 * @brief       Implements lightptop.hpp.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2022-11-07
 */
#include <ui/lightprop.hpp>
#include <imgui.h>

ui::LightProperties::LightProperties(const std::string& Name, 
                                     unsigned int PosX,
                                     unsigned int PosY,
                                     unsigned int SizeX,
                                     unsigned int SizeY)
    : ui::UIComponent(Name, PosX, PosY, SizeX, SizeY)
{
    m_Light.Position = glm::vec3(15.0f, 15.0f, -15.0f);
    m_Light.Ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    m_Light.Diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    m_Light.Specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

ui::LightProperties::~LightProperties() { }

const render::Light& ui::LightProperties::GetLight() const { return m_Light; }


void ui::LightProperties::Draw()
{
    ImGui::InputFloat3("Position", (float*)(&(m_Light.Position)));
    ImGui::ColorEdit3("Ambient", (float*)(&(m_Light.Ambient)));
    ImGui::ColorEdit3("Diffuse", (float*)(&(m_Light.Diffuse)));
    ImGui::ColorEdit3("Specular", (float*)(&(m_Light.Specular)));
}