/**
 * @file        camera.hpp
 * 
 * @brief       Declaration of a class Camera.
 * 
 * @details     This file contains the declaration of a class Camera.\n 
 *              A Camera represents a point of view for rendering a 3D scene.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-22
 */
#pragma once

#include <rendering/transform.hpp>

namespace render
{
    
/**
 * @brief       Represents a render point for the scene.
 * 
 * @details     An object of type Camera represents a camera in a 3D scene.\n 
 *              A camera is a point of view for rendering the scene.\n 
 *              This object provides a set of methods for handling a basic perspective
 *              camera and moving it in a scene.
 */
class Camera
{
private:
    Transform   m_Transform;
    float       m_FoV;
    float       m_Aspect;
    float       m_Near;
    float       m_Far;

    float       m_MoveSpeed = 3.0f;
    float       m_RotSpeed  = 3.0f;
    float       m_Sprint    = 2.0f;

public:
    Camera(const Transform& T, float FoV, float Aspect, float ZNear, float ZFar);
    Camera(float FoV, float Aspect, float ZNear, float ZFar);
    Camera(const Camera& C);
    Camera();

    Camera& operator=(const Camera& C);

    ~Camera();


    Transform& GetTransform();
    Transform GetTransform() const;

    float GetFieldOfView() const;
    float GetAspectRatio() const;
    float GetZNear() const;
    float GetZFar() const;

    float GetMovementSpeed() const;
    float GetRotationSpeed() const;
    float GetSprintMultiplier() const;


    void SetFieldOfView(float FoV);
    void SetAspectRatio(float Aspect);
    void SetAspectRatio(float Width, float Height);
    void SetZNear(float ZNear);
    void SetZFar(float ZFar);
    void SetClipping(float ZNear, float ZFar);

    void SetMovementSpeed(float MoveSpeed);
    void SetRotationSpeed(float RotSpeed);
    void SetSprintMultiplier(float Multiplier);


    void RelativeMovement(const glm::vec3& RelDir, bool Sprint = false, float dt = 1.0f);
    void YawRotate(float Degrees, bool Sprint = false, float dt = 1.0f);
    void PitchRotate(float Degrees, bool Sprint = false, float dt = 1.0f);


    


    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
};


} // namespace bboids
