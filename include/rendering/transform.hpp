/**
 * @file        transform.hpp
 * 
 * @brief       Declaration of the Transform object.
 * 
 * @details     This file contains the declaration of the Transform object.\n 
 *              This object is used for representing transformations in 3D space.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-22
 */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace render
{
    
/**
 * @brief       Representation of the 3D transformations of an object.
 * 
 * @details     The Transform object represents the possible transformations of an
 *              object in 3D space.\n 
 *              The Transform can represents translations, rotations and scalings.\n 
 *              The class also provides a set of methods to access the transformation data
 *              and easily apply transformations to the object.
 */
class Transform
{
private:
    glm::vec3 m_Pos;
    glm::quat m_Rot;
    glm::vec3 m_Sca;


public:
    Transform(const glm::vec3& Pos, const glm::quat& Rot, const glm::vec3& Sca);
    Transform(const glm::vec3& Pos, const glm::vec3& EulerDeg, const glm::vec3& Sca);
    Transform(const glm::vec3& Pos = glm::vec3(0.0f));
    Transform(const Transform& T);

    Transform& operator=(const Transform& T);

    ~Transform();


    glm::vec3 GetPosition() const;
    glm::quat GetRotation() const;
    glm::vec3 GetEulerAngle() const;
    glm::vec3 GetScale() const;


    void SetPosition(const glm::vec3& Pos);
    void SetRotation(const glm::quat& Rot);
    void SetRotation(const glm::vec3& EulerDeg);
    void SetScale(const glm::vec3& Sca);
    void SetScale(float Sca);


    void Translate(const glm::vec3& Move);
    void Rotate(const glm::quat& Rotation);
    void Rotate(const glm::vec3& Rotation);
    void RotateAround(const glm::vec3& Axis, float Degrees);
    void LookAt(const glm::vec3& Target, const glm::vec3& WorldUp = glm::vec3(0.0f, 1.0f, 0.0f));
    void Scale(const glm::vec3& Factor);
    void Scale(float Factor);
    

    glm::vec3 Up() const;
    glm::vec3 Down() const;
    glm::vec3 Right() const;
    glm::vec3 Left() const;
    glm::vec3 Forward() const;
    glm::vec3 Backward() const;


    glm::mat4 GetTransformationMatrix() const;


    glm::vec3 Apply(const glm::vec3& Vec) const;
};

} // namespace bboids
