/**
 * @file        colmapprop.cpp
 * 
 * @brief       Implements ColormapProperties.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-02-07
 */
#include <ui/colmapprop.hpp>
#include <imgui.h>


ui::ColormapProperties::ColormapProperties(const std::string& Name, 
                                           unsigned int PosX,
                                           unsigned int PosY,
                                           unsigned int SizeX,
                                           unsigned int SizeY)
    : ui::UIComponent(Name, PosX, PosY, SizeX, SizeY)
{
    m_Values.push_back(0.0f);
    m_Values.push_back(0.2f);
    m_Values.push_back(0.4f);
    m_Values.push_back(0.6f);
    m_Values.push_back(0.8f);
    m_Values.push_back(1.0f);

    m_Colors.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    m_Colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    m_Colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
    m_Colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    m_Colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
    m_Colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
}


ui::ColormapProperties::~ColormapProperties() { }


#include <iostream>

glm::vec3 ui::ColormapProperties::GetColor(float t) const
{
    t = glm::clamp(t, 0.0f, 1.0f);
    size_t Idx;
    for (Idx = 0; Idx < m_Values.size() - 1; ++Idx)
    {
        if (t >= m_Values[Idx] && t < m_Values[Idx + 1])
            break;
    }
    if (Idx == m_Values.size() - 1)
        return m_Colors[Idx];

    t -= m_Values[Idx];
    t /= (m_Values[Idx + 1] - m_Values[Idx]);
    glm::vec3 Left = (1 - t) * m_Colors[Idx];
    glm::vec3 Right = t * m_Colors[Idx + 1];    
    // return glm::sqrt(Left * Left + Right * Right);
    return Left + Right;
}


void ui::ColormapProperties::Draw()
{
    for (int i = 0; i < m_Values.size(); ++i)
    {
        ImGui::PushID(i);

        ImGui::ColorEdit3("Color", (float*)&m_Colors[i], ImGuiColorEditFlags_PickerHueWheel);

        if (i == 0 || i == m_Values.size() - 1)
        {
            ImGui::InputFloat("Value", &m_Values[i], 0.0f, 0.0f, "%.2e", ImGuiInputTextFlags_ReadOnly);
        }
        else
        {
            ImGui::InputFloat("Value", &m_Values[i], 0.0f, 0.0f, "%.2e");
            m_Values[i] = glm::clamp(m_Values[i], m_Values[i - 1] + 1e-9f, m_Values[i + 1] - 1e-9f);
        }

        ImGui::PopID();
    }
}