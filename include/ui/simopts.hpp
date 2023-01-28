/**
 * @file        simopts.hpp
 * 
 * @brief       Declaration of UIComponent SimulationOptions.
 * 
 * @details     This file contains the declaration of class SimulationOptions, which
 *              derives from UIComponent.\n 
 *              This class handles a widget for setting up options and properties of
 *              the simulation.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2022-11-07
 */
#pragma once

#include <ui/uicomponent.hpp>

namespace ui
{
    
class SimulationOptions : public UIComponent
{
private:
    float m_MoveSpeed;
    float m_RotSpeed;
    bool m_Paused;
    

public:
    SimulationOptions(const std::string& Name, 
                      unsigned int PosX,
                      unsigned int PosY,
                      unsigned int SizeX,
                      unsigned int SizeY);
    virtual ~SimulationOptions();

    float GetMoveSpeed() const;
    float GetRotSpeed() const;
    bool IsPaused() const;

protected:
    virtual void Draw() override;
};


} // namespace ui
