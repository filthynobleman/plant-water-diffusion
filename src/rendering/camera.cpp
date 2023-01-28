/**
 * @file        camera.cpp
 * 
 * @brief       Implementation of camera.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-22
 */
#include <rendering/camera.hpp>


render::Camera::Camera(const render::Transform& T, float FoV, float Aspect, float ZNear, float ZFar)
    : m_Transform(T), m_Aspect(Aspect), m_FoV(glm::radians(FoV)), m_Near(ZNear), m_Far(ZFar) {}

render::Camera::Camera(float FoV, float Aspect, float ZNear, float ZFar)
    : m_Aspect(Aspect), m_FoV(glm::radians(FoV)), m_Near(ZNear), m_Far(ZFar) {}

render::Camera::Camera(const render::Camera& C)
    : m_Transform(C.m_Transform), m_FoV(C.m_FoV), m_Aspect(C.m_Aspect), 
      m_Near(C.m_Near), m_Far(C.m_Far) {}

render::Camera::Camera() 
    : m_FoV(glm::radians(45.0f)), m_Aspect(16.0f / 9.0f), m_Near(1e-3f), m_Far(1e3f) {}

render::Camera& render::Camera::operator=(const render::Camera& C)
{
    m_Transform = C.m_Transform;
    m_FoV = C.m_FoV;
    m_Aspect = C.m_Aspect;
    m_Near = C.m_Near;
    m_Far = C.m_Far;

    return *this;
}

render::Camera::~Camera() {}




render::Transform& render::Camera::GetTransform() { return m_Transform; }
render::Transform render::Camera::GetTransform() const { return m_Transform; }

float render::Camera::GetFieldOfView() const { return glm::degrees(m_FoV); }
float render::Camera::GetAspectRatio() const { return m_Aspect; }
float render::Camera::GetZNear() const { return m_Near; }
float render::Camera::GetZFar() const { return m_Far; }
float render::Camera::GetMovementSpeed() const { return m_MoveSpeed; }
float render::Camera::GetRotationSpeed() const { return m_RotSpeed; }
float render::Camera::GetSprintMultiplier() const { return m_Sprint; }

void render::Camera::SetFieldOfView(float FoV)
{
    m_FoV = glm::radians(FoV);
}
void render::Camera::SetAspectRatio(float Aspect)
{
    m_Aspect = Aspect;
}
void render::Camera::SetAspectRatio(float Width, float Height)
{
    m_Aspect = Width / Height;
}
void render::Camera::SetZNear(float ZNear) { m_Near = ZNear; }
void render::Camera::SetZFar(float ZFar) { m_Far = ZFar; }
void render::Camera::SetClipping(float ZNear, float ZFar)
{
    m_Near = ZNear;
    m_Far = ZFar;
}
void render::Camera::SetMovementSpeed(float MoveSpeed) { m_MoveSpeed = MoveSpeed; }
void render::Camera::SetRotationSpeed(float RotSpeed) { m_RotSpeed = RotSpeed; }
void render::Camera::SetSprintMultiplier(float Multiplier) { m_Sprint = Multiplier; }


glm::mat4 render::Camera::GetViewMatrix() const
{
    glm::vec3 Eye = m_Transform.GetPosition();
    glm::vec3 Target = Eye + m_Transform.Forward();
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);// m_Transform.Up();
    return glm::lookAt(Eye, Target, Up);
}

glm::mat4 render::Camera::GetProjectionMatrix() const
{
    return glm::perspective(m_FoV, m_Aspect, m_Near, m_Far);
}

void render::Camera::RelativeMovement(const glm::vec3& RelDir, bool Sprint, float dt)
{
    glm::vec3 Dir = RelDir.x * GetTransform().Right() +
                    RelDir.y * GetTransform().Up() +
                    RelDir.z * GetTransform().Forward();
    Dir *= m_MoveSpeed;
    if (Sprint)
        Dir *= m_Sprint;
    Dir *= dt;
    GetTransform().Translate(Dir);
}

void render::Camera::YawRotate(float Degrees, bool Sprint, float dt)
{
    float Angle = Degrees * m_RotSpeed * dt;
    if (Sprint)
        Angle *= m_Sprint;
    GetTransform().RotateAround(glm::vec3(0.0f, 1.0f, 0.0f), Angle);
}

void render::Camera::PitchRotate(float Degrees, bool Sprint, float dt)
{
    float Angle = Degrees * m_RotSpeed * dt;
    if (Sprint)
        Angle *= m_Sprint;
    float CurPitch = glm::degrees(glm::acos(GetTransform().Forward().y)) - 90.0f;
    float RealAngle = glm::clamp(CurPitch + Angle, -80.0f, 80.0f);
    RealAngle -= CurPitch;
    GetTransform().RotateAround(GetTransform().Right(), RealAngle);
}