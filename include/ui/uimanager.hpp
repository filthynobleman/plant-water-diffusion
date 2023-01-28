/**
 * @file        uimanager.hpp
 * 
 * @brief       Declaration of class UIManager.
 * 
 * @details     This file contains the declaration of the class UIManager.\n 
 *              The UIManager wraps the ImGui backend and is resposnsible for
 *              handling the UIComponents that form the whole interface of
 *              the application.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-11-01
 */
#pragma once

#include <ui/uicomponent.hpp>
#include <unordered_map>

namespace render { class Window; }

namespace ui
{
    
class UIManager
{
private:
    std::unordered_map<std::string, UIComponent&> m_Components;
    
public:
    UIManager(render::Window* Window);
    ~UIManager();

    void AttachComponent(const std::string& Name, UIComponent& Component);
    void AttachComponent(UIComponent& Component);
    void RemoveComponent(const std::string& Name);

    const UIComponent& GetComponent(const std::string& Name) const;
    UIComponent& GetComponent(const std::string& Name);
    
    void Draw() const;
};


} // namespace ui
