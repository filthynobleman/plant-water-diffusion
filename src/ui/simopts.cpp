/**
 * @file        simopts.cpp
 * 
 * @brief       Implements simopts.hpp.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2022-11-07
 */
#include <ui/simopts.hpp>
#include <imgui.h>


ui::SimulationOptions::SimulationOptions(const std::string& Name, 
                                         unsigned int PosX,
                                         unsigned int PosY,
                                         unsigned int SizeX,
                                         unsigned int SizeY)
    : ui::UIComponent(Name, PosX, PosY, SizeX, SizeY), 
      m_MoveSpeed(1.0f), m_RotSpeed(1.0f), m_Paused(true)
{

}

ui::SimulationOptions::~SimulationOptions() { }

float ui::SimulationOptions::GetMoveSpeed() const   { return m_MoveSpeed; }
float ui::SimulationOptions::GetRotSpeed() const    { return m_RotSpeed; }
bool ui::SimulationOptions::IsPaused() const        { return m_Paused; }

void ui::SimulationOptions::Draw()
{
    // Simulation pause/start
    if (ImGui::Button("Run")) 
        m_Paused = false;
    ImGui::SameLine();
    if (ImGui::Button("Pause"))
        m_Paused = true;

    // Agent movement and rotation speed
    ImGui::InputFloat("Move Speed", &m_MoveSpeed);
    ImGui::InputFloat("Rot Speed", &m_RotSpeed);
}