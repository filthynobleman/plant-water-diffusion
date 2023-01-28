/**
 * @file        lightprop.hpp
 * 
 * @brief       Declaration of UIComponent LightProperties.
 * 
 * @details     This file contains the declaration of the class LightProperties,
 *              derived from UIComponent.\n 
 *              This class implements a widget for handling properties of a light source.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2022-11-07
 */
#pragma once

#include <ui/uicomponent.hpp>
#include <rendering/shader.hpp>

namespace ui
{
    
class LightProperties : public UIComponent
{
private:
    render::Light m_Light;
    

public:
    LightProperties(const std::string& Name,
                    unsigned int PosX,
                    unsigned int PosY,
                    unsigned int SizeX,
                    unsigned int SizeY);
    virtual ~LightProperties();

    const render::Light& GetLight() const;

protected:
    virtual void Draw() override;
};


} // namespace ui
