/**
 * @file        colmapprop.hpp
 * 
 * @brief       Declaration of UIComponent ColormapProperties.
 * 
 * @details     This file contains the declaration of the class ColormapProperties,
 *              which extends UIComponent.\n 
 *              This class provides a user interface widget for handling and editing
 *              a colormap.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-02-07
 */
#pragma once

#include <ui/uicomponent.hpp>
#include <vector>
#include <glm/glm.hpp>



namespace ui
{
    
class ColormapProperties : public UIComponent
{
private:
    std::vector<float> m_Values;
    std::vector<glm::vec3> m_Colors;

protected:
    virtual void Draw() override;

public:
    ColormapProperties(const std::string& Name, 
                       unsigned int PosX,
                       unsigned int PosY,
                       unsigned int SizeX,
                       unsigned int SizeY);
    virtual ~ColormapProperties();

    glm::vec3 GetColor(float t) const;
};

} // namespace ui
