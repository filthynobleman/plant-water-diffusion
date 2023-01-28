/**
 * @file        camprop.cpp
 * 
 * @brief       Implements camprop.hpp.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2022-11-07
 */
#include <ui/camprop.hpp>
#include <imgui.h>
#include <iostream>


ui::CameraProperties::CameraProperties(const std::string& Name, 
                                       unsigned int PosX,
                                       unsigned int PosY,
                                       unsigned int SizeX,
                                       unsigned int SizeY)
    : ui::UIComponent(Name, PosX, PosY, SizeX, SizeY), 
      m_MoveSpeed(5.0f), m_RotSpeed(20.0f), m_Multiplier(2.0f)
{ }

ui::CameraProperties::~CameraProperties() { }

float ui::CameraProperties::GetMoveSpeed() const        { return m_MoveSpeed; }
float ui::CameraProperties::GetRotSpeed() const         { return m_RotSpeed; }
float ui::CameraProperties::GetSpeedMultiplier() const  { return m_Multiplier; }

void ui::CameraProperties::Draw()
{
    ImGui::InputFloat("Move Speed", &m_MoveSpeed);
    ImGui::InputFloat("Rot Speed", &m_RotSpeed);
    ImGui::InputFloat("Sprint Factor", &m_Multiplier);
}