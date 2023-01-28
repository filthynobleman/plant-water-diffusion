/**
 * @file        window.hpp
 * 
 * @brief       Declaration of GLWindow.
 * 
 * @details     This file contains the declaration of the class GLWindow.\n 
 *              The class is a wrapper of basic functionalities for an OpenGL window.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-29
 */
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <ui/uimanager.hpp>

#include <string>

namespace render
{

struct Input
{
    GLenum      Keys[GLFW_KEY_LAST + 1];
    GLenum      Mouse[GLFW_MOUSE_BUTTON_LAST + 1];
    glm::dvec2  Cursor;
};
    
class Window
{
private:
    GLFWwindow* m_Window;
    glm::vec3   m_BGCol;
    bool        m_VSync;

    Input       m_PrevInput;
    Input       m_CurInput;

    double      m_PrevFrameTime;
    double      m_CurFrameTime;
    
public:
    Window(const std::string& Title, int Width, int Height);
    Window(const std::string& Title);
    ~Window();

    bool ShouldClose() const;
    void Close();

    int Width() const;
    int Height() const;

    glm::vec3 GetBackgroundColor() const;
    void SetBackgroundColor(const glm::vec3& BGCol);

    bool IsVSyncEnabled() const;
    void ToggleVSync(bool Value);

    void PollEvents();
    void RegisterInput();
    void ClearBackground();
    void SwapBuffers();

    bool KeyDown(GLenum Key) const;
    bool KeyPressed(GLenum Key) const;
    bool KeyReleased(GLenum Key) const;

    bool ButtonDown(GLenum Button) const;
    bool ButtonPressed(GLenum Button) const;
    bool ButtonReleased(GLenum Button) const;

    glm::dvec2 CursorPosition() const;
    glm::dvec2 CursorDelta() const;

    double Time() const;
    double DeltaTime() const;

    friend ui::UIManager::UIManager(render::Window*);
};


} // namespace render
