/**
 * @file        wmodprop.hpp
 * 
 * @brief       Declaration of UIComponent WaterModelProperties.
 * 
 * @details     This file contains the declaration of the class WaterModelProperties,
 *              which extends UIComponent.\n 
 *              This class provides a user interface widget for handling and editing the
 *              properties of the water diffusion model.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-02-07
 */
#pragma once

#include <ui/uicomponent.hpp>


namespace ui
{
    
class WaterModelProperties : public UIComponent
{
private:
    double m_InitialWater;
    double m_LossRate;
    double m_Time;
    double m_TimeStep;
    bool m_Exact;
    bool m_IsPaused;
    bool m_IsReset;

protected:
    virtual void Draw() override;

public:
    WaterModelProperties(const std::string& Name,
                         int PosX,
                         int PosY,
                         int SizeX,
                         int SizeY);
    virtual ~WaterModelProperties();

    double GetInitialWater() const;
    double GetLossRate() const;
    double GetTime() const;
    double GetTimeStep() const;
    bool IsExact() const;
    bool IsPaused() const;
    bool IsReset() const;

    void Pause();
    void Reset();
};

    
} // namespace ui
