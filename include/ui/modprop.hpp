/**
 * @file        modprop.hpp
 * 
 * @brief       Declaration of UIComponent ModelProperties.
 * 
 * @details     This file contains the declaration of the class ModelProperties, which
 *              extends UIComponent.\n 
 *              This class provides a user interface widget for modifying rendering
 *              properties of the model.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2022-11-07
 */
#pragma once

#include <ui/uicomponent.hpp>
#include <rendering/model.hpp>
#include <rendering/shader.hpp>


namespace ui
{
    
class ModelProperties : public UIComponent
{
private:
    float m_CurScale;
    bool m_Updated;
    render::Material m_Material;
    render::Model* m_Model;

public:
    ModelProperties(const std::string& Name, 
                    render::Model* Model,
                    unsigned int PosX,
                    unsigned int PosY,
                    unsigned int SizeX,
                    unsigned int SizeY);
    virtual ~ModelProperties();

    const render::Material& GetMaterial() const;

protected:
    virtual void Draw() override;
};

} // namespace ui
