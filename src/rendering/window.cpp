/**
 * @file        window.cpp
 * 
 * @brief       Implements window.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-31
 */
#include <rendering/window.hpp>
#include <sstream>

#include <imgui.h>
#include <imgui_impl_opengl3.h>

void framebuf_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


render::Window::Window(const std::string& Title)
{
    // Initialize GLFW
    if (!glfwInit())
        throw std::runtime_error("Cannot initialize GLFW.");

    // Create actual window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* VideoMode = glfwGetVideoMode(Monitor);
    int Width = VideoMode->width;
    int Height = VideoMode->height;
    m_Window = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
    if (m_Window == NULL)
    {
        std::stringstream ss;
        ss << "Cannot initialize a " << Width << " x " << Height << " window ";
        ss << "with title \"" << Title << "\".";
        throw std::runtime_error(ss.str());
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, framebuf_size_callback);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Cannot load GLAD.");

    // Z-buffer ordering
    glEnable(GL_DEPTH_TEST);

    // Enable VSync
    ToggleVSync(true);

    // Background color
    m_BGCol = glm::vec3(0.0f);

    // Register initial time
    m_PrevFrameTime = glfwGetTime();
    m_CurFrameTime = glfwGetTime();
}

render::Window::Window(const std::string& Title, int Width, int Height)
{
    // Initialize GLFW
    if (!glfwInit())
        throw std::runtime_error("Cannot initialize GLFW.");

    // Create actual window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_Window = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
    if (m_Window == NULL)
    {
        std::stringstream ss;
        ss << "Cannot initialize a " << Width << " x " << Height << " window ";
        ss << "with title \"" << Title << "\".";
        throw std::runtime_error(ss.str());
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, framebuf_size_callback);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Cannot load GLAD.");

    // Z-buffer ordering
    glEnable(GL_DEPTH_TEST);

    // Enable VSync
    ToggleVSync(true);

    // Background color
    m_BGCol = glm::vec3(0.0f);

    // Register initial time
    m_PrevFrameTime = glfwGetTime();
    m_CurFrameTime = glfwGetTime();
}

render::Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}


bool render::Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

void render::Window::Close()
{
    glfwSetWindowShouldClose(m_Window, true);
}

int render::Window::Width() const
{
    int w, h;
    glfwGetWindowSize(m_Window, &w, &h);
    return w;
}

int render::Window::Height() const
{
    int w, h;
    glfwGetWindowSize(m_Window, &w, &h);
    return h;
}

bool render::Window::IsVSyncEnabled() const
{
    return m_VSync;
}

void render::Window::ToggleVSync(bool Value)
{
    m_VSync = Value;
    glfwSwapInterval(Value ? 1 : 0);
}


glm::vec3 render::Window::GetBackgroundColor() const { return m_BGCol; }
void render::Window::SetBackgroundColor(const glm::vec3& BGCol)
{
    m_BGCol = glm::clamp(BGCol, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}


void render::Window::PollEvents()
{
    glfwPollEvents();
}

void render::Window::ClearBackground()
{
    glClearColor(m_BGCol.r, m_BGCol.g, m_BGCol.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render::Window::SwapBuffers()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_Window);
    m_PrevFrameTime = m_CurFrameTime;
    m_CurFrameTime = glfwGetTime();
}


void render::Window::RegisterInput()
{
    m_PrevInput = m_CurInput;

    for (int i = 0; i < GLFW_KEY_LAST; ++i)
        m_CurInput.Keys[i] = glfwGetKey(m_Window, i);
    
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
        m_CurInput.Mouse[i] = glfwGetMouseButton(m_Window, i);

    glfwGetCursorPos(m_Window, &(m_CurInput.Cursor.x), &(m_CurInput.Cursor.y));
}

bool render::Window::KeyDown(GLenum Key) const
{
    return m_CurInput.Keys[Key] == GLFW_PRESS;
}
bool render::Window::KeyPressed(GLenum Key) const
{
    return KeyDown(Key) && m_PrevInput.Keys[Key] == GLFW_RELEASE;
}
bool render::Window::KeyReleased(GLenum Key) const
{
    return !KeyDown(Key) && m_PrevInput.Keys[Key] == GLFW_PRESS;
}

bool render::Window::ButtonDown(GLenum Button) const
{
    return m_CurInput.Mouse[Button] == GLFW_PRESS;
}
bool render::Window::ButtonPressed(GLenum Button) const
{
    return ButtonDown(Button) && m_PrevInput.Mouse[Button] == GLFW_RELEASE;
}
bool render::Window::ButtonReleased(GLenum Button) const
{
    return !ButtonDown(Button) && m_PrevInput.Mouse[Button] == GLFW_PRESS;
}

glm::dvec2 render::Window::CursorPosition() const
{
    return m_CurInput.Cursor;
}
glm::dvec2 render::Window::CursorDelta() const
{
    return CursorPosition() - m_PrevInput.Cursor;
}

double render::Window::Time() const
{
    return m_CurFrameTime;
}
double render::Window::DeltaTime() const
{
    return m_CurFrameTime - m_PrevFrameTime;
}