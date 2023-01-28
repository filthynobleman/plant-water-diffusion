/**
 * @file        transform.cpp
 * 
 * @brief       Implementation of transform.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-22
 */
#include <rendering/transform.hpp>


render::Transform::Transform(const glm::vec3& Pos, const glm::quat& Rot, const glm::vec3& Sca)
    : m_Pos(Pos), m_Rot(Rot), m_Sca(Sca) { }

render::Transform::Transform(const glm::vec3& Pos, const glm::vec3& EulerDeg, const glm::vec3& Sca)
    : m_Pos(Pos), m_Rot(glm::radians(EulerDeg)), m_Sca(Sca) { }

render::Transform::Transform(const glm::vec3& Pos) 
    : m_Pos(Pos), m_Rot(glm::identity<glm::quat>()), m_Sca(glm::vec3(1.0f, 1.0f, 1.0f)) {}

render::Transform::Transform(const render::Transform& T)
    : m_Pos(T.m_Pos), m_Rot(T.m_Rot), m_Sca(T.m_Sca) {}

render::Transform& render::Transform::operator=(const render::Transform& T)
{
    m_Pos = T.m_Pos;
    m_Rot = T.m_Rot;
    m_Sca = T.m_Sca;
    return *this;
}

render::Transform::~Transform() {}



glm::vec3 render::Transform::GetPosition() const { return m_Pos; }
glm::quat render::Transform::GetRotation() const { return m_Rot; }
glm::vec3 render::Transform::GetScale() const { return m_Sca; }
glm::vec3 render::Transform::GetEulerAngle() const
{
    return glm::degrees(glm::eulerAngles(m_Rot));
}


void render::Transform::SetPosition(const glm::vec3& Pos)
{
    m_Pos = Pos;
}
void render::Transform::SetRotation(const glm::quat& Rot)
{
    m_Rot = Rot;
}
void render::Transform::SetRotation(const glm::vec3& EulerDeg)
{
    m_Rot = glm::quat(glm::radians(EulerDeg));
}
void render::Transform::SetScale(const glm::vec3& Sca)
{
    m_Sca = Sca;
}
void render::Transform::SetScale(float Sca)
{
    m_Sca = glm::vec3(Sca, Sca, Sca);
}



void render::Transform::Translate(const glm::vec3& Move)
{
    m_Pos += Move;
}
void render::Transform::Rotate(const glm::quat& Rotation)
{
    m_Rot *= Rotation;
}
void render::Transform::Rotate(const glm::vec3& EulerDeg)
{
    m_Rot *= glm::quat(glm::radians(EulerDeg));
}
void render::Transform::RotateAround(const glm::vec3& Axis, float Angle)
{
    glm::vec3 Ax = glm::mat3(glm::inverse(glm::toMat4(m_Rot))) * Axis;
    m_Rot = glm::rotate(m_Rot, glm::radians(Angle), Ax);
}
void render::Transform::LookAt(const glm::vec3& Target, const glm::vec3& WorldUp)
{
    m_Rot = glm::toQuat(glm::inverse(glm::lookAt(m_Pos, Target, WorldUp)));
}
void render::Transform::Scale(const glm::vec3& Factor)
{
    m_Sca *= Factor;
}
void render::Transform::Scale(float Factor)
{
    m_Sca *= Factor;
}


glm::vec3 render::Transform::Up() const
{
    return m_Rot * glm::vec3(0.0f, 1.0f, 0.0f);
}
glm::vec3 render::Transform::Down() const
{
    return m_Rot * glm::vec3(0.0f, -1.0f, 0.0f);
}

glm::vec3 render::Transform::Right() const
{
    return m_Rot * glm::vec3(1.0f, 0.0f, 0.0f);
}
glm::vec3 render::Transform::Left() const
{
    return m_Rot * glm::vec3(-1.0f, 0.0f, 0.0f);
}

glm::vec3 render::Transform::Forward() const
{
    return m_Rot * glm::vec3(0.0f, 0.0f, -1.0f);
}
glm::vec3 render::Transform::Backward() const
{
    return m_Rot * glm::vec3(0.0f, 0.0f, 1.0f);
}


glm::mat4 render::Transform::GetTransformationMatrix() const
{
    glm::mat4 res = glm::identity<glm::mat4>();
    res = glm::translate(res, m_Pos);
    res = res * glm::toMat4(m_Rot);
    res = glm::scale(res, m_Sca);
    return res;
}


glm::vec3 render::Transform::Apply(const glm::vec3& Vec) const
{
    return (m_Rot * (Vec * m_Sca)) + m_Pos;
}