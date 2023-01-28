/**
 * @file        uimanager.cpp
 * 
 * @brief       Implements uimanager.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-11-01
 */
#include <ui/uimanager.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <rendering/window.hpp>

ui::UIManager::UIManager(render::Window* Window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Window->m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");

    // Load Font
    io.Fonts->AddFontFromFileTTF("../ext/imgui/misc/fonts/Roboto-Medium.ttf", 20.0f);
}

ui::UIManager::~UIManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void ui::UIManager::AttachComponent(const std::string& Name, 
                                    ui::UIComponent& Component)
{
    assert(m_Components.find(Name) == m_Components.end());

    m_Components.insert({ Name, Component });
}

void ui::UIManager::AttachComponent(ui::UIComponent& Component)
{
    assert(m_Components.find(Component.GetName()) == m_Components.end());

    m_Components.insert({ Component.GetName(), Component });
}

void ui::UIManager::RemoveComponent(const std::string& Name)
{
    assert(m_Components.find(Name) != m_Components.end());

    m_Components.erase(Name);
}

const ui::UIComponent& ui::UIManager::GetComponent(const std::string& Name) const
{
    assert(m_Components.find(Name) != m_Components.end());

    return m_Components.find(Name)->second;
}

ui::UIComponent& ui::UIManager::GetComponent(const std::string& Name)
{
    assert(m_Components.find(Name) != m_Components.end());

    return m_Components.find(Name)->second;
}


#include <iostream>

void ui::UIManager::Draw() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    std::unordered_map<std::string, ui::UIComponent&>::const_iterator it;
    for (it = m_Components.begin(); it != m_Components.end(); it++)
    {
        it->second.DrawWidget();
        // std::cout << it->first << std::endl;
    }
    // std::cout << std::endl;

    ImGui::Render();
}