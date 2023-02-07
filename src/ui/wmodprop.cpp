/**
 * @file        wmodprop.cpp
 * 
 * @brief       Implements WaterModelProperties.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-02-07
 */
#include <ui/wmodprop.hpp>
#include <imgui.h>


ui::WaterModelProperties::WaterModelProperties(const std::string& Name,
                                               int PosX, int PosY,
                                               int SizeX, int SizeY)
    : ui::UIComponent(Name, PosX, PosY, SizeX, SizeY)
{
    m_InitialWater = 4;
    m_LossRate = 3e-1;
    m_Time = 0.0;
    m_TimeStep = 0.1;
}

ui::WaterModelProperties::~WaterModelProperties() { }


double ui::WaterModelProperties::GetInitialWater() const { return m_InitialWater; }
double ui::WaterModelProperties::GetLossRate() const { return m_LossRate; }
double ui::WaterModelProperties::GetTime() const { return m_Time; }
double ui::WaterModelProperties::GetTimeStep() const { return m_TimeStep; }
bool ui::WaterModelProperties::IsPaused() const { return m_IsPaused; }
bool ui::WaterModelProperties::IsReset() const { return m_IsReset; }

void ui::WaterModelProperties::Pause() { m_IsPaused = !m_IsPaused; }


void ui::WaterModelProperties::Draw()
{
    ImGui::InputDouble("Initial Water", &m_InitialWater);
    ImGui::InputDouble("Loss Rate", &m_LossRate);
    ImGui::InputDouble("Time Step", &m_TimeStep);
    ImGui::InputDouble("Time", &m_Time);
    ImGui::Checkbox("Paused", &m_IsPaused);
    m_IsReset = ImGui::Button("Reset");
    if (m_IsReset)
    {
        m_Time = 0.0;
        m_IsPaused = true;
    }

    m_InitialWater = std::max(m_InitialWater, 0.0);
    m_LossRate = std::max(m_LossRate, 0.0);
    m_TimeStep = std::max(m_TimeStep, 0.0);
    m_Time = std::max(m_Time, 0.0);

    if (!m_IsPaused)
        m_Time += m_TimeStep;
}