/**
 * @file        camprop.hpp
 * 
 * @brief       Declaration of UIComponent CameraProperties.
 * 
 * @details     This file contains the declaration of the class CameraProperties,
 *              which derives from UIComponent.\n 
 *              This class handles a widget for modifying camera settings and properties.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2022-11-07
 */
#include <ui/uicomponent.hpp>

namespace ui
{
    
class CameraProperties : public UIComponent
{
private:
    float m_MoveSpeed;
    float m_RotSpeed;
    float m_Multiplier;


public:
    CameraProperties(const std::string& Name,
                     unsigned int PosX,
                     unsigned int PosY,
                     unsigned int SizeX,
                     unsigned int SizeY);
    virtual ~CameraProperties();

    float GetMoveSpeed() const;
    float GetRotSpeed() const;
    float GetSpeedMultiplier() const;

protected:
    virtual void Draw() override;
};

} // namespace ui
