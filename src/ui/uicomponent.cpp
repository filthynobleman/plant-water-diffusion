/**
 * @file        uicomponent.cpp
 * 
 * @brief       Implements uicomponent.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-11-01
 */
#include <ui/uicomponent.hpp>
#include <imgui.h>

ui::UIComponent::UIComponent(const std::string& Name, 
                             unsigned int PosX,
                             unsigned int PosY,
                             unsigned int SizeX,
                             unsigned int SizeY) 
    : m_Name(Name), m_PosX(PosX), m_PosY(PosY), m_SizeX(SizeX), m_SizeY(SizeY)
{ }
ui::UIComponent::~UIComponent() { }

std::string ui::UIComponent::GetName() const { return m_Name; }
void ui::UIComponent::SetName(const std::string& Name) { m_Name = Name; }

void ui::UIComponent::DrawWidget()
{
    ImGui::SetNextWindowPos(ImVec2(m_PosX, m_PosY));
    ImGui::SetNextWindowSize(ImVec2(m_SizeX, m_SizeY));
    ImGui::Begin(GetName().c_str(), nullptr, ImGuiCond_FirstUseEver |
                                             ImGuiWindowFlags_NoResize |
                                             ImGuiWindowFlags_NoMove |
                                             ImGuiWindowFlags_NoCollapse);

    Draw();

    ImGui::End();
}