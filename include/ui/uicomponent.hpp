/**
 * @file        uicomponent.hpp
 * 
 * @brief       Declaration of base class UIComponent.
 * 
 * @details     This file contains the declaration of the class UIComponent.\n 
 *              This is an abstract class that serves as base class for every
 *              component of the graphical user interface of the application.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-11-01
 */
#pragma once

#include <string>

namespace ui    
{

class UIComponent
{
private:
    std::string m_Name;

protected:
    unsigned int m_PosX;
    unsigned int m_PosY;
    unsigned int m_SizeX;
    unsigned int m_SizeY;

    virtual void Draw() = 0;
    
public:
    UIComponent(const std::string& Name, 
                unsigned int PosX,
                unsigned int PosY,
                unsigned int SizeX,
                unsigned int SizeY);
    virtual ~UIComponent();

    std::string GetName() const;
    void SetName(const std::string& Name);

    virtual void DrawWidget();
};

    
} // namespace ui   
